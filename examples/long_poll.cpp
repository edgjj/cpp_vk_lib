#include "runtime/include/string_utils/string_utils.hpp"

#include "vk/include/long_poll/long_poll.hpp"
#include "vk/include/config/loader.hpp"
#include "vk/include/events/message_new.hpp"
#include "vk/include/methods/basic.hpp"
#include "vk/include/setup_logger.hpp"

#include <iostream>

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

int main()
{
    vk::setup_logger("info");
    vk::config::load_string(sample_config);

    asio::io_context io_context;
    vk::long_poll api(io_context);

    while (true) {
        auto events = api.listen(/*timeout=*/60);
        for (auto& event : events) {
            api.on_event("message_new", event, [&event] {
                vk::event::message_new message_event = event.get_message_new();
                vk::method::messages::send(message_event.peer_id(), "response");
            });
        }
        api.run();
    }
}
