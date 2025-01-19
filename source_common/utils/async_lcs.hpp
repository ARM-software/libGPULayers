/*
 * SPDX-License-Identifier: MIT
 * ----------------------------------------------------------------------------
 * Copyright (c) 2025 Arm Limited
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 * ----------------------------------------------------------------------------
 */

/**
 * @file
 * Vulkan layers often need to perform tasks that can only be performed when
 * submitted GPU command streams have progressed to a certain point. Triggers
 * for CPU-side work can include:
 *
 *   - A timeline semaphore reaching a threshold value when a submit completes.
 *   - An event being signalled when a command stream reaches a certain point*.
 *
 * (*): Waiting on an event that is set by a command stream while its submit
 * is still executing, and using the triggered CPU-side work to set an event
 * for GPU-side work that is already submitted is out-of-spec. However, some of
 * our layers rely on it to avoid the need to have the layer manually split
 * apart application command buffers.
 *
 * The asynchronous layer command stream (ALCS) is a way of quickly and
 * reliably managing execution of CPU-side tasks that can only be triggered
 * when a particular milestone is reached in the command stream. To allow these
 * async tasks to progress independently from the application API calls, the
 * async layer command stream manager creates one thread per Vulkan queue to
 * perform all async tasks associated with that queue.
 *
 * Cross-queue async work can be implemented by using Timeline semaphores and
 * injecting the ALSC task into the queue that writes the highest timeline
 * semaphore value. Cross-queue handling is implemented outside of the ALSC
 * module.
 *
 *
 * Async trigger: Timeline semaphore
 * ---------------------------------
 *
 * Work associated with a timeline semaphore must also specify the time value
 * to wait for, and will block and wait for the semaphore to reach that value.
 *
 * Async trigger: Event
 * --------------------
 *
 * Work associated with a binary event will block and wait for the binary
 * event to be signalled.
 *
 * Threading model
 * ---------------
 *
 * The ALSC workloads for any single queue are processed in FIFO order, with
 * the worker thread dequeuing one task at a time and then blocking waiting for
 * it to become eligible for execution. The layer MUST add ALSC workloads to
 * the queue in the order they are signalled by the implementation or deadlock
 * will occur.
 *
 * The ALSC callbacks that run to execute an async task and triggered with no
 * locks held. The layer MUST use appropriate locking in the event handler
 * is accessing shared data resources.
 */

#pragma  once

#include <atomic>
#include <functional>
#include <memory>
#include <thread>

#include <vulkan/vulkan.h>

#include "device.hpp"          // Include from per-layer code
#include "utils/queue.hpp"

/**
 * @brief Baseclass for an async layer command stream task.
 */
class ALSCTask : public Task
{
public:
    /**
     * @brief Type for execution callbacks.
     */
    using Action = std::function<void()>;

    /**
     * @brief Destroy the task.
     */
    virtual ~ALSCTask() = default;

    /**
     * @brief Wait for this task to become runnable.
     *
     * @return True on success, or False on a Vulkan error.
     */
    virtual bool waitForRunnable() = 0;

    /**
     * @brief Run this task.
     */
    virtual void runTask() = 0;

    /**
     * @brief Is this a stop task?
     */
    virtual bool isStop()
    {
        return false;
    }
};

/**
 * @brief Dummy task use to unblock the task queue.
 */
class ALSCTaskStop : public ALSCTask
{
public:
    /**
     * @brief Destroy the task.
     */
    virtual ~ALSCTaskStop() = default;

    /* See baseclass for documentation. */
    bool waitForRunnable()
    {
        return true;
    }

    /* See baseclass for documentation. */
    virtual void runTask() { };

    /* See baseclass for documentation. */
    virtual bool isStop()
    {
        return true;
    }
};

/**
 * @brief An async layer command stream task triggered by a timeline sem.
 */
class ALSCTaskTimelineSem : public ALSCTask
{
public:
    /**
     * @brief Create a new async event.
     *
     * @param device       The layer device context.
     * @param semaphore    The triggering timeline semaphore.
     * @param waitValue    The target timeline value to wait for.
     * @param action       The callback to trigger.
     */
    ALSCTaskTimelineSem(
        Device& device,
        VkSemaphore semaphore,
        uint64_t waitValue,
        Action action);

    /**
     * @brief Destroy the task.
     */
    virtual ~ALSCTaskTimelineSem() = default;

    /* See baseclass for documentation. */
    virtual bool waitForRunnable();

    /* See baseclass for documentation. */
    virtual void runTask() ;

private:
    /**
     * @brief The layer device context.
     */
    Device& device;

    /**
     * @brief The layer semaphore to wait for.
     */
    VkSemaphore semaphore;

    /**
     * @brief The layer timeline value to wait for.
     */
    uint64_t waitValue;

    /**
     * @brief The action to trigger.
     */
    Action action;
};

/**
 * @brief An async layer command stream task triggered by an event.
 */
class ALSCTaskEvent : public ALSCTask
{
public:
    /**
     * @brief Create a new async event.
     *
     * @param device   The layer device context.
     * @param event    The triggering event.
     * @param action   The callback to trigger.
     */
    ALSCTaskEvent(
        Device& device,
        VkEvent event,
        Action action);

    /* See baseclass for documentation. */
    virtual ~ALSCTaskEvent() = default;

    /* See baseclass for documentation. */
    virtual bool waitForRunnable();

    /* See baseclass for documentation. */
    virtual void runTask();

private:
    /**
     * @brief The layer device context.
     */
    Device& device;

    /**
     * @brief The layer event to wait for.
     */
    VkEvent event;

    /**
     * @brief The action to trigger.
     */
    Action action;
};


/**
 * @brief Runner class used to run the async command stream.
 *
 * Commands in the command stream are executed in FIFO order. Queue commands in
 * such a way to avoid deadlocks.
 */
class ALSCRunner
{
public:
    /**
     * @brief Construct an async queue and start the runner working.
     */
    ALSCRunner();

    /**
     * @brief Put a new async task on the end of the queue.
     *
     * @param task   The async task to execute when it becomes runnable.
     */
    void put(
        std::shared_ptr<ALSCTask> task);

    /**
     * @brief Stop the runner thread and wait for it to stop.
     */
    void stop();

    /**
     * @brief Async entrypoint for the worker thread.
     */
    void runWorker();

private:
    /**
     * @brief The worker thread running the async handler.
     */
    std::thread worker;

    /**
     * @brief The FIFO task queue of async tasks.
     */
    TaskQueue<std::shared_ptr<ALSCTask>> queue;
};
