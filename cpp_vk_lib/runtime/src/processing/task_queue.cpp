#include "runtime/include/processing/task_queue.hpp"

#include <sstream>

runtime::processing::task_queue::task_queue(size_t num_workers)
    : m_num_workers(num_workers)
    , m_running(false)
    , m_stop_requested(false)
{
    set_default_exception_handler();
}


runtime::processing::task_queue& runtime::processing::task_queue::set_exception_handler(task_queue::exception_callback_t handler)
{
    m_on_exception = std::move(handler);
    return *this;
}

runtime::processing::task_queue& runtime::processing::task_queue::set_num_workers(size_t num)
{
    if (m_running) {
        throw std::runtime_error("Attempt to change number of workers while running");
    }

    m_num_workers = num;
    return *this;
}

void runtime::processing::task_queue::start()
{
    if (m_running) {
        return;
    }
    m_running = true;
    init_workers(m_num_workers);
}

void runtime::processing::task_queue::stop()
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

void runtime::processing::task_queue::wait_for_completion()
{
    if (!m_running) { return; }

    m_stop_policy = stop_policy::wait_for_queue_completion;
    stop();

    m_stop_policy = stop_policy::stop_after_current_task;
    start();
}

runtime::processing::task_queue::~task_queue()
{
    stop();
}

void runtime::processing::task_queue::set_default_exception_handler()
{
    m_on_exception = [](std::exception_ptr ex_ptr) -> void {
        if (!ex_ptr) { return; }

        try {
            std::rethrow_exception(ex_ptr);
        } catch (std::exception& ex) {
            std::ostringstream stream;
            stream << std::this_thread::get_id();
            spdlog::warn("task queue: exception from thread {}: {}", stream.str(), ex.what());
        } catch (...) {
            spdlog::warn("task queue: unknown exception");
        }
    };
}

void runtime::processing::task_queue::init_workers(size_t num)
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
