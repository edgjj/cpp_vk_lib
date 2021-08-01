#include "vk/include/methods/groups.hpp"

#include "vk/include/exception/error-inl.hpp"

#include "simdjson.h"

vk::method::groups::groups(error_code& errc)
    : m_stored_error(errc)
    , m_group_constructor()
    , m_parser(std::make_unique<simdjson::dom::parser>()) {}

vk::method::groups::~groups() = default;

int64_t vk::method::groups::get_by_id() const
{
    const std::string raw_response = m_group_constructor
        .method("groups.getById")
        .perform_request();

    const simdjson::dom::object response = m_parser->parse(raw_response);

    if (response.begin().key() == "error") {
        m_stored_error.assign(exception::translate_error(response["error"]["error_code"].get_int64()));
        return -1;
    }

    return response["response"].at(0)["id"];
}

simdjson::dom::object vk::method::groups::get_long_poll_server(int64_t group_id) const
{
    const std::string raw_response = m_group_constructor
        .method("groups.getLongPollServer")
        .param("group_id", std::to_string(group_id))
        .param("random_id", "0")
        .perform_request();

    const simdjson::dom::object response = m_parser->parse(raw_response);

    if (response.begin().key() == "error") {
        m_stored_error.assign(exception::translate_error(response["error"]["error_code"].get_int64()));
        return {};
    }

    return response["response"];
}
