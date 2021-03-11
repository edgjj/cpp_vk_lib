#include "keyboard/layout.hpp"


vk::keyboard::layout::layout(vk::keyboard::flag flags_)
  : buttons()
  , flags(flags_)
{ }

void vk::keyboard::layout::add_row(const std::vector<vk::keyboard::any_button>& row) {
  buttons.push_back(row);
}

template <typename button_type>
static bool has_type(vk::keyboard::any_button button) noexcept {
  return std::holds_alternative<button_type>(button);
}

template <typename button_type>
static void try_push_button(vk::keyboard::any_button any_button, std::vector<std::string>& buttons) {
  if (has_type<button_type>(any_button)) {
    button_type button = std::get<button_type>(any_button);
    buttons.push_back(button.serialize());
  }
}

std::string vk::keyboard::layout::serialize() const {
  std::string serialized;
  serialized.reserve(1024);
  serialized.push_back('{');

  if (is_flag_set(flag::in_line))  { serialized.append(R"("inline":true,)"); }
  if (is_flag_set(flag::one_time)) { serialized.append(R"("one_time":true,)"); }

  serialized.append(R"("buttons":[)");

  std::vector<std::string> serialized_buttons;
  std::vector<std::string> serialized_rows;

  for (auto&& row : buttons) {
    for (auto&& any_button : row) {
      try_push_button<button::text>(any_button, serialized_buttons);
      try_push_button<button::vk_pay>(any_button, serialized_buttons);
      try_push_button<button::open_app>(any_button, serialized_buttons);
      try_push_button<button::location>(any_button, serialized_buttons);
    }
    serialized_rows.push_back('[' + string_utils::join<std::string>(serialized_buttons) + ']');
    serialized_buttons.clear();
  }

  serialized += string_utils::join<std::string>(serialized_rows);

  serialized.push_back(']');
  serialized.push_back('}');
  serialized.shrink_to_fit();
  return serialized;
}

bool vk::keyboard::layout::is_flag_set(vk::keyboard::flag flag_) const noexcept {
  return ((flags & flag_) > 0);
}

