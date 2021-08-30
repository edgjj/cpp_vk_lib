#include "cpp_vk_lib/runtime/net/network.hpp"
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

void create_curl_payload(std::vector<float>& outputs, std::function<void()> executor)
{
    for (size_t total = 0; total < 1; ++total) {
        std::vector<std::pair<std::thread, std::future<float>>> threads;
        for (size_t i = 0; i < std::thread::hardware_concurrency(); ++i) {
            std::promise<float> promise;
            std::future <float> future = promise.get_future();
            std::thread thread([p = std::move(promise), &executor]() mutable {
                float seconds = get_elapsed_seconds_for_executor(executor);
                p.set_value(seconds);
            });
            threads.push_back(std::make_pair(std::move(thread), std::move(future)));
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

    net::init_shared_curl();

    std::cout << "execute " << std::thread::hardware_concurrency() * 8 << " require_data requests..." << std::endl;
    create_curl_payload(require_data_curl_times, []{
        net::request(net::require_data, "https://www.google.com");
    });
    std::cout << "execute " << std::thread::hardware_concurrency() * 8 << " omit_data requests..." << std::endl;
    create_curl_payload(omit_data_curl_times, []{
        net::request(net::omit_data, "https://www.google.com");
    });

    std::cout << "require data average time: " << std::accumulate(
        require_data_curl_times.begin(),
        require_data_curl_times.end(),
        0.0f) / require_data_curl_times.size() << std::endl;

    std::cout << "omit data average time:    " << std::accumulate(
        omit_data_curl_times.begin(),
        omit_data_curl_times.end(),
        0.0f) / omit_data_curl_times.size() << std::endl;
}
