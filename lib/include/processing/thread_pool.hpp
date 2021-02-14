#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <condition_variable>
#include <future>
#include <deque>
#include <vector>

#include "misc/cppdefs.hpp"


namespace vk {
namespace processing {
class vk_export thread_pool {
public:
    disable_copy(thread_pool)
    disable_move(thread_pool)
    thread_pool() = default;
    ~thread_pool() { finish(); }

    template <typename function, typename result_of = std::result_of_t<function&()>>
    std::future<result_of> queue(function&& f);
    void start(std::size_t num_threads = 1);
    void abort();
    void cancel_pending();
    void finish();

private:
    void thread_task();

    std::mutex locker;
    std::condition_variable condition;
    std::deque<std::packaged_task<void()>> worker;
    std::vector<std::future<void>> finished;
};
} // namespace processing
} // namespace vk

template <typename function, typename result_of>
std::future<result_of> vk::processing::thread_pool::queue(function&& f) {
    std::packaged_task<result_of()> task(std::forward<function>(f));
    auto future = task.get_future(); {
        std::unique_lock<std::mutex> l(locker);
        worker.emplace_back(std::move(task));
    }
    condition.notify_one();

    return future;
}

#endif // VK_THREAD_POOL_H
