#include "api/base_object.hpp"

#include "logger/logger.hpp"


namespace vk
{
class base_object;
}

namespace
{
class VK_HIDDEN config
{
public:
    friend class vk::base_object;

private:
    simdjson::dom::element element;
    simdjson::dom::parser parser;
    config(std::string_view path) noexcept
    {
        element = parser.load(path.data());
        logger(logflag::info | logflag::flush) << std::string("config successfully loaded (") + path.data() + std::string(")");
    }
    std::string_view load_access_token() const noexcept { return element["access_token"].get_string(); }
    std::string_view load_user_token()   const noexcept { return element["user_token"].get_string(); }
};
}

vk::base_object::base_object() noexcept
{
    static config config("./config.json");

    access_token = config.load_access_token();
    user_token   = config.load_user_token();
}

std::string vk::base_object::append_url(std::string_view method) const
{
    return "https://api.vk.com/method/" + std::string { method } + '?';
}

std::map<std::string, std::string> vk::base_object::user_params(std::map<std::string, std::string>&& params) const
{
    params.insert({{"access_token", user_token}, {"v", api_v}});
    return std::move(params);
}

std::map<std::string, std::string> vk::base_object::group_params(std::map<std::string, std::string>&& params) const
{
    params.insert({{"access_token", access_token}, {"v", api_v}});
    return std::move(params);
}

simdjson::dom::object vk::base_object::call_and_parse(std::string_view method, const std::map<std::string, std::string>& params)
{
    return parser.parse(call(method, std::move(params)));
}

std::string vk::base_object::call(std::string_view method, const std::map<std::string, std::string>& params) const
{
    return network_client.request(append_url(method), params);
}

bool vk::base_object::error_returned(const simdjson::dom::object& response, std::int64_t error_code)
{
    return response.begin().key() == "error" && response["error"]["error_code"].get_int64() == error_code;
}
