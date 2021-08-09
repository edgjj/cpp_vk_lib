#ifndef VK_KEYBOARD_BUTTONS_TEXT_HPP
#define VK_KEYBOARD_BUTTONS_TEXT_HPP

#include "runtime/include/string_utils/string_utils.hpp"

#include "vk/include/keyboard/colors.hpp"

namespace vk {
namespace keyboard {
namespace button {

class text
{
public:
    text(color selected_color, std::string_view payload_data)
        : selected_color_(selected_color)
        , payload_data_(payload_data) {}

    std::string serialize() const
    {
        const char* color = keyboard::get_color(selected_color_);
        return runtime::string_utils::format(
            R"__({"action":{"type":"text","payload":"{\"button\":\"1\"}","label":"{}"},"color":"{}"})__",
            payload_data_,
            color);
    }

private:
    color selected_color_ = color::none;
    std::string payload_data_;
};

}// namespace button
}// namespace keyboard
}// namespace vk

#endif// VK_KEYBOARD_BUTTONS_TEXT_HPP
