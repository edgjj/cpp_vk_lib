#ifndef VK_PAY_BUTTON_H
#define VK_PAY_BUTTON_H

#include "string_utils/string_utils.hpp"


namespace vk {
namespace keyboard {

class vk_pay_button {
public:
  vk_pay_button(std::string_view hash_)
    : hash(hash_.data()) { }
  std::string serialize() {
    return
    string_utils::format(
      R"({"action":{"type":"vkpay","hash":"{}"}})",
      hash
    );
  }
private:
  const char* hash;
};
} // namespace keyboard
} // namespace vk

#endif // VK_PAY_BUTTON_H
