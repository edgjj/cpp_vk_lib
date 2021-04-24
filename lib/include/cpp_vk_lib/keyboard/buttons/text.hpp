#ifndef VK_TEXT_BUTTON_H
#define VK_TEXT_BUTTON_H

#include "keyboard/colors.hpp"
#include "string_utils/string_utils.hpp"

namespace vk {
namespace keyboard {
namespace button {

class text
{
public:
    text(color selected_color, std::string_view text)
      : m_selected_color(selected_color)
      , m_payload_data(text)
    {}
    std::string serialize() const
    {
        const char* color(keyboard::get_color(m_selected_color));
        return string_utils::format(
            R"({"action":{"type":"text","payload":"{\"button\":\"1\"}","label":"{}"},"color":"{}"})",
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

#endif// VK_TEXT_BUTTON_H
