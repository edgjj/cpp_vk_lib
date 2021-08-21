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

#include "cpp_vk_lib/vk/attachment/attachment.hpp"
#include "cpp_vk_lib/vk/config/loader.hpp"
#include "cpp_vk_lib/vk/events/common_event.hpp"
#include "cpp_vk_lib/vk/events/attachment_handler.hpp"
#include "cpp_vk_lib/vk/events/action.hpp"
#include "cpp_vk_lib/vk/events/message_new.hpp"
#include "cpp_vk_lib/vk/events/wall_post_new.hpp"
#include "cpp_vk_lib/vk/events/wall_reply_new.hpp"
#include "cpp_vk_lib/vk/exception/error-inl.hpp"
#include "cpp_vk_lib/vk/keyboard/colors.hpp"
#include "cpp_vk_lib/vk/keyboard/flags.hpp"
#include "cpp_vk_lib/vk/keyboard/layout.hpp"
#include "cpp_vk_lib/vk/long_poll/long_poll.hpp"
#include "cpp_vk_lib/vk/oauth/client.hpp"

#endif// VK_COMMON_HPP
