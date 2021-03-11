#ifndef BOT_LONG_POLLER_H
#define BOT_LONG_POLLER_H

#include "cpp_vk_lib/long_poll/api.hpp"

#include "../handlers/message_handler.hpp"


namespace bot {

class long_poller {
public:
  explicit long_poller() : data(api.server())
  { }
  message_handler& get_message_handler() noexcept {
    return msg_handler;
  }
  int run() {
    while (true) {
      auto events = api.listen(data);
      for (auto& event : events) {
        if (event->on_type("message_new")) {
          api.queue([this, &event](){
            msg_handler.process(event->get_message_event());
          });
        }
      }
      api.run();
    }
    return EXIT_SUCCESS;
  }
private:
  message_handler msg_handler;
  vk::long_poll::api api;
  vk::long_poll::data data;
};

} // namespace bot

#endif // BOT_LONG_POLLER_H
