#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <condition_variable>
#include <future>
#include <deque>
#include <vector>

#include "misc/cppdefs.hpp"


namespace vk
{
namespace processing
{
class VK_EXPORT thread_pool
{
public:
    DISABLE_COPY(thread_pool)
    DISABLE_MOVE(thread_pool)
    thread_pool() = default;
    ~thread_pool()
    {
        finish();
    }

    template <typename _Function, typename _Result_of = std::result_of_t<_Function&()>>
    std::future<_Result_of> queue(_Function&& f);
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

template <typename _Function, typename _Result_of>
std::future<_Result_of> vk::processing::thread_pool::queue(_Function&& f)
{
    std::packaged_task<_Result_of()> task(std::forward<_Function>(f));
    auto future = task.get_future();
    {
        std::unique_lock<std::mutex> l(locker);
        worker.emplace_back(std::move(task));
    }
    condition.notify_one();

    return future;
}

#endif // VK_THREAD_POOL_H
