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
        : m_selected_color(selected_color)
        , m_payload_data(payload_data) {}

    std::string serialize() const
    {
        const char* color = keyboard::get_color(m_selected_color);
        return runtime::string_utils::format(
            R"__({"action":{"type":"text","payload":"{\"button\":\"1\"}","label":"{}"},"color":"{}"})__",
            m_payload_data,
            color);
    }

private:
    color m_selected_color = color::none;
    std::string m_payload_data;
};

}// namespace button
}// namespace keyboard
}// namespace vk

#endif// VK_KEYBOARD_BUTTONS_TEXT_HPP
