#include "cpp_vk_lib/runtime/net/network.hpp"
#include "cpp_vk_lib/vk/setup_logger.hpp"
#include "cpp_vk_lib/vk/methods/basic.hpp"
#include "cpp_vk_lib/vk/methods/constructor.hpp"

#include <gtest/gtest.h>
#include "simdjson.h"

#include <fstream>
#include <future>
#include <filesystem>

TEST(curl, POST)
{
    const auto received = runtime::network::request("https://www.example.com");
    if (received.error()) {
        ASSERT_FALSE(true);
    }
    const auto result = received.value();
    if (result.empty()) {
        ASSERT_FALSE(true);
    } else {
        if (result.find("Example Domain") == std::string::npos) {
            ASSERT_FALSE(true);
        }
    }
}

TEST(curl, POST_speed_test)
{
    constexpr std::string_view url = "https://www.example.com";
    for (size_t i = 0; i < 5; ++i) {
        runtime::network::request(url);
    }
}

TEST(curl, POST_multithreaded)
{
    std::vector<std::pair<std::thread, std::future<std::string>>> threads;
    for (size_t i = 0; i < std::thread::hardware_concurrency(); ++i) {
        std::promise<std::string> promise;
        std::future <std::string> future = promise.get_future();
        std::thread thread([promise = std::move(promise)]() mutable {
            const auto received = runtime::network::request("https://www.example.com");
            if (received.error()) {
                ASSERT_FALSE(true);
            }
            promise.set_value(received.value());
        });
        threads.push_back(std::make_pair(std::move(thread), std::move(future)));
    }
    std::vector<std::string> responses;
    for (auto& el : threads) {
        auto thread = std::move(el.first);
        auto future = std::move(el.second);
        responses.emplace_back(future.get());
        thread.join();
    }
    ASSERT_TRUE(std::adjacent_find(responses.begin(), responses.end(), std::not_equal_to<>()) == responses.end());
}

TEST(curl, download_to_file)
{
    if (runtime::network::download("buffer", "https://psv4.userapi.com/c536236/u561321493/docs/d33/f7cc086dba89/Korone_Headbob_gif.gif?extra=kghQXdwaja1KksbzxIbPteeCO2VFb4RdZLH2alAw1w_HNhwc9JZzw31uoVBp_Ntfo6jP1XB-A8i4KWPB9QKt8DdW_J4sB9gz2Fk6X-LMqxIiI2uYErb9ACbc2Ox7LCMY5H97zSf47nvCy27W9GTW2BQm") != 0) {
        FAIL() << "Failed to download to file";
    }
    std::remove("buffer");
}

TEST(curl, download_to_buffer)
{
    const std::string_view url = "https://psv4.userapi.com/c536236/u561321493/docs/d33/f7cc086dba89/Korone_Headbob_gif.gif?extra=kghQXdwaja1KksbzxIbPteeCO2VFb4RdZLH2alAw1w_HNhwc9JZzw31uoVBp_Ntfo6jP1XB-A8i4KWPB9QKt8DdW_J4sB9gz2Fk6X-LMqxIiI2uYErb9ACbc2Ox7LCMY5H97zSf47nvCy27W9GTW2BQm";
    const size_t estimated_capacity = 700000;
    if (std::vector<uint8_t> raw_buffer; runtime::network::download(raw_buffer, url, estimated_capacity) != 0) {
        FAIL() << "Failed to download to buffer";
    }
}

TEST(curl, download_compare)
{
    const char url[] = "https://www.example.com";
    runtime::network::download("file", url);
    std::ostringstream ss;
    ss << std::ifstream("file").rdbuf();
    const std::string& streambuf = ss.str();
    std::vector<uint8_t> file_buffer(streambuf.begin(), streambuf.end());

    std::vector<uint8_t> raw_buffer;
    const size_t estimated_capacity = 500;
    runtime::network::download(raw_buffer, url, estimated_capacity);

    ASSERT_EQ(file_buffer, raw_buffer);

    std::remove("file");
}
