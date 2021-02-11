#include "processing/exception.hpp"
#include "methods/groups.hpp"


std::int64_t vk::groups::get_by_id() {
    simdjson::dom::object response(call_and_parse("groups.getById", group_args({ })));

    if (error_returned(response, 5))
        VK_THROW(vk::exception::access_error, 5,
            "Failed to retrieve group id. Maybe, wrong access token was passed.");

    return response["response"].at(0)["id"].get_int64();
}

simdjson::dom::object vk::groups::get_long_poll_server(std::string_view group_id) {
    return
    call_and_parse("groups.getLongPollServer", group_args({
        {"group_id",   group_id.data()},
        {"random_id",  "0"}
    }))["response"].get_object();
}
