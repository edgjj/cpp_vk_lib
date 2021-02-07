#ifndef VK_NETWORK_CLIENT_H
#define VK_NETWORK_CLIENT_H

#include <string_view>
#include <memory>
#include <map>

#include "misc/cppdefs.hpp"

#if defined VK_CURL_DEBUG
#include "logger/logger.hpp"
#endif // VK_CURL_DEBUG


namespace vk
{
class VK_EXPORT network_client
{
public:
    std::string request(std::string_view body, const std::map<std::string, std::string>& params = { }) const;
    std::size_t download(std::string_view filename, std::string_view server) const;
    std::string upload(std::string_view field_name, std::string_view filename, std::string_view server) const;
    std::string request_data(std::string_view body, std::string_view data) const;

    static std::string unescape(std::string_view text);

private:
#if defined VK_CURL_DEBUG
    template <typename... Args>
    void debug(Args&&... args) const noexcept
    {
        logger(logflag::debug | logflag::spaces).print_pack(args...);
    }
    template <typename... Args>
    void debug_error(Args&&... args) const noexcept
    {
        logger(logflag::error | logflag::spaces).print_pack(args...);
    }
#else
    template <typename... Args>
    constexpr void debug(Args&&...) const noexcept
    { }
    template <typename... Args>
    constexpr void debug_error(Args&&...) const noexcept
    { }
#endif // VK_CURL_DEBUG
};
} // namespace vk

#endif // VK_NETWORK_CLIENT_H
