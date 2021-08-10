#include "vk/include/long_poll/api.hpp"
#include "vk/include/methods/basic.hpp"
#include "vk/include/events/message_new.hpp"

#include "vk/include/config/loader.hpp"
#include "vk/include/log_level.hpp"

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

/*!
 *  int main()
 *  {
 *      vk::config::load_string(sample_config);
 *      vk::log_level::trace();
 *      const std::size_t lp_timeout_secs = 60;
 *      asio::io_context io_context;
 *
 *      vk::group_long_poll group_lp(io_context);
 *
 *      group_lp.on_event<vk::event::message_new>([]{
 *          vk::method::messages::send(message_event.peer_id(), "message_new");
 *      });
 *      group_lp.on_event<vk::event::wall_post_new>([]{
 *          vk::method::messages::send(message_event.peer_id(), "wall_post_new");
 *      });
 *
 *      return group_lp.run();
 *  }
 */

int main()
{
    vk::config::load_string(sample_config);
    vk::log_level::trace();

    const std::size_t lp_timeout_secs = 60;
    asio::io_context io_context;

    vk::long_poll api(io_context);
    vk::long_poll_data data = api.server();

    while (true) {
        auto events = api.listen(data, lp_timeout_secs);

        for (auto& event : events) {
            api.on_event("message_new", event, [&event] {
                vk::event::message_new message_event = event.get_message_new();
                vk::method::messages::send(message_event.peer_id(), "response");
            });
        }
        api.run();
    }
}
