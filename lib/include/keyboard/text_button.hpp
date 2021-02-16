#ifndef VK_TEXT_BUTTON_H
#define VK_TEXT_BUTTON_H

#include "string_util/string_util.hpp"


namespace vk {
namespace keyboard {

class text_button {
public:
  text_button(std::string_view text_)
    : text(text_.data()) { }
  std::string serialize() {
    return
    string_util::format(
      R"({"action":{"type":"text","payload":"{\"button\":\"1\"}","label":"{}"},"color":"negative"})",
      text
    );
  }
private:
  const char* text;
};
} // namespace keyboard
} // namespace vk

#endif // VK_TEXT_BUTTON_H
