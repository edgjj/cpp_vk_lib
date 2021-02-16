#ifndef VK_LOCATION_BUTTON_H
#define VK_LOCATION_BUTTON_H

#include "string_util/string_util.hpp"


namespace vk {
namespace keyboard {

class location_button {
public:
  std::string serialize() {
    return R"({"action":{"type":"location","payload":"{\"button\":\"1\"}"}})";
  }
};
} // namespace keyboard
} // namespace vk

#endif // VK_LOCATION_BUTTON_H
