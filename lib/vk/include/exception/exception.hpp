#ifndef VK_EXCEPTION_HPP
#define VK_EXCEPTION_HPP

#include "runtime/include/string_utils/string_utils.hpp"

#include <stdexcept>

namespace vk {
namespace exception {

/*!
 * @brief General exception of VK method classes.
 */
class common_exception : public std::exception
{
public:
    const char* what() const noexcept override
    {
        return m_error.what();
    }

protected:
    explicit common_exception(std::string_view what_arg)
        : m_error(what_arg.data()) {}

    std::string create(size_t id, const char* error_name, const char* arg) const
    {
        return runtime::string_utils::format("[vk.exception.{}.{}]: {}", error_name, id, arg);
    }

private:
    std::runtime_error m_error;
};

class upload_error : public common_exception
{
public:
    explicit upload_error(size_t id, const char* what_arg)
        : common_exception(create(id, "upload_error", what_arg)) {}
};

class access_error : public common_exception
{
public:
    explicit access_error(size_t id, const char* what_arg)
        : common_exception(create(id, "access_error", what_arg)) {}
};

class invalid_parameter_error : public common_exception
{
public:
    explicit invalid_parameter_error(size_t id, const char* what_arg)
        : common_exception(create(id, "invalid_parameter_error", what_arg)) {}
};

class runtime_error : public common_exception
{
public:
    explicit runtime_error(size_t id, const char* what_arg)
        : common_exception(create(id, "runtime_error", what_arg)) {}
};

template <typename Base, typename Derived>
class bad_cast_error : public common_exception
{
public:
    explicit bad_cast_error()
        : common_exception(create(0, "bad_cast_error", "Cast error")) {}
};

}// namespace exception
}// namespace vk

#endif// VK_EXCEPTION_HPP
