#include "runtime/include/string_utils/string_utils.hpp"

#include "vk/include/long_poll/long_poll.hpp"
#include "vk/include/config/loader.hpp"
#include "vk/include/events/message_new.hpp"
#include "vk/include/methods/basic.hpp"
#include "vk/include/setup_logger.hpp"

#include <iostream>

int main(int argc, char* argv[])
{
    if (argc != 2) {
        std::cerr << "Usage: ./long_poll <config.json>" << std::endl;
        return 1;
    }

    vk::setup_logger("trace");
    vk::config::load(argv[1]);

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
    return 0;
}
