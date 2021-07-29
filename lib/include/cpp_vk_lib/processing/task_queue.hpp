#ifndef VK_PROCESSING_TASK_QUEUE_HPP
#define VK_PROCESSING_TASK_QUEUE_HPP

#include "misc/cppdefs.hpp"

#include "spdlog/spdlog.h"

#include <condition_variable>
#include <deque>
#include <future>
#include <iostream>
#include <sstream>
#include <vector>

namespace vk {
namespace processing {

class task_queue
{
    enum class stop_policy
    {
        wait_for_queue_completion,
        stop_after_current_task
    };

public:
    VK_DISABLE_COPY_MOVE(task_queue)

    using exception_callback_t = std::function<void(std::exception_ptr)>;

    explicit task_queue(size_t num_workers = std::thread::hardware_concurrency());

    task_queue& set_exception_handler(exception_callback_t handler);

    task_queue& set_num_workers(size_t num);

    void start();
    void stop();

    template <typename Function, typename... Args>
    bool push_void_task(Function&& fn, Args&&... args);

    template <typename Function, typename... Args, typename InvokeTaskType = std::invoke_result_t<Function, Args...>>
    std::pair<bool, std::future<InvokeTaskType>> push_future_task(Function&& fn, Args&&... args);

    void wait_for_completion();

    ~task_queue();

private:
    void set_default_exception_handler();
    void init_workers(size_t num);

    std::condition_variable m_notifier;
    std::deque<std::function<void()>> m_tasks;
    exception_callback_t m_on_exception;
    std::mutex m_locker;
    std::vector<std::thread> m_workers;
    size_t m_num_workers;
    stop_policy m_stop_policy = stop_policy::stop_after_current_task;
    std::atomic<bool> m_running;
    std::atomic<bool> m_stop_requested;
};

inline task_queue::task_queue(size_t num_workers)
  : m_num_workers(num_workers)
  , m_running(false)
  , m_stop_requested(false)
{
    set_default_exception_handler();
}

inline task_queue& task_queue::set_exception_handler(task_queue::exception_callback_t handler)
{
    m_on_exception = std::move(handler);
    return *this;
}

inline task_queue& task_queue::set_num_workers(size_t num)
{
    if (m_running) {
        throw std::runtime_error("Attempt to change number of workers while running");
    }
    m_num_workers = num;
    return *this;
}

inline void task_queue::start()
{
    if (m_running) {
        return;
    }
    m_running = true;
    init_workers(m_num_workers);
}

inline void task_queue::stop()
{
    if (!m_running) {
        return;
    }
    m_stop_requested = true;
    m_running = false;
    m_notifier.notify_all();
    for (auto& w : m_workers) {
        w.join();
    }
    m_workers.clear();
    m_stop_requested = false;
}

template <typename Function, typename... Args>
bool task_queue::push_void_task(Function&& fn, Args&&... args)
{
    if (m_stop_requested) {
        return false;
    }

    std::unique_lock<decltype(m_locker)> lock(m_locker);
    m_tasks.emplace_back([this, fn = std::forward<Function>(fn), tp = std::make_tuple(std::forward<Args>(args)...)]() mutable {
        try {
            std::apply(std::forward<Function>(fn), std::forward<decltype(tp)>(tp));
        } catch (...) {
            m_on_exception(std::current_exception());
        }
    });
    m_locker.unlock();
    m_notifier.notify_one();

    return true;
}

inline void task_queue::wait_for_completion()
{
    if (!m_running) {
        return;
    }
    m_stop_policy = stop_policy::wait_for_queue_completion;
    stop();
    m_stop_policy = stop_policy::stop_after_current_task;
    start();
}

inline task_queue::~task_queue()
{
    stop();
}

inline void task_queue::set_default_exception_handler()
{
    m_on_exception = [](std::exception_ptr ex_ptr) -> void {
        if (!ex_ptr) {
            return;
        }

        try {
            std::rethrow_exception(ex_ptr);
        } catch (std::exception& ex) {
            std::ostringstream stream;
            stream << std::this_thread::get_id();
            spdlog::warn("task queue: exception from thread {}", stream.str());
        } catch (...) {
            spdlog::warn("task queue: unknown exception");
        }
    };
}

inline void task_queue::init_workers(size_t num)
{
    for (size_t i = 0; i < num; ++i) {
        m_workers.emplace_back([this]() {
            while (true) {
                std::unique_lock<decltype(m_locker)> locker(m_locker);
                m_notifier.wait(locker, [this] {
                    return !m_tasks.empty() || m_stop_requested;
                });
                if (m_stop_requested) {
                    if (m_tasks.empty() || m_stop_policy == stop_policy::stop_after_current_task) {
                        return;
                    }
                }
                auto task = std::move(m_tasks.front());
                m_tasks.pop_front();
                locker.unlock();
                task();
            }
        });
    }
}

template <typename Function, typename... Args, typename InvokeTaskType>
inline std::pair<bool, std::future<InvokeTaskType>> task_queue::push_future_task(Function&& fn, Args&&... args)
{
    if (m_stop_requested) {
        return {false, std::future<InvokeTaskType>()};
    }
    auto result_promise = std::make_shared<std::promise<InvokeTaskType>>();
    auto result_future = result_promise->get_future();
    std::unique_lock<decltype(m_locker)> lock(m_locker);

    m_tasks.emplace_back([fn = std::forward<Function>(fn),
                          tp = std::make_tuple(std::forward<Args>(args)...),
                          promise = std::move(result_promise)]() mutable {
        if constexpr (std::is_void_v<InvokeTaskType>) {
            try {
                std::apply(std::forward<Function>(fn), std::forward<decltype(tp)>(tp));
                promise->set_value();
            } catch (...) {
                promise->set_exception(std::current_exception());
            }
        } else {
            try {
                promise->set_value(std::apply(std::forward<Function>(fn), std::forward<decltype(tp)>(tp)));
            } catch (...) {
                promise->set_exception(std::current_exception());
            }
        }
    });
    lock.unlock();
    m_notifier.notify_one();
    return {true, std::move(result_future)};
}

}// namespace processing
}// namespace vk


#endif// VK_PROCESSING_TASK_QUEUE_HPP
