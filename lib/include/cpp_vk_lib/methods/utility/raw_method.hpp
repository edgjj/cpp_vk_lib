#ifndef RAW_METHOD_HPP
#define RAW_METHOD_HPP

#include "utility.hpp"

namespace vk {
namespace method {
/*!
 * @code
 *  m_raw_method
 *      .method("messages.send")
 *      .param("key", "value")
 *      .param("key", "value")
 *      .param("key", "value")
 *      .param("key", "value")
 *      .param("key", "value")
 *      .param("key", "value")
 *      .execute();
 * @endcode
 */
class raw_method
{
public:
    static inline bool use_api_link = true;
    static inline bool do_not_use_api_link = false;

    static inline bool group_params = true;
    static inline bool user_params = false;

    explicit raw_method(bool use_api_link_flag)
        : m_group_params(group_params)
        , m_use_api_link(use_api_link_flag)
    { }

    raw_method& method(std::string_view method_name)
    {
        m_method_name = method_name;
        return *this;
    }

    raw_method& append_map(const std::map<std::string, std::string>& map)
    {
        m_params.insert(map.begin(), map.end());
        return *this;
    }

    raw_method& param(std::string_view key, std::string_view value)
    {
        m_params.emplace(key, value);
        return *this;
    }
    /*!
     * @brief Process vk request.
     * @note Parameter map is cleaned up automatically after request.
     * @return Raw JSON.
     */
    std::string execute()
    {
        if (m_use_api_link)
        {
            if (m_group_params)
            {
                std::string response = m_method_util.call(m_method_name, m_method_util.group_args(m_params));
                reset();
                return response;
            }
            else {
                std::string response = m_method_util.call(m_method_name, m_method_util.user_args(m_params));
                reset();
                return response;
            }
        }
        else {
            std::string response = m_net_client.request(m_method_name, m_params);
            reset();
            return response;
        }
    }

    void reset()
    {
        m_method_name.clear();
        m_params.clear();
    }

private:
    friend class user_raw_method;
    friend class group_raw_method;

    explicit raw_method(bool use_api_link_flag, bool group_or_user_params)
      : m_group_params(group_or_user_params)
      , m_use_api_link(use_api_link_flag)
    { }

    explicit raw_method(std::string_view user_token, bool use_api_link_flag, bool group_or_user_params)
      : m_group_params(group_or_user_params)
      , m_use_api_link(use_api_link_flag)
      , m_method_util(user_token)
    { }

    bool m_group_params;
    bool m_use_api_link;
    vk::network_client m_net_client{};
    std::string m_method_name{};
    vk::method::utility m_method_util{};
    std::map<std::string, std::string> m_params{};
};

class user_raw_method
{
public:
    user_raw_method()
      : m_raw_method(raw_method::use_api_link, raw_method::user_params)
    { }

    user_raw_method(std::string_view user_token)
      : m_raw_method(user_token, raw_method::use_api_link, raw_method::user_params)
    { }

    raw_method& impl()
    {
        return m_raw_method;
    }

private:
    raw_method m_raw_method;
};

class group_raw_method
{
public:
    group_raw_method()
      : m_raw_method(raw_method::use_api_link, raw_method::group_params)
    { }

    raw_method& impl()
    {
        return m_raw_method;
    }

private:
    raw_method m_raw_method;
};
}// namespace method
}// namespace vk

#endif// RAW_METHOD_HPP
