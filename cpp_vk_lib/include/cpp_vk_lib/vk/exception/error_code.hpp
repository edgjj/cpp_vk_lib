#ifndef VK_EXCEPTION_ERROR_CODE_HPP
#define VK_EXCEPTION_ERROR_CODE_HPP

#include <string>

namespace vk {

class error_code
{
public:
    error_code() noexcept;
    error_code(std::string_view message);
    error_code(const error_code& rhs) = default;
    error_code(error_code&& rhs) noexcept;

    error_code& operator=(const error_code&) = delete;
    error_code& operator=(error_code&&) = delete;

    void assign(std::string_view error);
    void clear();
    const std::string& message() const noexcept;

    explicit operator bool() const noexcept;

private:
    std::string message_;
    bool has_error_;
};

}// namespace vk

#endif// VK_EXCEPTION_ERROR_CODE_HPP
