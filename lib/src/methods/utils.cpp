#include "simdjson.h"

#include "methods/utils.hpp"
#include "processing/error_processor.hpp"


bool vk::method::utils::check_link(std::string_view url) {
  simdjson::dom::object response =
    method_util.call_and_parse("utils.checkLink", method_util.group_args({
      {"url", url.data()}
    }));

  if (response.begin().key() == "error") {
    processing::error_log_and_throw("messages", exception::invalid_parameter_error(
      response["error"]["error_code"].get_int64(), response["error"]["error_msg"].get_c_str()
    ));
  }
  return response["response"]["status"].get_string().take_value() == "not_banned";
}

std::string vk::method::utils::get_short_link(std::string_view url) {
  simdjson::dom::object response =
    method_util.call_and_parse("utils.getShortLink", method_util.group_args({
      {"url", url.data()}
    }));

  if (response.begin().key() == "error") {
    processing::error_log_and_throw("messages", exception::invalid_parameter_error(
      response["error"]["error_code"].get_int64(), response["error"]["error_msg"].get_c_str()
    ));
  }
  return response["response"]["short_url"].get_c_str().take_value();
}

std::int64_t vk::method::utils::resolve_screen_name(std::string_view screen_name) {
  if (screen_name.empty())
    processing::error_log_and_throw("utils", exception::invalid_parameter_error(
      -1, "Empty argument provided."));

  simdjson::dom::object response =
    method_util.call_and_parse("utils.resolveScreenName", method_util.group_args({
      {"screen_name", screen_name.data()}
    }));

  if (response["response"].get_array().size() == 0)
    processing::error_log_and_throw("utils", exception::access_error(-1, "No such user."));

  return response["response"]["object_id"].get_int64();
}
