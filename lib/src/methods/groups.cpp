#include "simdjson.h"

#include "processing/error_handler.hpp"
#include "methods/groups.hpp"


std::int64_t vk::method::groups::get_by_id() {
  simdjson::dom::object response(method_util.call_and_parse("groups.getById", method_util.group_args({ })));

  if (method_util.error_returned(response, 5))
    processing::process_error("groups", exception::access_error(5,
      "Failed to retrieve group id. Maybe, wrong access token was passed.")
    );

  return response["response"].at(0)["id"].get_int64();
}

simdjson::dom::object vk::method::groups::get_long_poll_server(std::string_view group_id) {
  return
  method_util.call_and_parse("groups.getLongPollServer", method_util.group_args({
    {"group_id",   group_id.data()},
    {"random_id",  "0"}
  }))["response"].get_object();
}
