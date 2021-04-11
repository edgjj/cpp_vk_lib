#include "keyboard/layout.hpp"

#include <algorithm>

vk::keyboard::layout::layout(vk::keyboard::flag flags_)
  : buttons()
  , flags(flags_) {}

void vk::keyboard::layout::add_row(const std::vector<vk::keyboard::any_button>& row) {
  buttons.push_back(row);
}

template <typename _Button_type>
static bool has_type(vk::keyboard::any_button button) noexcept {
  return std::holds_alternative<_Button_type>(button);
}

static std::string create_button(const vk::keyboard::any_button& any_button) {
  if (has_type<vk::keyboard::button::text>(any_button)) { return std::get<vk::keyboard::button::text>(any_button).serialize(); }
  if (has_type<vk::keyboard::button::vk_pay>(any_button)) { return std::get<vk::keyboard::button::vk_pay>(any_button).serialize(); }
  if (has_type<vk::keyboard::button::open_app>(any_button)) { return std::get<vk::keyboard::button::open_app>(any_button).serialize(); }
  if (has_type<vk::keyboard::button::location>(any_button)) { return std::get<vk::keyboard::button::location>(any_button).serialize(); }
  return "";
}

std::string vk::keyboard::layout::serialize() const {
  std::string serialized;
  serialized.reserve(1024);
  serialized.push_back('{');

  if (has_flag(flag::in_line)) { serialized.append(R"("inline":true,)"); }
  if (has_flag(flag::one_time)) { serialized.append(R"("one_time":true,)"); }

  serialized.append(R"("buttons":[)");

  std::vector<std::string> serialized_rows;

  for (auto&& row : buttons) {
    std::vector<std::string> serialized_buttons;
    for (auto&& any_button : row) {
      serialized_buttons.push_back(create_button(any_button));
    }
    serialized_rows.push_back('[' + string_utils::join<std::string>(serialized_buttons) + ']');
  }

  serialized += string_utils::join<std::string>(serialized_rows);

  serialized.append("]}");
  serialized.shrink_to_fit();
  return serialized;
}

bool vk::keyboard::layout::has_flag(vk::keyboard::flag flag_) const noexcept {
  return ((flags & flag_) > 0);
}
