#include "runtime/include/processing/task_queue.hpp"

#include <gtest/gtest.h>

#include <thread>

namespace proc = runtime::processing;

// It's enough 500-510ms for Linux tests, but on MacOS it may
// take up to 700-800ms
TEST(task_queue, future_tasks)
{
    proc::task_queue task_queue(/*num_workers=*/2);

    std::vector<std::pair<bool, std::future<size_t>>> tasks;

    for (size_t i = 0; i < 1000; ++i) {
        tasks.emplace_back(task_queue.push_future_task([_i = i] {
            using namespace std::chrono_literals;
            std::this_thread::sleep_for(1ms);
            return _i;
        }));
    }

    auto start_time = std::chrono::system_clock::now();

    task_queue.start();
    task_queue.wait_for_completion();

    for (size_t i = 0; i < 10; ++i) {
        ASSERT_EQ(tasks[i].second.get(), i);
    }

    auto finish_time = std::chrono::system_clock::now();

    ASSERT_LT(finish_time - start_time, std::chrono::milliseconds(900));
}

TEST(task_queue, void_tasks)
{
    proc::task_queue task_queue(/*num_workers=*/2);

    std::vector<bool> successfully_completed_tasks;

    for (size_t i = 0; i < 1000; ++i) {
        successfully_completed_tasks.push_back(task_queue.push_void_task([] {
            using namespace std::chrono_literals;
            std::this_thread::sleep_for(1ms);
        }));
    }

    auto start_time = std::chrono::system_clock::now();

    task_queue.start();
    task_queue.wait_for_completion();

    for (bool task_flag : successfully_completed_tasks) {
        ASSERT_TRUE(task_flag);
    }

    auto finish_time = std::chrono::system_clock::now();

    ASSERT_LT(finish_time - start_time, std::chrono::milliseconds(900));
}

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
