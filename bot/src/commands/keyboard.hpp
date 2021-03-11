#ifndef BOT_KEYBOARD_COMMAND_H
#define BOT_KEYBOARD_COMMAND_H

#include "cpp_vk_lib/events/message_new.hpp"
#include "cpp_vk_lib/keyboard/layout.hpp"
#include "cpp_vk_lib/methods/messages.hpp"

#include "../commands/base.hpp"


namespace bot {
namespace command {

class keyboard_command final : public base_command {
public:
  // vk::keyboard::layout has `none` flag by default, which corresponds to white color.
  explicit keyboard_command()
    : layout(std::make_unique<vk::keyboard::layout>(vk::keyboard::flag::in_line))
  {
    setup_keyboard();
  }
  void execute(const vk::event::message_new& event) const override {
    messages.send(event.peer_id(), "Here is keyboard: ", *layout);
  }
private:
  void setup_keyboard() {
    layout->add_row({
      vk::keyboard::button::text(vk::keyboard::color::blue, "Text 1"),
      vk::keyboard::button::text(vk::keyboard::color::blue, "Text 2")
    });
    layout->add_row({
      vk::keyboard::button::location()
    });
    layout->add_row({
      vk::keyboard::button::vk_pay("action=transfer-to-group&group_id=181108510&aid=10")
    });
  }

  std::unique_ptr<vk::keyboard::layout> layout;
  vk::method::messages messages{vk::method::messages::disable_mentions};
};

} // namespace command
} // namespace bot

#endif // BOT_KEYBOARD_COMMAND_H
