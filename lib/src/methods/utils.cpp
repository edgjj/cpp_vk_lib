#include "simdjson.h"

#include "processing/exception.hpp"
#include "methods/utils.hpp"


bool vk::method::utils::check_link(std::string_view url) {
  simdjson::dom::object response(
    method_util.call_and_parse("utils.checkLink", method_util.group_args({
      {"url", url.data()}
    }))
  );
  if (method_util.error_returned(response, 100))
    vk_throw(exception::invalid_parameter_error, 100, "Invalid URL.");

  return response["response"]["status"].get_string().take_value() == "not_banned";
}

std::string vk::method::utils::get_short_link(std::string_view url) {
  simdjson::dom::object response(
    method_util.call_and_parse("utils.getShortLink", method_util.group_args({
      {"url", url.data()}
    }))
  );
  if (method_util.error_returned(response, 100))
    vk_throw(exception::invalid_parameter_error, 100, "Invalid URL.");

  return response["response"]["short_url"].get_string().take_value().data();
}

std::int64_t vk::method::utils::resolve_screen_name(std::string_view screen_name) {
  if (screen_name.empty())
    vk_throw(exception::invalid_parameter_error, -1, "Empty argument passed.");

  simdjson::dom::object response(
    method_util.call_and_parse("utils.resolveScreenName", method_util.group_args({
      {"screen_name", screen_name.data()}
    }))
  );
  if (response["response"].get_array().size() == 0)
    vk_throw(exception::access_error, -1, "No such user");

  return response["response"]["object_id"].get_int64();
}
