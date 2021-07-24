#ifndef VK_METHODS_VIDEO_HPP
#define VK_METHODS_VIDEO_HPP

#include "document/common.hpp"
#include "methods/utility/constructor.hpp"

namespace vk {
namespace method {
/*!
 * @brief The video methods representation.
 *
 * Please, inherit this class to add new methods.
 */
class video
{
public:
    explicit video();
    explicit video(std::string_view user_token);
    ~video();

    vk::attachment::attachments_t search(std::string_view query, int64_t count) const;
    void save_by_link(std::string_view url) const;

protected:
    mutable method::user_constructor m_user_constructor;
    document::common m_document;
};

}// namespace method
}// namespace vk

#endif// VK_METHODS_VIDEO_HPP
