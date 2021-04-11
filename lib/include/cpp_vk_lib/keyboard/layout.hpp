#ifndef VK_KEYBOARD_LAYOUT_H
#define VK_KEYBOARD_LAYOUT_H

#include "keyboard/buttons/location.hpp"
#include "keyboard/buttons/open_app.hpp"
#include "keyboard/buttons/text.hpp"
#include "keyboard/buttons/vk_pay.hpp"
#include "keyboard/flags.hpp"

#include <variant>

namespace vk {
namespace keyboard {

using any_button = std::variant<button::text, button::vk_pay, button::open_app, button::location>;

/*!
 * @brief The buttons grid representation.
 */
class layout {
public:
  layout(keyboard::flag);

  layout() = default;
  layout(const layout&) = default;
  layout(layout&&) = default;
  layout& operator=(const layout&) = default;
  layout& operator=(layout&&) = default;
  ~layout() = default;

  /*!
   * @brief Add row by passing `std::vector`.
   */
  void add_row(const std::vector<any_button>& row);
  /*!
   * @brief Convert buttons data to JSON schema.
   * @return JSON representation.
   */
  std::string serialize() const;
  bool has_flag(flag flag_) const noexcept;

private:
  /*!
   * @brief Button grid container.
   *
   * Example: for 2x2 layout: [[button1,button2],[button3,button4]].
   */
  std::vector<std::vector<any_button>> buttons{};
  flag flags = vk::keyboard::flag::none;
};

}// namespace keyboard
}// namespace vk

#endif// VK_KEYBOARD_LAYOUT_H