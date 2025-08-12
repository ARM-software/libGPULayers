/*
 * SPDX-License-Identifier: MIT
 * ----------------------------------------------------------------------------
 * Copyright (c) 2024-2025 Arm Limited
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
 * The implementation of a basic thread-safe task queue.
 */

#pragma once

#include <atomic>
#include <deque>
#include <mutex>
#include <condition_variable>

/**
 * @brief Base class for a task.
 */
class Task
{
public:
    /**
     * @brief Destroy the task.
     */
    virtual ~Task() = default;

    /**
     * @brief Wait for the task to be complete.
     */
    void wait()
    {
        std::unique_lock<std::mutex> lock(conditionLock);
        completeCondition.wait(lock, [this]{ return complete.load(); });
    }

    /**
     * @brief Notify that the task is complete.
     */
    void notify()
    {
        std::unique_lock<std::mutex> lock(conditionLock);
        complete = true;
        lock.unlock();
        completeCondition.notify_all();
    }

private:
    /** @brief Task completion status. */
    std::atomic<bool> complete { false };

    /** @brief Condition variable for notifications. */
    std::condition_variable completeCondition;

    /** @brief Lock for notifications. */
    std::mutex conditionLock;
};


/**
 * @brief A thread-safe FIFO task queue.
 */
template <class T>
class TaskQueue
{
private:
    /** @brief Lock for thread-safe access. */
    std::mutex storeLock;

    /** @brief Condition variable for notifications. */
    std::condition_variable condition;

    /** @brief Dequeue for data storage. */
    std::deque<T> store;

public:
    /**
     * @brief Add a new task to the end of the queue.
     *
     * @param task   The new task to append to the queue.
     */
    void put(
        T task
    ) {
        std::lock_guard<std::mutex> lock(storeLock);
        store.push_back(task);
        condition.notify_one();
    }

    /**
     * @brief Get the oldest task from the head of the queue.
     *
     * This function blocks until a task is available.
     *
     * @return The oldest task in the list.
     */
    T get()
    {
        std::unique_lock<std::mutex> lock(storeLock);

        // Release lock until we have data, and then reacquire
        while(store.empty())
        {
            condition.wait(lock);
        }

        T task = store.front();
        store.pop_front();
        return task;
    }

    /**
     * @brief Test if the queue is currently empty.
     *
     * Note that this is racy so the queue may not stay empty if other
     * threads are still using it ...
     *
     * @return @c true if the queue is empty, @c false otherwise.
     */
    bool isEmpty()
    {
        std::lock_guard<std::mutex> lock(storeLock);
        return store.empty();
    }
};
