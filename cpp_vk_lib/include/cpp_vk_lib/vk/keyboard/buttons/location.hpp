#ifndef VK_KEYBOARD_BUTTONS_LOCATION_HPP
#define VK_KEYBOARD_BUTTONS_LOCATION_HPP

#include <string>

namespace vk::keyboard::button {

class location
{
public:
    const char* serialize() const noexcept
    {
        return R"__({"action":{"type":"location","payload":"{\"button\":\"1\"}"}})__";
    }
};

}// namespace vk::keyboard::button

#endif// VK_KEYBOARD_BUTTONS_LOCATION_HPP
