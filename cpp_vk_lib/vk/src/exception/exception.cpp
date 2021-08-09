#include "vk/include/exception/exception.hpp"

#include "runtime/include/string_utils/string_utils.hpp"

vk::exception::common_exception::common_exception(std::string_view what_arg)
  : error_(what_arg.data()) {}

const char* vk::exception::common_exception::what() const noexcept
{
    return error_.what();
}

std::string vk::exception::common_exception::create(size_t id, const char* error_name, const char* arg)
{
    return runtime::string_utils::format("[vk.exception.{}.{}]: {}", error_name, id, arg);
}

vk::exception::upload_error::upload_error(size_t id, const char* what_arg)
  : common_exception(create(id, "upload_error", what_arg)) {}

vk::exception::access_error::access_error(size_t id, const char* what_arg)
  : common_exception(create(id, "access_error", what_arg)) {}

vk::exception::invalid_parameter_error::invalid_parameter_error(size_t id, const char* what_arg)
  : common_exception(create(id, "invalid_parameter_error", what_arg)) {}

vk::exception::runtime_error::runtime_error(size_t id, const char* what_arg)
  : common_exception(create(id, "runtime_error", what_arg)) {}
