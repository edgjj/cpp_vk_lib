#ifndef VK_ERROR_HANDLER_H
#define VK_ERROR_HANDLER_H

#include "exception/exception.hpp"

namespace simdjson {
namespace dom {
class object;
}// namespace dom
}// namespace simdjson

namespace vk {
namespace processing {

template <typename Exception>
inline constexpr bool is_exception_inheritor_v = std::is_base_of_v<exception::common_exception, Exception>;

std::pair<std::int64_t, std::string> extract_from_json(const simdjson::dom::object& error_object);
void log_and_rethrow(std::string_view label, std::exception_ptr exception_ptr);

template <typename Exception, typename = std::enable_if_t<is_exception_inheritor_v<Exception>>>
std::exception_ptr try_construct_exception_ptr(const std::pair<std::int64_t, std::string>& error)
{
    std::exception_ptr exception_ptr = std::make_exception_ptr(Exception(error.first, error.second.c_str()));
    return exception_ptr;
}

template <typename Exception, typename = std::enable_if_t<is_exception_inheritor_v<Exception>>>
void log_and_throw(std::string_view label, const simdjson::dom::object& error_object)
{
    std::exception_ptr exception_ptr = try_construct_exception_ptr<Exception>(extract_from_json(error_object));
    log_and_rethrow(label, exception_ptr);
    throw std::current_exception();
}

template <typename Exception, typename = std::enable_if_t<is_exception_inheritor_v<Exception>>>
void log_and_throw(std::string_view label, std::string_view error_message)
{
    std::exception_ptr exception_ptr = try_construct_exception_ptr<Exception>({-1, error_message.data()});
    log_and_rethrow(label, exception_ptr);
    throw std::current_exception();
}

template <typename Exception, typename = std::enable_if_t<is_exception_inheritor_v<Exception>>>
void log_only(std::string_view label, const simdjson::dom::object& error_object)
{
    std::exception_ptr exception_ptr = try_construct_exception_ptr<Exception>(extract_from_json(error_object));
    log_and_rethrow(label, exception_ptr);
}

template <typename Exception, typename = std::enable_if_t<is_exception_inheritor_v<Exception>>>
void log_only(std::string_view label, std::string_view error_message)
{
    std::exception_ptr exception_ptr = try_construct_exception_ptr<Exception>({-1, error_message});
    log_and_rethrow(label, exception_ptr);
}

}// namespace processing
}// namespace vk

#endif// VK_ERROR_HANDLER_H
