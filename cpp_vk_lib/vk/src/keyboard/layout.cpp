#include "vk/include/keyboard/layout.hpp"

#include <algorithm>

vk::keyboard::layout::layout(vk::keyboard::flag flags)
    : m_serialized()
    , m_buttons()
    , m_flags(flags) {}

void vk::keyboard::layout::add_row(const std::vector<vk::keyboard::any_button>& row)
{
    m_buttons.push_back(row);
}

static std::string create_button(const vk::keyboard::any_button& any_button)
{
    if (std::holds_alternative<vk::keyboard::button::text>(any_button)) {
        return std::get<vk::keyboard::button::text>(any_button).serialize();
    }

    if (std::holds_alternative<vk::keyboard::button::vk_pay>(any_button)) {
        return std::get<vk::keyboard::button::vk_pay>(any_button).serialize();
    }

    if (std::holds_alternative<vk::keyboard::button::open_app>(any_button)) {
        return std::get<vk::keyboard::button::open_app>(any_button).serialize();
    }

    if (std::holds_alternative<vk::keyboard::button::location>(any_button)) {
        return std::get<vk::keyboard::button::location>(any_button).serialize();
    }

    return "";
}

void vk::keyboard::layout::serialize()
{
    m_serialized.push_back('{');

    if (has_flag(flag::in_line)) {
        m_serialized.append("\"inline\":true,");
    }

    if (has_flag(flag::one_time)) {
        m_serialized.append("\"one_time\":true,");
    }

    m_serialized.append("\"buttons\":[");

    std::vector<std::string> serialized_rows;

    for (const auto& row : m_buttons) {
        std::vector<std::string> serialized_buttons;
        std::transform(row.begin(), row.end(), std::back_inserter(serialized_buttons), [](const any_button& button){
            return create_button(button);
        });

        serialized_rows.push_back('[' + runtime::string_utils::join<std::string>(serialized_buttons) + ']');
    }

    m_serialized += runtime::string_utils::join<std::string>(serialized_rows);

    m_serialized.append("]}");
}

std::string vk::keyboard::layout::get() const noexcept
{
    return m_serialized;
}

bool vk::keyboard::layout::has_flag(vk::keyboard::flag flag) const noexcept
{
    return (m_flags & flag) > 0;
}
