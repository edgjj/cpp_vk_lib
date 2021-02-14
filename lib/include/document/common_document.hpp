#ifndef VK_COMMON_DOCUMENT_H
#define VK_COMMON_DOCUMENT_H

#include "attachment/attachment.hpp"
#include "api/base_object.hpp"


namespace vk {
namespace document {
class vk_hidden common : public base_object {
protected:
  explicit common(std::string_view user_token_) : base_object(user_token_) { };
  explicit common() = default;
  vk::attachment::attachments_t common_search(std::string_view type, std::string_view query, std::int64_t count);
  simdjson::dom::object common_upload(
    simdjson::dom::parser& parser,
    const vk::network_client& network_client,
    std::string_view filename,
    std::string_view server,
    std::string_view field_name
  );
};
} // namespace document
} // namespace vk
#endif // VK_COMMON_DOCUMENT_H
