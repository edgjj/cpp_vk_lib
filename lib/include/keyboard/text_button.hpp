#ifndef VK_TEXT_BUTTON_H
#define VK_TEXT_BUTTON_H

#include "keyboard/colors.hpp"
#include "string_util/string_util.hpp"


namespace vk {
namespace keyboard {

class text_button {
public:
  text_button(color selected_color_, std::string_view text_)
    : selected_color(selected_color_), text(text_.data()) { }
  std::string serialize() {
    const char* color(keyboard::get_color(selected_color));
    return
    string_util::format(
      R"({"action":{"type":"text","payload":"{\"button\":\"1\"}","label":"{}"},"color":"{}"})",
      text, color
    );
  }
private:
  color selected_color = color::none;
  const char* text;
};
} // namespace keyboard
} // namespace vk

#endif // VK_TEXT_BUTTON_H
