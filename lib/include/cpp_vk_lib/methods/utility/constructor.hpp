#ifndef VK_METHOD_CONSTRUCTOR_HPP
#define VK_METHOD_CONSTRUCTOR_HPP

#include "utility.hpp"

namespace vk {
namespace method {

enum class method_parameter : std::uint32_t
{
    use_api_link        = 1 << 1,
    do_not_use_api_link = 1 << 2,
    user_params         = 1 << 3,
    group_params        = 1 << 4,
};

constexpr std::uint32_t operator & (std::uint32_t lhs, method_parameter rhs) noexcept
{
    return lhs & static_cast<std::uint32_t>(rhs);
}
constexpr std::uint32_t operator & (method_parameter rhs, std::uint32_t lhs) noexcept
{
    return static_cast<std::uint32_t>(lhs) & rhs;
}
constexpr method_parameter operator | (method_parameter lhs, method_parameter rhs) noexcept
{
    return static_cast<method_parameter>(static_cast<std::uint32_t>(lhs) | static_cast<std::uint32_t>(rhs));
}
constexpr bool is_flag_set(method_parameter flag, std::uint32_t params)
{
    return ((params & flag) > 0);
}
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
template <method_parameter parameter>
class constructor
{
public:
    explicit constructor()
      : m_flags(static_cast<std::uint32_t>(parameter))
    { }

    explicit constructor(std::string_view user_token)
      : m_flags(static_cast<std::uint32_t>(parameter))
      , m_method_util(user_token)
    { }

    constructor& method(std::string_view method_name)
    {
        m_method_name = method_name;
        return *this;
    }
    /*!
     * @note Additional_params should be moved.
     */
    constructor& append_map(std::map<std::string, std::string> additional_params)
    {
        m_params.merge(std::move(additional_params));
        return *this;
    }

    constructor& param(std::string_view key, std::string_view value)
    {
        m_params.emplace(key, value);
        return *this;
    }
    /*!
     * @brief Process VK request.
     * @note Parameter map is cleaned up automatically after request.
     * @return Raw JSON.
     */
    std::string execute()
    {
        std::string response;

        if (is_flag_set(method_parameter::use_api_link, m_flags))
        {
            if (is_flag_set(method_parameter::group_params, m_flags))
            {
                response = m_method_util.call(m_method_name, m_method_util.group_args(m_params));
            }
            else {
                response = m_method_util.call(m_method_name, m_method_util.user_args(m_params));
            }
        }
        else {
            response = m_net_client.request(m_method_name, m_params);
        }

        reset();

        return response;
    }

    void reset()
    {
        m_method_name.clear();
        m_params.clear();
    }

private:
    std::uint32_t m_flags;
    vk::network_client m_net_client{};
    std::string m_method_name{};
    vk::method::utility m_method_util{};
    std::map<std::string, std::string> m_params{};
};

using user_constructor_proxy = constructor<method_parameter::use_api_link | method_parameter::user_params>;
using group_constructor_proxy = constructor<method_parameter::use_api_link | method_parameter::group_params>;

}// namespace method
}// namespace vk

#endif// VK_METHOD_CONSTRUCTOR_HPP
