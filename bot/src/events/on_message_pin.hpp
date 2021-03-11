#ifndef BOT_ON_MESSAGE_PIN_EVENT_H
#define BOT_ON_MESSAGE_PIN_EVENT_H

#include "events/message_new.hpp"
#include "methods/messages.hpp"
#include "string_utils/string_utils.hpp"


namespace bot {
namespace event {

class on_message_pin_event {
public:
  void execute(const vk::event::message_new& event) const {
    auto pinned = std::get<vk::action::chat_pin_message>(event.action());
    messages.send(event.peer_id(),
      vk::string_utils::format("Message was pinned with text: {}.", pinned.message));
  }
private:
  vk::method::messages messages{vk::method::messages::disable_mentions};
};

} // namespace event
} // namespace bot

#endif // BOT_ON_MESSAGE_PIN_EVENT_H
