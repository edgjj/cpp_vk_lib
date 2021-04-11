#ifndef VK_LOCATION_BUTTON_H
#define VK_LOCATION_BUTTON_H

#include <string>

namespace vk {
namespace keyboard {
namespace button {

class location {
public:
  std::string serialize() const {
    return R"({"action":{"type":"location","payload":"{\"button\":\"1\"}"}})";
  }
};
}// namespace button
}// namespace keyboard
}// namespace vk

#endif// VK_LOCATION_BUTTON_H
