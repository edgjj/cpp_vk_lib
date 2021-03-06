#ifndef BOT_HIDE_KEYBOARD_COMMAND_H
#define BOT_HIDE_KEYBOARD_COMMAND_H

#include "events/message_new.hpp"
#include "keyboard/layout.hpp"
#include "methods/messages.hpp"

#include "../commands/base.hpp"


namespace bot {
namespace command {

class hide_keyboard_command final : public base_command {
public:
  void execute(const vk::event::message_new& event) const override {
    // You should to pass empty layout to hide keyboard.
    vk::keyboard::layout layout;
    messages.send(event.peer_id(), "Keyboard was hidden", layout);
  }
private:
  vk::method::messages messages{vk::method::messages::disable_mentions};
};

} // namespace command
} // namespace bot

#endif // BOT_HIDE_KEYBOARD_COMMAND_H
