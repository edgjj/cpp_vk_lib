#ifndef VK_COMMON_DOCUMENT_H
#define VK_COMMON_DOCUMENT_H

#include "attachment/attachment.hpp"
#include "api/service.hpp"


namespace vk {
namespace document {
/*!
 * @brief The base class for @ref vk::docs, @ref vk::photos and @ref vk::video.
 */
class vk_hidden common : public service {
protected:
  explicit common(std::string_view user_token_) : service(user_token_) { };
  explicit common() = default;
  /*!
   * @brief Search attachments of requested type.
   * @param method    - method name (photos.search, video.search or docs.search)
   * @param query     - search query
   * @param count     - maximum count of documents to search
   * @return vector of attachments.
   */
  vk::attachment::attachments_t common_search(std::string_view method, std::string_view query, std::int64_t count);
  /*!
   * \brief Upload file to server.
   * \return parsed JSON response.
   */
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
