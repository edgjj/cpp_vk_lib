#ifndef VK_COMMON_DOCUMENT_H
#define VK_COMMON_DOCUMENT_H

#include "attachment/attachment.hpp"
#include "api/base_object.hpp"


namespace vk::document
{
class VK_HIDDEN common : public base_object
{
protected:
    vk::attachment::attachments_t common_search(std::string_view type, std::string_view query, std::int64_t count);
    simdjson::dom::object common_upload(
        simdjson::dom::parser& parser,
        const vk::lib::network_client& network_client,
        std::string_view filename,
        std::string_view server,
        std::string_view field_name
    );
    virtual ~common() = default;
};
} // namespace vk::document

#endif // VK_COMMON_DOCUMENT_H
