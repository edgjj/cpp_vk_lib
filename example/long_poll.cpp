#include "vk/include/long_poll/long_poll.hpp"

#include "runtime/include/string_utils/string_utils.hpp"
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

void parse_command_line_args(int argc, char** argv)
{
    for (size_t i = 0; i < argc; ++i) {
        auto params = runtime::string_utils::split(argv[i], '=');
        if (params.size() % 2 != 0) {
            continue;
        }

        if (params[0] == "--log-level") {
            for (const char* level : {"off", "critical", "error", "warn", "info", "debug", "trace"}) {
                if (params[1] == level) {
                    vk::setup_logger(level);
                    break;
                }
            }
        }
    }
}

int main(int argc, char** argv)
{
    if (argc == 2 && strcmp(argv[1], "--help") == 0) {
        std::cerr <<
            "Usage:\n" <<
            "    long_poll_example (optional) --log-level=(off | critical | error | warn | info | debug | trace)\n" <<
            "Example:\n" <<
            "    long_poll_example --log-level=trace\n";
        return EXIT_SUCCESS;
    }

    vk::setup_logger("info");
    parse_command_line_args(argc, argv);
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
