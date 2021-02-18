#ifndef VK_OPEN_APP_BUTTON_H
#define VK_OPEN_APP_BUTTON_H

#include "string_utils/string_utils.hpp"


namespace vk {
namespace keyboard {

class open_app_button {
public:
  open_app_button(std::int64_t app_id_, std::int64_t owner_id_, std::string_view hash_, std::string_view label_)
    : app_id(app_id_), owner_id(owner_id_), hash(hash_.data()), label(label_.data()) { }
  std::string serialize() {
    return
    string_utils::format(
      R"({"action":{"type":"open_app","app_id":{},"owner_id":{},"hash":"{}","label":"{}"}})",
      app_id, owner_id, hash, label
    );
  }
private:
  std::int64_t app_id;
  std::int64_t owner_id;
  const char* hash;
  const char* label;
};
} // namespace keyboard
} // namespace vk

#endif // VK_OPEN_APP_BUTTON_H
