#ifndef VK_KEYBOARD_COLORS_H
#define VK_KEYBOARD_COLORS_H

namespace vk {
namespace keyboard {
namespace color_data {

static inline constexpr char red[] = "negative";
static inline constexpr char green[] = "positive";
static inline constexpr char blue[] = "primary";
static inline constexpr char white[] = "secondary";
}// namespace color_data

enum class color : unsigned char
{
    none = (1 << 0),
    red = (1 << 1),
    green = (1 << 2),
    blue = (1 << 3),
    white = (1 << 4)
};

inline const char* get_color(color c) noexcept
{
    switch (c)
    {
        case color::red:
            return color_data::red;
            break;
        case color::green:
            return color_data::green;
            break;
        case color::blue:
            return color_data::blue;
            break;
        default:
            return color_data::white;
            break;
    }
}
}// namespace keyboard
}// namespace vk

#endif// VK_KEYBOARD_COLORS_H
