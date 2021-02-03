#ifndef VK_COMMON_DOCUMENT_H
#define VK_COMMON_DOCUMENT_H

#include "lib/include/attachment/attachment.hpp"
#include "lib/include/api/base_object.hpp"


namespace simdjson::dom
{
class parser;
class object;
}

namespace vk::document
{
class VK_HIDDEN common : public base_object
{
public:
    vk::attachment::attachments_t common_search(std::string_view type, std::string_view query, std::int64_t count);
    static simdjson::dom::object common_upload(
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
