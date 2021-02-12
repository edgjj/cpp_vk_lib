#include "processing/thread_pool.hpp"


void vk::processing::thread_pool::start(std::size_t num_threads) {
    for (std::size_t i = 0; i < num_threads; i++) {
        finished.push_back(
            std::async(
                std::launch::async,
                [this]{ thread_task(); }
            )
        );
    }
}

void vk::processing::thread_pool::abort() {
    cancel_pending();
    finish();
}

void vk::processing::thread_pool::cancel_pending() {
    std::unique_lock<decltype(locker)> lock(locker);
    worker.clear();
}

void vk::processing::thread_pool::finish() {
    {
        std::unique_lock<decltype(locker)> lock(locker);
        for ([[maybe_unused]] auto&& unused : finished) {
            worker.push_back({ });
        }
    }
    condition.notify_all();
    finished.clear();
}

void vk::processing::thread_pool::thread_task() {
    while (true) {
        std::packaged_task<void()> task; {
            std::unique_lock<decltype(locker)> l(locker);
            if (worker.empty()) {
                condition.wait(l, [&]{ return !worker.empty(); });
            }
            task = std::move(worker.front());
            worker.pop_front();
        }
        if (!task.valid()) { return; }
        task();
    }
}
