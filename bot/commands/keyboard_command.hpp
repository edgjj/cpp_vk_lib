#ifndef BOT_KEYBOARD_COMMAND_H
#define BOT_KEYBOARD_COMMAND_H

#include "events/message_new.hpp"
#include "keyboard/layout.hpp"
#include "keyboard/flags.hpp"
#include "methods/messages.hpp"

#include "../commands/base_command.hpp"


class keyboard_command final : public base_command {
public:
  // vk::keyboard::layout has `none` flag by default, which corresponds to white.
  explicit keyboard_command()
    : layout(std::make_unique<vk::keyboard::layout>(vk::keyboard::flag::in_line))
  {
    setup_keyboard();
  }
  void execute(vk::event::message_new& event) override {
    messages.send(event.peer_id(), "Here is keyboard: ", *layout);
  }
private:
  void setup_keyboard() {
    layout->add_row({
      vk::keyboard::text_button(vk::keyboard::color::blue, "Text 1"),
      vk::keyboard::text_button(vk::keyboard::color::blue, "Text 2")
    });
    layout->add_row({
      vk::keyboard::location_button()
    });
    layout->add_row({
      vk::keyboard::vk_pay_button("action=transfer-to-group&group_id=181108510&aid=10")
    });
  }

  std::unique_ptr<vk::keyboard::layout> layout;
  vk::method::messages messages;
};

#endif // BOT_KEYBOARD_COMMAND_H
