#ifndef VK_KEYBOARD_LAYOUT_HPP
#define VK_KEYBOARD_LAYOUT_HPP

#include "cpp_vk_lib/vk/keyboard/buttons/location.hpp"
#include "cpp_vk_lib/vk/keyboard/buttons/open_app.hpp"
#include "cpp_vk_lib/vk/keyboard/buttons/text.hpp"
#include "cpp_vk_lib/vk/keyboard/buttons/vk_pay.hpp"
#include "cpp_vk_lib/vk/keyboard/flags.hpp"

#include <variant>

namespace vk::keyboard {

using any_button = std::variant<button::text, button::vk_pay, button::open_app, button::location>;

/*!
 * @brief The buttons grid representation.
 */
class layout
{
public:
    layout() = default;
    layout(keyboard::flag flags);

    /*!
     * @brief Add row. Each `add_row` call adds
     * new row to keyboard.
     */
    void add_row(const std::vector<any_button>& row);
    /*!
     * @brief Convert buttons data to JSON schema.
     * @return JSON representation.
     */
    void serialize();
    const std::string& get() const noexcept;
    bool has_flag(keyboard::flag flag) const noexcept;

private:
    std::string serialized_{};
    std::vector<std::vector<any_button>> buttons_{};
    flag flags_ = vk::keyboard::flag::none;
};

}// namespace vk::keyboard

#endif// VK_KEYBOARD_LAYOUT_HPP
