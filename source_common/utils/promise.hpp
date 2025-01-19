/*
 * SPDX-License-Identifier: MIT
 * ----------------------------------------------------------------------------
 * Copyright (c) 2014-2025 Arm Limited
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
 * This module implements a way of wrapping arbitrary resource cleanup for
 * resources that are not natively RAII-managed.
 */

#pragma  once

#include <functional>
#include <ranges>
#include <vector>

/**
 * @brief RAII managed trigger for cleanup actions.
 *
 * A Promise is designed as a means to manage arbitrary cleanup actions using
 * C++ object lifetime to trigger cleanup when the Promise is destroyed.
 * Typically a Promise will be allocated on the stack, executing cleanups when
 * the object drops out of scope.
 *
 * - A Promise can be manually resolved early by calling fulfill().
 * - A Promise can be discarded without executing by calling dispose().
 * - A Promise cannot be copy constructed or copy assigned.
 * - A Promise can be move constructed or move assigned.
 *
 * All references to the resource itself are via the "action" object, which
 * will typically be a dynamically created lambda function.
 */
class Promise
{
public:
    /* Disable copying; only moving allowed. */
    Promise(const Promise&) = delete;
    Promise& operator=(const Promise&) = delete;

    /** @brief Resource cleanup is a "void func()" function. */
    using Action = std::function<void()>;

    /**
     * @brief Create a new promise.
     *
     * @param[in] action   A callable action to execute in future.
     */
    Promise(const Action& action) : action(action) { }

    /**
     * @brief Destroy the promise.
     *
     * This will execute the promised action, unless it has already been
     * manually resolved or discarded.
     */
    ~Promise()
    {
        fulfill();
    }

    /**
     * @brief Create a new promise by moving the action out of another.
     *
     * @param[in] that   The promise to move the action from.
     */
    Promise(Promise&& that) : action(nullptr)
    {
        std::swap(this->action, that.action);
    }

    /**
     * @brief Assign a new promise by moving the action out of another.
     *
     * @param[in] that   The promise to move the action from.
     */
    Promise& operator=(Promise&& that)
    {
        Promise temp(std::move(that));
        std::swap(this->action, temp.action);
        return *this;
    }

    /**
     * @brief Fullfill the promise.
     */
    void fulfill()
    {
        // Swap with nullptr so that calling fulfill twice is benign
        Action action_copy(nullptr);
        std::swap(action, action_copy);
        if (action_copy != nullptr)
        {
            action_copy();
        }
    }

    /**
     * @brief Dispose of the promise without executing it.
     */
    void dispose()
    {
        action = nullptr;
    }

private:
    /** @brief The stored action function. */
    Action action;
};

/**
 * @brief RAII managed trigger for a stack of cleanup actions.
 *
 * Promises are designed as a means to manage arbitrary cleanup actions stored
 * in a Promise, using the Promises container object lifetime to trigger
 * cleanup of the Promise objects it contains when the container is destroyed.
 *
 * Promise actions in this container are fulfilled in the reverse order to
 * which they were added, i.e. LIFO, which is often needed for resource
 * cleanup actions.
 *
 * - A Promises stack can be resolved early by calling fulfill().
 * - A Promises stack cannot be copy constructed or copy assigned.
 * - A Promises stack can be move constructed or move assigned.
 */
class Promises
{
public:
    /* Disable all copies and moves of the container type. */
    Promises(const Promise&) = delete;
    Promises& operator=(const Promise&) = delete;
    Promises(Promises &&) = delete;
    Promises& operator= (Promises &&) = delete;

    /**
     * @brief Create a new empty stack.
     */
    Promises() = default;

    /**
     * @brief Destroy the promises stack.
     *
     * This will fulfill all stored promises in LIFO order.
     */
    ~Promises()
    {
        fulfill();
    }

    /**
     * @brief Add a new clean up action to the list.
     *
     * @param action   A callable action to execute in future.
     */
    void add(const Promise::Action & action)
    {
        promises.emplace_back(action);
    }

    /**
     * @brief Add a new promise to the list.
     *
     * The original Promise passed in will be invalid after this, as ownership
     * of the stored action it contained will have been transferred to another
     * Promise owned by this container.
     *
     * @param promise   A previously created Promised action.
     */
    void add(Promise && promise)
    {
        promises.emplace_back(std::move(promise));
    }

    /**
     * @brief Fulfill all stored promises in LIFO order.
     */
    void fulfill()
    {
        // Move to clear the stored list
        std::vector<Promise> promises_copy(std::move(promises));

        // Resolve the promises in reverse order
        for(auto& i :  std::ranges::reverse_view(promises_copy))
        {
            i.fulfill();
        }
    }

private:
    /** @brief The stored list of promises. */
    std::vector<Promise> promises;
};
