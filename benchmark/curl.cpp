#include "cpp_vk_lib/runtime/net/network.hpp"
#include "cpp_vk_lib/runtime/setup_logger.hpp"
#include "cpp_vk_lib/runtime/signal_handlers.hpp"
#include "cpp_vk_lib/vk/config/config.hpp"
#include "cpp_vk_lib/runtime/string_utils/implementation/format.hpp"

#include <functional>
#include <chrono>
#include <iostream>
#include <thread>
#include <future>
#include <numeric>

float get_elapsed_seconds_for_executor(std::function<void()> executor)
{
    auto start = std::chrono::steady_clock::now();
    executor();
    auto time_spent = std::chrono::steady_clock::now() - start;
    return std::chrono::duration_cast<std::chrono::duration<float>>(time_spent).count();
}

void create_curl_payload(size_t thread_count, size_t iterations, std::vector<float>& outputs, std::function<void()> executor)
{
    for (size_t total = 0; total < iterations; ++total) {
        std::vector<std::pair<std::thread, std::future<float>>> threads;
        for (size_t i = 0; i < thread_count; ++i) {
            std::promise<float> promise;
            std::future <float> future = promise.get_future();
            std::thread thread([p = std::move(promise), &executor]() mutable {
                float seconds = get_elapsed_seconds_for_executor(executor);
                p.set_value(seconds);
            });
            threads.emplace_back(std::move(thread), std::move(future));
        }

        for (auto& el : threads) {
            auto thread = std::move(el.first);
            auto future = std::move(el.second);
            outputs.push_back(future.get());
            thread.join();
        }
    }
}

int main() {
    namespace net = runtime::network;
    std::vector<float> require_data_curl_times;
    std::vector<float> omit_data_curl_times;

    runtime::setup_signal_handlers();
    net::init_shared_curl();

    const size_t threads = 2;
    const size_t iterations = 10;
    std::cout << "execute " << threads * iterations << " require_data requests..." << std::endl;
    create_curl_payload(threads, iterations, require_data_curl_times, []{
        net::request(net::require_data, "https://www.google.com");
    });
    std::cout << "execute " << threads * iterations << " omit_data requests..." << std::endl;
    create_curl_payload(threads, iterations, omit_data_curl_times, []{
        net::request(net::omit_data, "https://www.google.com");
    });

    std::cout << "require data average time: " << std::accumulate(
        require_data_curl_times.begin(),
        require_data_curl_times.end(),
        0.0f) / static_cast<float>(require_data_curl_times.size()) << std::endl;

    std::cout << "omit data average time:    " << std::accumulate(
        omit_data_curl_times.begin(),
        omit_data_curl_times.end(),
        0.0f) / static_cast<float>(omit_data_curl_times.size()) << std::endl;
}
