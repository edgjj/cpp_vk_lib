#ifndef VK_VIDEO_H
#define VK_VIDEO_H

#include "document/common.hpp"
#include "methods/utility/raw_method.hpp"

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

    video(const video&) = default;
    video(video&&) = default;
    video& operator=(const video&) = default;
    video& operator=(video&&) = default;
    ~video() = default;

    vk::attachment::attachments_t search(std::string_view query, std::int64_t count) const;
    void save_by_link(std::string_view url) const;

protected:
    mutable method::user_raw_method m_user_method;
    document::common m_document;
};
}// namespace method
}// namespace vk

#endif// VK_VIDEO_H
