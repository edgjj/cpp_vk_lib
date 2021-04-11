#ifndef VK_TEXT_BUTTON_H
#define VK_TEXT_BUTTON_H

#include "keyboard/colors.hpp"
#include "string_utils/string_utils.hpp"

namespace vk {
namespace keyboard {
namespace button {

class text {
public:
  text(color selected_color_, std::string_view text_)
    : selected_color(selected_color_)
    , payload_data(text_) {}
  std::string serialize() const {
    const char* color(keyboard::get_color(selected_color));
    return string_utils::format(
        R"({"action":{"type":"text","payload":"{\"button\":\"1\"}","label":"{}"},"color":"{}"})",
        payload_data,
        color);
  }

private:
  color selected_color = color::none;
  std::string payload_data;
};
}// namespace button
}// namespace keyboard
}// namespace vk

#endif// VK_TEXT_BUTTON_H
