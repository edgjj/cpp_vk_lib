#include "vk/include/config/loader.hpp"

#include <gtest/gtest.h>

#include <fstream>

constexpr char sample_config[] = R"__(
{
  "api": {
    "access_token": "access_token",
    "user_token": "user_token"
  },
  "oauth": {
    "login": "login@gmail.com",
    "password": "password"
  },
  "environment": {
    "num_workers": 8,
    "log_path": "/tmp/bot.log"
  }
}
)__";

TEST(config, field_access)
{
    std::ofstream("config.json") << sample_config;

    vk::config::load("config.json");

    ASSERT_EQ(vk::config::access_token(), "access_token");
    ASSERT_EQ(vk::config::user_token(), "user_token");

    vk::config::set_user_token("new_token");

    ASSERT_EQ(vk::config::user_token(), "new_token");

    ASSERT_EQ(vk::config::username(), "login@gmail.com");
    ASSERT_EQ(vk::config::password(), "password");

    ASSERT_EQ(vk::config::num_workers(), 8);
    
    ASSERT_EQ(vk::config::log_path(), "/tmp/bot.log");
}

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
