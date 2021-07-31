#include "runtime/include/processing/task_queue.hpp"

#include <gtest/gtest.h>

#include <thread>

namespace proc = runtime::processing;

TEST(task_queue, future_tasks)
{
#ifndef __APPLE__
    proc::task_queue task_queue;

    std::vector<std::pair<bool, std::future<size_t>>> tasks;

    for (size_t i = 0; i < 1000; ++i) {
        auto future = task_queue.push_future_task([i]{
            using namespace std::chrono_literals;
            std::this_thread::sleep_for(1ms);
            return i;
        });
        tasks.push_back(std::move(future));
    }

    auto start_time = std::chrono::system_clock::now();

    task_queue.start();
    task_queue.wait_for_completion();

    auto finish_time = std::chrono::system_clock::now();

    for (size_t i = 0; i < 1000; ++i) {
        ASSERT_EQ(tasks[i].second.get(), i);
    }

    ASSERT_LT(finish_time - start_time, std::chrono::milliseconds(1100 / std::thread::hardware_concurrency()));
#endif // __APPLE__
}

TEST(task_queue, void_tasks)
{
#ifndef __APPLE__
    proc::task_queue task_queue;

    std::vector<bool> successfully_completed_tasks;

    for (size_t i = 0; i < 1000; ++i) {
        bool task_status = task_queue.push_void_task([]{
            using namespace std::chrono_literals;
            std::this_thread::sleep_for(1ms);
        });

        successfully_completed_tasks.push_back(task_status);
    }

    auto start_time = std::chrono::system_clock::now();

    task_queue.start();
    task_queue.wait_for_completion();

    auto finish_time = std::chrono::system_clock::now();

    for (bool task_flag : successfully_completed_tasks) {
        ASSERT_TRUE(task_flag);
    }

    ASSERT_LT(finish_time - start_time, std::chrono::milliseconds(1100 / std::thread::hardware_concurrency()));
#endif // __APPLE__
}

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
