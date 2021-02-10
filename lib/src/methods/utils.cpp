#include "processing/exception.hpp"
#include "methods/utils.hpp"


bool vk::utils::check_link(std::string_view url) {
    simdjson::dom::object response(
        call_and_parse("utils.checkLink", group_params({
            {"url", url.data()}
        }))
    );
    if (error_returned(response, 100))
        VK_THROW(exception::invalid_parameter_error, 100, "Invalid URL.");

    return response["response"]["status"].get_string().take_value() == "not_banned";
}

std::string vk::utils::get_short_link(std::string_view url) {
    simdjson::dom::object response(
        call_and_parse("utils.getShortLink", group_params({
            {"url", url.data()}
        }))
    );
    if (error_returned(response, 100))
        VK_THROW(exception::invalid_parameter_error, 100, "Invalid URL.");

    return response["response"]["short_url"].get_string().take_value().data();
}

std::int64_t vk::utils::resolve_screen_name(std::string_view screen_name) {
    if (screen_name.empty())
        VK_THROW(exception::invalid_parameter_error, -1, "Empty argument passed.");

    simdjson::dom::object response(
        call_and_parse("utils.resolveScreenName", group_params({
            {"screen_name", screen_name.data()}
        }))
    );
    if (response["response"].get_array().size() == 0)
        VK_THROW(exception::access_error, -1, "No such user");

    return response["response"]["object_id"].get_int64();
}
