#include "cpp_vk_lib/config/loader.hpp"

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
    "error_log_path": "/tmp/errors.log",
    "event_log_path": "/tmp/events.log"
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
    
    ASSERT_EQ(vk::config::error_logpath(), "/tmp/errors.log");
    ASSERT_EQ(vk::config::event_logpath(), "/tmp/events.log");
}

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
