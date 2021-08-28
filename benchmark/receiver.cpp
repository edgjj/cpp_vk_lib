#include "cpp_vk_lib/runtime/signal_handlers.hpp"
#include "cpp_vk_lib/runtime/setup_logger.hpp"
#include "cpp_vk_lib/vk/config/config.hpp"
#include "cpp_vk_lib/vk/methods/basic.hpp"
#include "cpp_vk_lib/vk/api_constants.hpp"
#include "cpp_vk_lib/vk/long_poll/long_poll.hpp"
#include "cpp_vk_lib/vk/events/message_new.hpp"

#include <iostream>

int main()
{
    constexpr char receiver_config[] = R"__(
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

    vk::config::load_string(receiver_config);
    runtime::setup_signal_handlers();
    runtime::setup_logger(spdlog::level::level_enum::info);

    asio::io_context io_context;
    vk::long_poll api(io_context);

    const size_t total_messages = 25;
    bool is_time_set = false;
    std::chrono::system_clock::time_point start;
    std::atomic<size_t> messages_sent = 0;

    while (true) {
        auto events = api.listen();
        if (!is_time_set) {
            start = std::chrono::high_resolution_clock::now();
            is_time_set = true;
        }
        for (const auto& event : events) {
            api.on_event("message_new", event, [&event] {
                vk::event::message_new message_event = event.get_message_new();
                vk::method::messages::send(message_event.peer_id(), "response");
            });
            ++messages_sent;
        }
        api.run();
        if (messages_sent == total_messages) {
            break;
        }
    }

    auto time_spent = std::chrono::high_resolution_clock::now() - start;
    std::string info;
    info += std::to_string(std::chrono::duration_cast<std::chrono::duration<float>>(time_spent).count());
    info += " s., ";
    info += std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(time_spent).count());
    info += " ms. (";
    info += std::to_string(total_messages / std::chrono::duration_cast<std::chrono::duration<float>>(time_spent).count());
    info += "/s.)";
    std::cout << info << std::endl;

    if (messages_sent != total_messages) {
        std::cerr << "ERROR: expected " << total_messages << " to send, but " << messages_sent << " was actually sended!\n";
        return -1;
    }
}
