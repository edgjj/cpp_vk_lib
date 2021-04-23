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
        return username_;
    }
    std::string password() const noexcept
    {
        return password_;
    }
    std::string& user_token_instance() noexcept
    {
        return user_token_;
    }
    std::string user_token() const noexcept
    {
        return user_token_;
    }
    std::string access_token() const noexcept
    {
        return access_token_;
    }
    std::string error_logpath() const noexcept
    {
        return error_logpath_;
    }
    std::string event_logpath() const noexcept
    {
        return event_logpath_;
    }
    std::int64_t num_workers() const noexcept
    {
        return num_workers_;
    }

private:
    loader(std::string_view path);

    std::string username_{};
    std::string password_{};
    std::string user_token_{};
    std::string access_token_{};
    std::string error_logpath_{};
    std::string event_logpath_{};
    std::int8_t num_workers_{};

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
