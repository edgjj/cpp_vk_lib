#include "cpp_vk_lib/runtime/signal_handlers.hpp"
#include "cpp_vk_lib/runtime/setup_logger.hpp"
#include "cpp_vk_lib/runtime/net/network.hpp"
#include "cpp_vk_lib/vk/config/config.hpp"
#include "cpp_vk_lib/vk/methods/basic.hpp"
#include "cpp_vk_lib/vk/api_constants.hpp"

#include <future>

int main()
{
    runtime::network::init_shared_curl();

    constexpr char sender_config[] = R"__(
        {
          "api": {
            "access_token": "5c50bdfddd4e07326238f1c229f24bd8c91393865cf1e0fb6e522597f0ec4e3e1e21540e142b85811e80d",
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

    vk::config::load_string(sender_config);
    runtime::setup_signal_handlers();
    runtime::setup_logger(spdlog::level::level_enum::info);

    std::vector<std::thread> threads;

    const size_t total_messages = 25;
    constexpr size_t test_chat_id = vk::api_constants::chat_id_constant + 1;

    for (size_t i = 0; i < total_messages; ++i) {
        threads.emplace_back([i = i]{
            vk::method::messages::send(test_chat_id, std::to_string(i));
        });
    }
    for (auto& t : threads) {
        t.join();
    }
}
