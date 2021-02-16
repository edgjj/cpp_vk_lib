#include "keyboard/layout.hpp"


vk::keyboard::layout::layout(vk::keyboard::flag flags_)
  : flags(flags_) { }

void vk::keyboard::layout::add_row(const std::vector<vk::keyboard::any_button>& row) {
  buttons.push_back(row);
}

std::string vk::keyboard::layout::serialize() const {
  std::string serialized;

  if (is_flag_set(flag::in_line)) {
    serialized.append(R"json("inline":true,)json");
  }
  if (is_flag_set(flag::one_time)) {
    serialized.append(R"json("one_time":true,)json");
  }
  serialized.append(R"json("buttons":[)json");

  std::vector<std::string> serialized_buttons;
  std::vector<std::string> serialized_rows;

  for (auto&& row : buttons) {
    for (auto&& any_button : row) {
      if (has_type<text_button>(any_button)) {
        text_button button = std::get<text_button>(any_button);
        serialized_buttons.push_back(button.serialize());
      }
      if (has_type<vk_pay_button>(any_button)) {
        vk_pay_button button = std::get<vk_pay_button>(any_button);
        serialized_buttons.push_back(button.serialize());
      }
      if (has_type<open_app_button>(any_button)) {
        open_app_button button = std::get<open_app_button>(any_button);
        serialized_buttons.push_back(button.serialize());
      }
      if (has_type<location_button>(any_button)) {
        location_button button = std::get<location_button>(any_button);
        serialized_buttons.push_back(button.serialize());
      }
    }

    serialized_rows.push_back('[' + string_util::join<std::string>(serialized_buttons) + ']');
    serialized_buttons.clear();
  }

  serialized += string_util::join<std::string>(serialized_rows);

  serialized.push_back(']');
  return '{' + serialized + '}';
}

bool vk::keyboard::layout::is_flag_set(vk::keyboard::flag flag_) const noexcept {
  return ((flags & flag_) > 0);
}

