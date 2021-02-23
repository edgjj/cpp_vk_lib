#include "processing/task_queue.hpp"


vk::processing::task_queue::~task_queue() {
  finish();
}

void vk::processing::task_queue::start(std::size_t num_threads) {
  for (std::size_t i = 0; i < num_threads; i++) {
    workers.push_back(
      std::async(
        std::launch::async,
        [this]{ thread_task(); }
      )
    );
  }
}

void vk::processing::task_queue::cancel_pending() {
  std::unique_lock<decltype(locker)> local_locker(locker);
  tasks.clear();
}

void vk::processing::task_queue::finish() {
  std::unique_lock<decltype(locker)> local_locker(locker);
  for ([[maybe_unused]] auto&& unused : workers)
    tasks.push_back({ });
  local_locker.unlock();
  condition.notify_all();
  workers.clear();
}

void vk::processing::task_queue::thread_task() {
  while (true) {
    std::packaged_task<void()> task;
    std::unique_lock<decltype(locker)> local_locker(locker);
    if (tasks.empty())
      condition.wait(local_locker, [&]{ return !tasks.empty(); });
    task = std::move(tasks.front());
    tasks.pop_front();
    local_locker.unlock();
    if (!task.valid())
      return;
    task();
  }
}
