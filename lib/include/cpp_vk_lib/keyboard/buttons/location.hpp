#ifndef VK_KEYBOARD_BUTTONS_LOCATION_HPP
#define VK_KEYBOARD_BUTTONS_LOCATION_HPP

#include <string>

namespace vk {
namespace keyboard {
namespace button {

class location
{
public:
    const char* serialize() const noexcept
    {
        return R"__({"action":{"type":"location","payload":"{\"button\":\"1\"}"}})__";
    }
};

}// namespace button
}// namespace keyboard
}// namespace vk

#endif// VK_KEYBOARD_BUTTONS_LOCATION_HPP
