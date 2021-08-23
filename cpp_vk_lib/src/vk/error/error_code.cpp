#include "cpp_vk_lib/vk/error/error_code.hpp"

namespace vk {

error_code::error_code() noexcept
    : message_()
    , has_error_(false)
{}

error_code::error_code(std::string_view message)
    : message_(message.data(), message.length())
    , has_error_(true)
{}

error_code::error_code(error_code&& rhs) noexcept
    : message_(std::move(rhs.message_))
    , has_error_(rhs.has_error_)
{
    rhs.has_error_ = false;
}

void error_code::assign(std::string_view error)
{
    message_.assign(error.data(), error.length());
    has_error_ = true;
}

void error_code::clear()
{
    message_.clear();
    has_error_ = false;
}

error_code::operator bool() const noexcept
{
    return has_error_;
}

const std::string& error_code::message() const noexcept
{
    return message_;
}

}// namespace vk
