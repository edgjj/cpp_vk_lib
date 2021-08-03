#ifndef VK_METHODS_UTILITY_HPP
#define VK_METHODS_UTILITY_HPP

#include <map>
#include <memory>
#include <string>

namespace simdjson {
namespace dom {
class object;
class parser;
}// namespace dom
}// namespace simdjson

namespace vk {
namespace method {
/*!
 * @brief The container of common functions and constants needed by various methods.
 */
class utility
{
public:
    utility();
    utility(std::string_view user_token);
    ~utility();

    std::map<std::string, std::string>& user_args(std::map<std::string, std::string>& params) const;
    std::map<std::string, std::string>& group_args(std::map<std::string, std::string>& params) const;
    /*!
     * Move or copy is your choice.
     */
    std::string call(std::string_view method, std::map<std::string, std::string> params) const;
    std::string append_url(std::string_view method) const;

    static inline const int64_t chat_id_constant = 2000000000;

private:
    std::string m_user_token;
    std::string m_access_token;
    mutable std::shared_ptr<simdjson::dom::parser> m_parser;
};

}// namespace method
}// namespace vk

#endif// VK_METHODS_UTILITY_HPP