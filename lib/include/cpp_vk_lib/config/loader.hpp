#ifndef VK_CONFIG_LOADER_H
#define VK_CONFIG_LOADER_H

#include <string>

namespace vk {
namespace config {
/*!
 * @brief Config class with its helper functions.
 *
 * Implemented as singleton to avoid multiply and senseless JSON file read.
 * Please, don't try to use this class directly, use non-member functions
 * instead.
 */
class loader
{
public:
    loader(const loader&) = delete;
    loader(loader&&) = delete;
    loader& operator=(const loader&) = delete;
    loader& operator=(loader&&) = delete;

    static loader* load(std::string_view path);
    static loader* get();

    std::string username() const noexcept
    {
        return m_username;
    }
    std::string password() const noexcept
    {
        return m_password;
    }
    std::string& user_token_instance() noexcept
    {
        return m_user_token;
    }
    std::string user_token() const noexcept
    {
        return m_user_token;
    }
    std::string access_token() const noexcept
    {
        return m_access_token;
    }
    std::string error_logpath() const noexcept
    {
        return m_error_logpath;
    }
    std::string event_logpath() const noexcept
    {
        return m_event_logpath;
    }
    std::int64_t num_workers() const noexcept
    {
        return m_num_workers;
    }

private:
    loader(std::string_view path);

    std::string m_username{};
    std::string m_password{};
    std::string m_user_token{};
    std::string m_access_token{};
    std::string m_error_logpath{};
    std::string m_event_logpath{};
    std::int8_t m_num_workers{};

    static loader* instance;
};

inline void load(std::string_view path)
{
    loader::load(path);
}
inline std::string password() noexcept
{
    return loader::get()->password();
}
inline std::string username() noexcept
{
    return loader::get()->username();
}
inline void set_user_token(std::string_view token)
{
    loader::get()->user_token_instance() = token;
}
inline std::string user_token() noexcept
{
    return loader::get()->user_token();
}
inline std::string access_token() noexcept
{
    return loader::get()->access_token();
}
inline std::string error_logpath() noexcept
{
    return loader::get()->error_logpath();
}
inline std::string event_logpath() noexcept
{
    return loader::get()->event_logpath();
}
inline std::int64_t num_workers() noexcept
{
    return loader::get()->num_workers();
}

}// namespace config
}// namespace vk

#endif// VK_CONFIG_LOADER_H
