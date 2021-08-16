/*!
 * @mainpage
 *
 * C++ VK library
 *
 * CMake options:
 *
 * Sample code
 *
 * @code
    #include "cpp_vk_lib/vk/include/config/loader.hpp"
    #include "cpp_vk_lib/vk/include/events/message_new.hpp"
    #include "cpp_vk_lib/vk/include/long_poll/long_poll.hpp"
    #include "cpp_vk_lib/vk/include/methods/basic.hpp"
    #include "cpp_vk_lib/vk/include/setup_logger.hpp"

    int main(int argc, char* argv[]) {
      if (argc != 2) {
        std::cerr << "Program requires path to config as the only argument." << std::endl;
        return 1;
      }

      vk::config::load(argv[1]);
      vk::setup_logger("trace");

      asio::io_context io_context;
      vk::long_poll api(io_context);

      while (true) {
        auto events = api.listen();
        for (auto& event : events) {
          api.on_event("message_new", event, [&event] {
            auto message_event = event.get_message_new();
            vk::method::messages::send(message_event.peer_id(), "response");
          });
        }
      }
    }
 * @endcode
 *
 * Please, check the
 * [README.md](https://github.com/threadpoolexecutor/cpp_vk_lib).
 */

#ifndef VK_COMMON_HPP
#define VK_COMMON_HPP

#include "vk/include/attachment/base.hpp"
#include "vk/include/config/loader.hpp"
#include "vk/include/document/common.hpp"
#include "vk/include/events/common_event.hpp"
#include "vk/include/events/handlers/attachment_handler.hpp"
#include "vk/include/events/handlers/message_action_handler.hpp"
#include "vk/include/events/message_new.hpp"
#include "vk/include/events/wall_post_new.hpp"
#include "vk/include/events/wall_reply_new.hpp"
#include "vk/include/exception/error-inl.hpp"
#include "vk/include/keyboard/colors.hpp"
#include "vk/include/keyboard/flags.hpp"
#include "vk/include/keyboard/layout.hpp"
#include "vk/include/long_poll/long_poll.hpp"
#include "vk/include/oauth/client.hpp"

#endif// VK_COMMON_HPP
