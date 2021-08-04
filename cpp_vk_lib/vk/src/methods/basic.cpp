#include "vk/include/methods/basic.hpp"

#include "vk/include/exception/error-inl.hpp"
#include "vk/include/methods/utility/message_constructor.hpp"

#include "simdjson.h"

void vk::method::messages::send(int64_t peer_id, std::string_view text, bool mentions_flag)
{
    message_constructor constructor(mentions_flag);

    constructor
        .param("peer_id", std::to_string(peer_id))
        .param("message", text)
        .perform_request();
}

void vk::method::messages::send(int64_t peer_id, std::string_view text, std::vector<attachment::attachment_ptr_t> list, bool mentions_flag)
{
    message_constructor constructor(mentions_flag);

    constructor
        .param("peer_id", std::to_string(peer_id))
        .param("message", text)
        .attachments(std::move(list))
        .perform_request();
}

void vk::method::messages::send(int64_t peer_id, std::string_view text, std::string_view keyboard_layout, bool mentions_flag)
{
    message_constructor constructor(mentions_flag);

    constructor
        .param("peer_id", std::to_string(peer_id))
        .param("message", text)
        .param("keyboard", keyboard_layout)
        .perform_request();
}

int64_t vk::method::groups::get_by_id(error_code& errc)
{
    const std::string response = group_constructor()
        .method("groups.getById")
        .perform_request();

    simdjson::dom::parser parser;
    const simdjson::dom::object parsed = parser.parse(response);

    if (parsed.begin().key() == "error") {
        errc.assign(exception::translate_error(parsed["error"]["error_code"].get_int64()));
        return -1;
    }

    return parsed["response"].at(0)["id"];
}

std::string vk::method::groups::get_long_poll_server(int64_t group_id)
{
    return group_constructor()
        .method("groups.getLongPollServer")
        .param("group_id", std::to_string(group_id))
        .param("random_id", "0")
        .perform_request();
}
