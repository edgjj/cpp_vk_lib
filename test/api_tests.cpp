#include "vk/include/methods/utility/message_constructor.hpp"

#include "vk/include/config/loader.hpp"
#include "vk/include/setup_logger.hpp"

#include <gtest/gtest.h>

#include <fstream>

constexpr char sample_config[] = R"__(
    {
      "api": {
        "access_token": "7483c78eba756697ae4727e5d255d7782226d8bf4dc1a87924897e23278fddd46512c759c960a6468e4cf",
        "user_token": "not used"
      },
      "oauth": {
        "login": "not used",
        "password": "not used"
      },
      "environment": {
        "num_workers": 8,
        "log_path": "logs.txt"
      }
    }
)__";

constexpr size_t test_chat_id = vk::method::utility::chat_id_constant + 1;

TEST(methods, method_construct)
{
    vk::method::group_constructor constructor;
    constructor
        .method("messages.send")
        .param("peer_id", std::to_string(test_chat_id))
        .param("text", "methods::method_construct")
        .perform_request();
}

int main(int argc, char* argv[])
{
    vk::setup_logger("trace");

    std::ofstream("config.json") << sample_config;
    vk::config::load("config.json");

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
