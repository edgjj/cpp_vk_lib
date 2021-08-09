#include "vk/include/exception/error_code.hpp"

vk::error_code::error_code() noexcept
    : message_()
    , has_error_(false) {}

vk::error_code::error_code(std::string_view message)
    : message_(message.data(), message.length())
    , has_error_(true) {}

vk::error_code::error_code(error_code&& rhs) noexcept
    : message_(std::move(rhs.message_))
    , has_error_(rhs.has_error_)
{
    rhs.has_error_ = false;
}

void vk::error_code::assign(std::string_view error)
{
    message_.assign(error.data(), error.length());
    has_error_ = true;
}

void vk::error_code::clear()
{
    message_.clear();
    has_error_ = false;
}

vk::error_code::operator bool() const noexcept { return has_error_; }

const std::string& vk::error_code::message() const noexcept { return message_; }
