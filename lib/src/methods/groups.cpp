#include "simdjson.h"

#include "processing/error_processor.hpp"
#include "methods/groups.hpp"


std::int64_t vk::method::groups::get_by_id() {
  simdjson::dom::object response(method_util.call_and_parse("groups.getById", method_util.group_args({ })));

  if (response.begin().key() == "error") {
    processing::error_log_and_throw("messages", exception::access_error(
      response["error"]["error_code"].get_int64(), response["error"]["error_msg"].get_c_str()
    ));
  }
  return response["response"].at(0)["id"].get_int64();
}

simdjson::dom::object vk::method::groups::get_long_poll_server(std::string_view group_id) {
  simdjson::dom::object response =
    method_util.call_and_parse("groups.getLongPollServer", method_util.group_args({
      {"group_id",   group_id.data()},
      {"random_id",  "0"}
    }));
  return response["response"].get_object();
}
