#include "methods/groups.hpp"

#include "exception/error_processor.hpp"
#include "simdjson.h"

std::int64_t vk::method::groups::get_by_id() const {
  simdjson::dom::object response = method_util.call_and_parse("groups.getById", method_util.group_args({}));

  if (response.begin().key() == "error") { processing::log_and_throw<exception::access_error>("groups", response); }
  return response["response"].at(0)["id"];
}

simdjson::dom::object vk::method::groups::get_long_poll_server(std::int64_t group_id) const {
  simdjson::dom::object response = method_util.call_and_parse(
      "groups.getLongPollServer",
      method_util.group_args({{"group_id", std::to_string(group_id)}, {"random_id", "0"}}));
  if (response.begin().key() == "error") { processing::log_and_throw<exception::access_error>("groups", response); }
  return response["response"];
}
