#ifndef VK_KEYBOARD_BUTTONS_VK_PAY_HPP
#define VK_KEYBOARD_BUTTONS_VK_PAY_HPP

#include "string_utils/string_utils.hpp"

namespace vk {
namespace keyboard {
namespace button {

class vk_pay
{
public:
    vk_pay(std::string_view hash)
        : m_hash(hash) {}

    std::string serialize() const
    {
        return string_utils::format(R"({"action":{"type":"vkpay","hash":"{}"}})", m_hash);
    }

private:
    std::string m_hash;
};
}// namespace button
}// namespace keyboard
}// namespace vk

#endif// VK_KEYBOARD_BUTTONS_VK_PAY_HPP
