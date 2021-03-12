#include "spdlog/spdlog.h"

#include "simdjson.h"

#include "config/loader.hpp"
#include "exception/error_processor.hpp"


std::pair<int64_t, std::string> vk::processing::extract_from_json(
    const simdjson::dom::object& error_object
) {
  auto&& error_body = error_object["error"];
  return {
    error_body["error_code"], error_body["error_msg"].get_string().take_value().data()
  };
}

void vk::processing::log_and_rethrow(
    std::string_view label, std::exception_ptr exception_ptr
) {
  try {
   if (exception_ptr) { std::rethrow_exception(exception_ptr); }
  }  catch (std::exception& ex) {
    spdlog::error("{}: {}", label, ex.what());
  }
}
