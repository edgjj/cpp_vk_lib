#ifndef BOT_LONG_POLLER_H
#define BOT_LONG_POLLER_H

#include "cpp_vk_lib/long_poll/api.hpp"

#include "../handlers/message_handler.hpp"


namespace bot {

class long_poller {
public:
  explicit long_poller()
    : api()
    , data(api.server())
    , msg_handler()
  { }
  message_handler& get_message_handler() noexcept {
    return msg_handler;
  }
  int run() {
    static int c = 0;
    while (++ c < 5) {
      auto events = api.listen(data);
      for (auto& event : events) {
        api.on_event("message_new", *event, [this, &event]{
          msg_handler.process(event->get_message_event());
        });
      }
      api.run();
    }
    return EXIT_SUCCESS;
  }
private:
  vk::long_poll::api api;
  vk::long_poll::data data;
  message_handler msg_handler;
};

} // namespace bot

#endif // BOT_LONG_POLLER_H
