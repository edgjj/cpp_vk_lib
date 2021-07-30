#ifndef VK_METHODS_AUDIO_HPP
#define VK_METHODS_AUDIO_HPP

#include "vk/include/document/common.hpp"
#include "vk/include/methods/utility/constructor.hpp"

namespace vk {
namespace method {
/*!
 * @brief The audio methods representation.
 *
 * Please, inherit this class to add new methods.
 */
class audio
{
public:
    audio();
    audio(std::string_view user_token);
    ~audio();

    std::string get_upload_server() const;
    void save(std::string_view artist, std::string_view title, std::string_view filename, std::string_view raw_server) const;

protected:
    std::shared_ptr<simdjson::dom::parser> m_parser;
    document::common m_document;
    mutable method::group_constructor m_group_constructor;
    mutable method::user_constructor m_user_constructor;
};

}// namespace method
}// namespace vk

#endif// VK_METHODS_AUDIO_HPP
