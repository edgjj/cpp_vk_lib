#include "methods/utils.hpp"

#include "exception/error_processor.hpp"
#include "simdjson.h"

vk::method::utils::utils()
    : m_parser(std::make_shared<simdjson::dom::parser>())
    , m_group_constructor()
{ }

vk::method::utils::~utils() = default;

bool vk::method::utils::check_link(std::string_view url) const
{
    std::string raw_response = m_group_constructor
        .method("utils.checkLink")
        .param("url", url)
        .execute();

    simdjson::dom::object response = m_parser->parse(raw_response);

    if (response.begin().key() == "error")
    {
        processing::log_and_throw<exception::invalid_parameter_error>("utils", response);
    }

    std::string_view status = response["response"]["status"];

    return status == "not_banned";
}

std::string vk::method::utils::get_short_link(std::string_view url) const
{
    std::string raw_response = m_group_constructor
        .method("utils.getShortLink")
        .param("url", url)
        .execute();

    simdjson::dom::object response = m_parser->parse(raw_response);

    if (response.begin().key() == "error")
    {
        processing::log_and_throw<exception::access_error>("utils", response);
    }

    std::string_view short_url_response = response["response"]["short_url"];
    std::string short_url;

    return short_url.assign(short_url_response.data(), short_url_response.size());
}

std::int64_t vk::method::utils::resolve_screen_name(std::string_view screen_name) const
{
    std::string raw_response = m_group_constructor
        .method("utils.resolveScreenName")
        .param("screen_name", screen_name)
        .execute();

    simdjson::dom::object response = m_parser->parse(raw_response);

    if (response["response"].get_array().size() == 0)
    {
        processing::log_and_throw<exception::access_error>("utils", "No such user.");
    }

    return response["response"]["object_id"].get_int64();
}
