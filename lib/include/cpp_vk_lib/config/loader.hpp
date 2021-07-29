#ifndef VK_CONFIG_LOADER_HPP
#define VK_CONFIG_LOADER_HPP

#include "misc/cppdefs.hpp"

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
    VK_DISABLE_COPY_MOVE(loader)

    static loader* load(std::string_view path);
    static loader* get();

    std::string& user_token_instance()        noexcept { return m_user_token; }
    const std::string& username()       const noexcept { return m_username; }
    const std::string& password()       const noexcept { return m_password; }
    const std::string& user_token()     const noexcept { return m_user_token; }
    const std::string& access_token()   const noexcept { return m_access_token; }
    const std::string& log_path()       const noexcept { return m_log_path; }
    int64_t num_workers()               const noexcept { return m_num_workers; }

private:
    loader(std::string_view path);

    std::string m_username{};
    std::string m_password{};
    std::string m_user_token{};
    std::string m_access_token{};
    std::string m_log_path{};
    int64_t m_num_workers{};

    static loader* instance;
};

inline void load(std::string_view path) { loader::load(path); }
inline void set_user_token(std::string_view token) { loader::get()->user_token_instance() = token; }
inline std::string password()     { return loader::get()->password(); }
inline std::string username()     { return loader::get()->username(); }
inline std::string user_token()   { return loader::get()->user_token(); }
inline std::string access_token() { return loader::get()->access_token(); }
inline std::string log_path()     { return loader::get()->log_path(); }
inline int64_t num_workers()      { return loader::get()->num_workers(); }

}// namespace config
}// namespace vk

#endif// VK_CONFIG_LOADER_HPP
