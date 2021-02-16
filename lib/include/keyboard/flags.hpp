#ifndef VK_KEYBOARD_FLAGS_H
#define VK_KEYBOARD_FLAGS_H


namespace vk {
namespace keyboard {

enum flag : unsigned char {
  in_line   = (1 << 0),
  one_time  = (1 << 1)
};
} // namespace keyboard
} // namespace vk

#endif // VK_KEYBOARD_FLAGS_H
