#ifndef VK_KEYBOARD_LAYOUT_H
#define VK_KEYBOARD_LAYOUT_H

#include <vector>
#include <variant>
#include <initializer_list>

#include "keyboard/open_app_button.hpp"
#include "keyboard/text_button.hpp"
#include "keyboard/vk_pay_button.hpp"


namespace vk {
namespace keyboard {

using any_button = std::variant<
  text_button,
  vk_pay_button,
  open_app_button
>;

class layout {
public:
  void add_row(const std::vector<any_button>& row) {
    buttons.push_back(row);
  }
  std::string serialize() const {
    std::string serialized;

    serialized.append(R"json("buttons":)json");
    serialized.push_back('[');

    std::vector<std::string> serialized_buttons;
    std::vector<std::string> serialized_rows;

    for (auto&& row : buttons) {
      for (auto&& any_button : row) {
        if (has_type<text_button>(any_button)) {
          auto button = std::get<text_button>(any_button);
          serialized_buttons.push_back(button.serialize());
          printf("%s\n", button.serialize().c_str());
        }
      }

      serialized_rows.push_back('[' + string_util::join(serialized_buttons) + ']');
      serialized_buttons.clear();
    }

    serialized += string_util::join(serialized_rows);

    serialized.push_back(']');
    return '{' + serialized + '}';
  }
  template <typename button_type>
  bool has_type(any_button button) const noexcept {
    return std::holds_alternative<button_type>(button);
  }

private:
  std::vector<std::vector<any_button>> buttons;
};

} // namespace keyboard
} // namespace vk

#endif // VK_KEYBOARD_LAYOUT_H
