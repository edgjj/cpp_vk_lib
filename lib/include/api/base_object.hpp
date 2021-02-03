#ifndef VK_BASE_OBJECT_H
#define VK_BASE_OBJECT_H

#include <simdjson.h>

#include <map>
#include <string>
#include <memory>

#include "lib/include/net/network_client.hpp"


namespace vk
{
class VK_EXPORT base_object
{
protected:
    explicit base_object() noexcept;
    std::string append_url(std::string_view method) const;
    std::map<std::string, std::string> user_params(std::map<std::string, std::string>&& params) const;
    std::map<std::string, std::string> group_params(std::map<std::string, std::string>&& params) const;

    std::string call(std::string_view method, const std::map<std::string, std::string>& params) const;

    static inline constexpr const char api_v[] = "5.124";

    std::string access_token;
    std::string user_token;

    lib::network_client network_client;
    simdjson::dom::parser parser;
};
} // namespace vk

#endif // VK_BASE_OBJECT_H
