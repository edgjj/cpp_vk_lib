#include "runtime/include/net/network.hpp"
#include "vk/include/setup_logger.hpp"

#include <gtest/gtest.h>

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

TEST(curl, download)
{
    try {
        runtime::network::download("buffer", "https://vk.com/doc499047616_610588168?hash=34afd2c8be4fd1867d&dl=GA:1628920721:b81d762eaaeeea9d8a&api=1&no_preview=1");
    } catch (std::exception& err) {
        printf("error: %s\n", err.what());
        ASSERT_FALSE(true);
    }
    ASSERT_TRUE(true);
    std::remove("buffer");
}

int main(int argc, char* argv[])
{
    vk::setup_logger("trace");

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
