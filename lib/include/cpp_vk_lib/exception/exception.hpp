#ifndef VK_EXCEPTION_H
#define VK_EXCEPTION_H

#include "processing/backtrace.hpp"

#include <stdexcept>
#include <string>

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
      : m_error(what_arg.data())
    {
        processing::backtrace_view{};
    }

    std::string create(std::int32_t id, std::string ename, std::string arg) const
    {
        return "[vk.exception." + ename + '.' + std::to_string(id) + "]: " + arg;
    }

private:
    std::runtime_error m_error;
};

class upload_error : public common_exception
{
public:
    explicit upload_error(int id, const char* what_arg)
      : common_exception(create(id, "upload_error", what_arg))
    {}
};

class access_error : public common_exception
{
public:
    explicit access_error(int id, const char* what_arg)
      : common_exception(create(id, "access_error", what_arg))
    {}
};

class invalid_parameter_error : public common_exception
{
public:
    explicit invalid_parameter_error(int id, const char* what_arg)
      : common_exception(create(id, "invalid_parameter_error", what_arg))
    {}
};

template <typename Base, typename Derived>
class bad_cast_error : public common_exception
{
public:
    explicit bad_cast_error()
      : common_exception(create(0, "bad_cast_error", "Cast error"))
    { }
};

}// namespace exception
}// namespace vk

#endif// VK_EXCEPTION_H
