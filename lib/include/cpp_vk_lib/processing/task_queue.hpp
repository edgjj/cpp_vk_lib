#ifndef VK_TASK_QUEUE_H
#define VK_TASK_QUEUE_H

#include <condition_variable>
#include <future>
#include <deque>
#include <vector>


namespace vk {
namespace processing {

class task_queue {
public:
  task_queue(const task_queue&) = delete;
  task_queue(task_queue&&) = delete;
  task_queue& operator=(const task_queue&) = delete;
  task_queue& operator=(task_queue&&) = delete;
  task_queue() : locker(), condition(), tasks(), workers() { }
 ~task_queue();

  template <typename Function, typename Result_Of = std::result_of_t<Function&()>>
  void queue(Function&& f);
  void start(std::size_t num_threads = std::thread::hardware_concurrency());
  void cancel_pending();
  void finish();

private:
  void thread_task();

  std::mutex locker;
  std::condition_variable condition;
  std::deque<std::packaged_task<void()>> tasks;
  std::vector<std::future<void>> workers;
};
} // namespace processing
} // namespace vk

template <typename Function, typename Result_Of>
void vk::processing::task_queue::queue(Function&& f) {
  std::packaged_task<Result_Of()> task(std::forward<Function>(f));
  std::unique_lock<std::mutex> local_locker(locker);
  tasks.emplace_back(std::move(task));
  local_locker.unlock();
  condition.notify_one();
}

#endif // VK_TASK_QUEUE_H
