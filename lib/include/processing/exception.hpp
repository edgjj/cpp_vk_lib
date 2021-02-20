#ifndef VK_EXCEPTION_H
#define VK_EXCEPTION_H

#include "processing/backtrace.hpp"


namespace vk {
namespace exception {

/*!
 * @brief General exception of VK method classes.
 */
class vk_export common_exception : public std::exception {
public:
  virtual const char* what() const noexcept override {
    return error.what();
  }
  std::int64_t id() const noexcept {
    return error_id;
  }
protected:
  explicit common_exception(std::int32_t id, const char* what_arg)
    : error_id(id), error(what_arg)
  {
    backtrace_view{0};
  }
  std::string create(std::int32_t id, const std::string& ename) const {
    return "[vk.exception." + ename + '.' + std::to_string(id) + "]: ";
  }

private:
  std::int32_t error_id;
  std::runtime_error error;
};

#define GENERATE_EXCEPTION_CLASS(EXCEPTION) \
  class vk_export EXCEPTION : public common_exception { \
  public: \
    explicit EXCEPTION(int id_, const char* what_arg_) \
      : common_exception(id_, std::string(create(id_, #EXCEPTION) + what_arg_).c_str()) \
    { } \
  }; \

GENERATE_EXCEPTION_CLASS(upload_error)
GENERATE_EXCEPTION_CLASS(access_error)
GENERATE_EXCEPTION_CLASS(invalid_parameter_error)

} // namespace exception
} // namespace vk

#define vk_throw(EXCEPTION, ID, MESSAGE) \
  throw EXCEPTION(ID, MESSAGE)


#undef GENERATE_EXCEPTION_CLASS

#endif // VK_EXCEPTION_H
