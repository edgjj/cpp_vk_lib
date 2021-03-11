#ifndef VK_EXCEPTION_H
#define VK_EXCEPTION_H

#include "processing/backtrace.hpp"
#include <stdexcept>
#include <string>

#include "misc/cppdefs.hpp"


namespace vk {
namespace exception {

/*!
 * @brief General exception of VK method classes.
 */
class common_exception : public std::exception {
public:
  virtual const char* what() const noexcept override {
    return error.what();
  }
protected:
  explicit common_exception(std::string_view what_arg)
    : error(what_arg.data())
  {
    processing::backtrace_view{};
  }
  std::string create(std::int32_t id, std::string ename, std::string arg) const {
    return "[vk.exception." + ename + '.' + std::to_string(id) + "]: " + arg;
  }

private:
  std::runtime_error error;
};

class vk_export upload_error : public common_exception {
public:
  explicit upload_error(int id_, const char* what_arg_)
    : common_exception(create(id_, "upload_error", what_arg_))
  { }
};

class vk_export access_error : public common_exception {
public:
  explicit access_error(int id_, const char* what_arg_)
    : common_exception(create(id_, "access_error", what_arg_))
  { }
};

class vk_export invalid_parameter_error : public common_exception {
public:
  explicit invalid_parameter_error(int id_, const char* what_arg_)
    : common_exception(create(id_, "invalid_parameter_error", what_arg_))
  { }
};

} // namespace exception
} // namespace vk

#endif // VK_EXCEPTION_H
