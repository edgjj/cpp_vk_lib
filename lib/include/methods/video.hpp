#ifndef VK_VIDEO_H
#define VK_VIDEO_H

#include "document/common_document.hpp"


namespace vk
{
class VK_EXPORT video : private document::common
{
public:
    vk::attachment::attachments_t search(std::string_view query, std::int64_t count);
    void save_by_link(std::string_view url);
};
} // namespace vk

#endif // VK_VIDEO_H
