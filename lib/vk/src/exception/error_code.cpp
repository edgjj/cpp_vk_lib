#include "vk/include/exception/error_code.hpp"

vk::error_code::error_code() noexcept
    : m_message()
    , m_has_error(false) {}

vk::error_code::error_code(std::string_view message)
    : m_message(message.data(), message.length())
    , m_has_error(true) {}

vk::error_code::error_code(const error_code& rhs)
    : m_message(rhs.m_message)
    , m_has_error(rhs.m_has_error) {}

vk::error_code::error_code(error_code&& rhs)
    : m_message(std::move(rhs.m_message))
    , m_has_error(rhs.m_has_error)
{
    rhs.m_has_error = false;
}

void vk::error_code::assign(std::string_view error)
{
    m_message.assign(error.data(), error.length());
    m_has_error = true;
}

void vk::error_code::clear()
{
    m_message.clear();
    m_has_error = false;
}

vk::error_code::operator bool() const noexcept { return m_has_error; }

const std::string& vk::error_code::message() const noexcept { return m_message; }
