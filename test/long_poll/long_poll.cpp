#include "vk/include/long_poll/api.hpp"
#include "vk/include/methods/basic.hpp"

#include "vk/include/config/loader.hpp"
#include "vk/include/log_level.hpp"
#include "vk/include/methods/utility/utility.hpp"

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

int main()
{
    std::ofstream("config.json") << sample_config;
    vk::config::load("config.json");
    vk::log_level::trace();

    const std::size_t lp_timeout_secs = 60;

    vk::long_poll api;
    vk::long_poll_data data = api.server();

    while (true) {
        auto events = api.listen(data, lp_timeout_secs);

        for (auto& event : events) {
            api.on_event("message_new", event, [&event] {
                auto message_event = event.get_message_event();
                vk::method::messages::send(vk::method::utility::chat_id_constant + 1, "response");
            });
        }
        api.run();
    }
}
