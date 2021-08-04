#ifndef VK_KEYBOARD_LAYOUT_HPP
#define VK_KEYBOARD_LAYOUT_HPP

#include "vk/include/keyboard/buttons/location.hpp"
#include "vk/include/keyboard/buttons/open_app.hpp"
#include "vk/include/keyboard/buttons/text.hpp"
#include "vk/include/keyboard/buttons/vk_pay.hpp"
#include "vk/include/keyboard/flags.hpp"

#include <variant>

namespace vk {
namespace keyboard {

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
     * @brief Add row by passing `std::vector`.
     */
    void add_row(const std::vector<any_button>& row);
    /*!
     * @brief Convert buttons data to JSON schema.
     * @return JSON representation.
     */
    void serialize();
    std::string get() const noexcept;
    bool has_flag(keyboard::flag flag) const noexcept;

private:
    std::string m_serialized{};
    /*!
     * @brief Button grid container.
     *
     * Example: for 2x2 layout: [[button1,button2],[button3,button4]].
     */
    std::vector<std::vector<any_button>> m_buttons{};
    flag m_flags = vk::keyboard::flag::none;
};

}// namespace keyboard
}// namespace vk

#endif// VK_KEYBOARD_LAYOUT_HPP
