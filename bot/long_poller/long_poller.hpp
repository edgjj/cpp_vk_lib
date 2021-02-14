#ifndef BOT_LONG_POLLER_H
#define BOT_LONG_POLLER_H

#include "api/long_poll_api.hpp"

#include "../handlers/message_handler.hpp"


class long_poller {
public:
    explicit long_poller() : data(api.server()) { }
    message_handler& get_message_handler() noexcept {
        return message_handler;
    }
    int run() {
        while (true) {
            auto events = api.listen(data);
            for (std::unique_ptr<vk::event::common>& event : events) {
                if (event->on_type("message_new")) {
                    api.queue([this, &event](){
                        message_handler.process(event->get_message_event());
                    });
                }
                data.ts = event->ts();
            }
            api.run();
        }
        return EXIT_SUCCESS;
    }
private:
    message_handler message_handler;
    vk::long_poll_api api;
    vk::long_poll_data data;
};

#endif // BOT_LONG_POLLER_H
