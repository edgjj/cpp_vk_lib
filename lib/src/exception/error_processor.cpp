#include "simdjson.h"

#include "config/loader.hpp"
#include "exception/exception.hpp"
#include "exception/error_processor.hpp"
#include "logger/logger.hpp"


static std::exception_ptr try_construct_exception_ptr(
    vk::processing::error_type error_type,
    const std::pair<std::int64_t, std::string_view>& exception_params
) {
  std::exception_ptr exception_ptr;
  switch (error_type) {
  case vk::processing::error_type::access_error:
    exception_ptr =
      std::make_exception_ptr(vk::exception::access_error(
        exception_params.first, exception_params.second.data()));
    break;
  case vk::processing::error_type::invalid_parameter_error:
    exception_ptr =
      std::make_exception_ptr(vk::exception::invalid_parameter_error(
        exception_params.first, exception_params.second.data()));
    break;
  case vk::processing::error_type::upload_error:
    exception_ptr =
      std::make_exception_ptr(vk::exception::upload_error(
        exception_params.first, exception_params.second.data()));
    break;
  }
  return exception_ptr;
}

static void rethrow_and_log(std::string_view label, std::exception_ptr exception_ptr) {
  try {
   if (exception_ptr) { std::rethrow_exception(exception_ptr); }
  }  catch (std::exception& ex) {
    logger(vk::config::error_logpath(), logflag::error) << label << ": " << ex.what();
  }
}

void vk::processing::log_and_throw(std::string_view label, error_type errtype, const simdjson::dom::object& error_object) {
  auto&& error_body = error_object["error"];
  std::exception_ptr exception_ptr = try_construct_exception_ptr(
    errtype, {error_body["error_code"], error_body["error_msg"]});
  rethrow_and_log(label, exception_ptr);
  throw std::current_exception();
}
void vk::processing::log_and_throw(std::string_view label, error_type errtype, std::string_view error_message) {
  std::exception_ptr exception_ptr = try_construct_exception_ptr(
    errtype, {-1, error_message});
  rethrow_and_log(label, exception_ptr);
  throw std::current_exception();
}
void vk::processing::log_only(std::string_view label, error_type errtype, const simdjson::dom::object& error_object) {
  auto&& error_body = error_object["error"];
  std::exception_ptr exception_ptr = try_construct_exception_ptr(
    errtype, {error_body["error_code"], error_body["error_msg"]});
  rethrow_and_log(label, exception_ptr);
}
void vk::processing::log_only(std::string_view label, error_type errtype, std::string_view error_message) {
  std::exception_ptr exception_ptr = try_construct_exception_ptr(
    errtype, {-1, error_message});
  rethrow_and_log(label, exception_ptr);
}
