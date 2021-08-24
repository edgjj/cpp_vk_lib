#include "api_tests.hpp"
#include "attachment_tests.hpp"
#include "config_tests.hpp"
#include "curl_tests.hpp"
#include "error_code_tests.hpp"
#include "event_tests.hpp"
#include "exception_tests.hpp"
#include "keyboard_tests.hpp"
#include "result_tests.hpp"
#include "string_util_tests.hpp"

int main(int argc, char* argv[])
{
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

    vk::setup_logger(spdlog::level::level_enum::trace);
    vk::config::load_string(sample_config);

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
