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
 *      .param("key", "value");
 *  m_raw_method.execute();
 *  m_raw_method.reset();
 * @endcode
 */
class raw_method
{
public:
    raw_method& method(std::string_view method_name)
    {
        m_method_name = method_name;
        return *this;
    }

    raw_method& param(std::string_view key, std::string_view value)
    {
        m_params.emplace(key, value);
        return *this;
    }

    std::string execute() const
    {
        return m_method_util.call(m_method_name, m_params);
    }

    void reset()
    {
        m_method_name.clear();
        m_params.clear();
    }

private:
    vk::method::utility m_method_util{};
    std::string m_method_name{};
    std::map<std::string, std::string> m_params{};
};
} // namespace method
} // namespace vk

#endif // RAW_METHOD_HPP
