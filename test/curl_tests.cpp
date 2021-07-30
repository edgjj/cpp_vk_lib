#include "runtime/include/net/network.hpp"

#include <gtest/gtest.h>

#include <regex>

TEST(curl, POST)
{
    try {
        const std::string received = runtime::network::request("https://www.example.com");
        if (received.empty()) {
            ASSERT_FALSE(true);
        } else {
            if (received.find("Example Domain") == std::string::npos) {
                ASSERT_FALSE(true);
            }
        }
    } catch (...) {
        ASSERT_FALSE(true);
    }
}

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
