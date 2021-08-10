#include "vk/include/keyboard/layout.hpp"

#include <algorithm>

namespace vk::keyboard {

layout::layout(flag flags)
    : serialized_()
    , buttons_()
    , flags_(flags) {}

void layout::add_row(const std::vector<any_button>& row)
{
    buttons_.push_back(row);
}

static std::string create_button(const any_button& any_button)
{
    if (std::holds_alternative<button::text>(any_button)) {
        return std::get<button::text>(any_button).serialize();
    }

    if (std::holds_alternative<button::vk_pay>(any_button)) {
        return std::get<button::vk_pay>(any_button).serialize();
    }

    if (std::holds_alternative<button::open_app>(any_button)) {
        return std::get<button::open_app>(any_button).serialize();
    }

    if (std::holds_alternative<button::location>(any_button)) {
        return std::get<button::location>(any_button).serialize();
    }

    return "";
}

void layout::serialize()
{
    serialized_.push_back('{');

    if (has_flag(flag::in_line)) {
        serialized_.append("\"inline\":true,");
    }

    if (has_flag(flag::one_time)) {
        serialized_.append("\"one_time\":true,");
    }

    serialized_.append("\"buttons\":[");

    std::vector<std::string> serialized_rows;

    for (const auto& row : buttons_) {
        std::vector<std::string> serialized_buttons;
        std::transform(row.begin(), row.end(), std::back_inserter(serialized_buttons), [](const any_button& button){
            return create_button(button);
        });

        serialized_rows.push_back('[' + runtime::string_utils::join<std::string>(serialized_buttons, ',') + ']');
    }

    serialized_ += runtime::string_utils::join<std::string>(serialized_rows, ',');

    serialized_.append("]}");
}

std::string layout::get() const noexcept
{
    return serialized_;
}

bool layout::has_flag(flag flag) const noexcept
{
    return (flags_ & flag) > 0;
}

}// namespace vk::keyboard