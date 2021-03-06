#ifndef VK_ERROR_HANDLER_H
#define VK_ERROR_HANDLER_H

#include <string>


namespace simdjson {
namespace dom {
class object;
} // namespace dom
} // namespace simdjson

namespace vk {
namespace processing {

enum class error_type {
  upload_error,
  access_error,
  invalid_parameter_error
};

void log_and_throw(std::string_view label, error_type errtype, const simdjson::dom::object& error_object);
void log_and_throw(std::string_view label, error_type errtype, std::string_view error_message);
void log_only(std::string_view label, error_type errtype, const simdjson::dom::object& error_object);
void log_only(std::string_view label, error_type errtype, std::string_view error_message);

} // namespace processing
} // namespace vk

#endif // VK_ERROR_HANDLER_H
