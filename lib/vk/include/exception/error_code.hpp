#ifndef VK_EXCEPTION_ERROR_CODE_HPP
#define VK_EXCEPTION_ERROR_CODE_HPP

#include <string>

namespace vk {

class error_code
{
public:
    error_code() noexcept
        : m_message()
        , m_has_error(false) {}

    error_code(const error_code& rhs)
        : m_message(rhs.m_message)
        , m_has_error(rhs.m_has_error) {}

    error_code(error_code&& rhs)
        : m_message(std::move(rhs.m_message))
        , m_has_error(rhs.m_has_error)
    {
        rhs.m_has_error = false;
    }

    error_code& operator=(const error_code&) = delete;
    error_code& operator=(error_code&&) = delete;

    void assign(std::string_view error)
    {
        m_message.assign(error.data(), error.length());
        m_has_error = true;
    }

    void clear()
    {
        m_message.clear();
        m_has_error = false;
    }

    explicit operator bool() const noexcept { return m_has_error; }

    const std::string& message() const noexcept { return m_message; }

private:
    std::string m_message;
    bool m_has_error;
};

}// namespace vk

#endif// VK_EXCEPTION_ERROR_CODE_HPP
