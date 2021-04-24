#include "methods/utils.hpp"

#include "exception/error_processor.hpp"
#include "simdjson.h"

bool vk::method::utils::check_link(std::string_view url) const
{
    simdjson::dom::object response = m_method_util.call_and_parse("utils.checkLink", m_method_util.group_args({{"url", url.data()}}));

    if (response.begin().key() == "error")
    {
        processing::log_and_throw<exception::invalid_parameter_error>("utils", response);
    }
    std::string_view status = response["response"]["status"];
    return status == "not_banned";
}

std::string vk::method::utils::get_short_link(std::string_view url) const
{
    simdjson::dom::object response = m_method_util.call_and_parse("utils.getShortLink", m_method_util.group_args({{"url", url.data()}}));

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
    simdjson::dom::object response =
        m_method_util.call_and_parse("utils.resolveScreenName", m_method_util.group_args({{"screen_name", screen_name.data()}}));

    if (response["response"].get_array().size() == 0)
    {
        processing::log_and_throw<exception::access_error>("utils", "No such user.");
    }

    return response["response"]["object_id"].get_int64();
}
