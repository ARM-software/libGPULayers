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
 * Implementation of the asynchronous layer command stream.
 */

#include <chrono>
#include <thread>

#include "utils/async_lcs.hpp"

/* See header for documentation. */
ALSCTaskTimelineSem::ALSCTaskTimelineSem(
    Device& _device,
    VkSemaphore _semaphore,
    uint64_t _waitValue,
    Action _action
):
    device(_device),
    semaphore(_semaphore),
    waitValue(_waitValue),
    action(_action)
{

}

/* See header for documentation. */
bool ALSCTaskTimelineSem::waitForRunnable()
{
    VkSemaphoreWaitInfo waitInfo {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_WAIT_INFO,
        .pNext = nullptr,
        .flags = 0,
        .semaphoreCount = 1,
        .pSemaphores = &semaphore,
        .pValues = &waitValue
    };

    auto result = vkWaitSemaphores(device.device, &waitInfo, UINT64_MAX);
    return result == VK_SUCCESS;
}

/* See header for documentation. */
void ALSCTaskTimelineSem::runTask()
{
    action();
}

/* See header for documentation. */
ALSCTaskEvent::ALSCTaskEvent(
    Device& _device,
    VkEvent _event,
    Action _action
):
    device(_device),
    event(_event),
    action(_action)
{

}

/* See header for documentation. */
bool ALSCTaskEvent::waitForRunnable()
{
    bool success { false };
    while(true)
    {
        auto result = vkGetEventStatus(device.device, event);
        if (result == VK_EVENT_RESET)
        {
            std::this_thread::sleep_for(std::chrono::microseconds(100));
            continue;
        }

        // Event is either set or Vulkan is in error ...
        success = result == VK_EVENT_SET;
        break;
    }

    return success;
}

/* See header for documentation. */
void ALSCTaskEvent::runTask()
{
    action();
}

/* See header for documentation. */
ALSCRunner::ALSCRunner()
{
    // Create and start a worker thread
    worker = std::thread(&ALSCRunner::runWorker, this);
}

/* See header for documentation. */
void ALSCRunner::put(
    std::shared_ptr<ALSCTask> task
) {
    queue.put(task);
}

/* See header for documentation. */
void ALSCRunner::stop()
{
    // Put a stop event at the end of the queue
    // All previous events are processed before stopping
    std::shared_ptr<ALSCTask> stopTask = std::make_shared<ALSCTaskStop>();
    put(stopTask);

    // Wait for the thread to complete pending events and shutdown
    worker.join();
}

void ALSCRunner::runWorker()
{
    while (true)
    {
        auto event = queue.get();

        // Event is a stop event used to wake the runner on shutdown
        if (event->isStop())
        {
            event->notify();
            break;
        }

        // Event is a real event that needs handling
        bool success = event->waitForRunnable();
        if (success)
        {
            event->runTask();
        }

        event->notify();
    }
}
