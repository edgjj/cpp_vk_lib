#ifndef VK_COMMON_DOCUMENT_H
#define VK_COMMON_DOCUMENT_H

#include "attachment/attachment.hpp"
#include "method_utils/method_utils.hpp"


namespace simdjson {
namespace dom {
class parser;
} // namespace dom
} // namespace simdjson

namespace vk {
namespace document {
/*!
 * @brief The base class for @ref vk::docs, @ref vk::photos and @ref vk::video.
 */
class vk_export common {
public:
  explicit common();
  ~common();
  /*!
   * @brief Upload file to server.
   * @return parsed JSON response.
   */
  simdjson::dom::object common_upload(
    std::string_view filename,
    std::string_view server,
    std::string_view field_name
  );
protected:
  /*!
   * @brief Search attachments of requested type.
   * @param method    - method name (photos.search, video.search or docs.search)
   * @param query     - search query
   * @param count     - maximum count of documents to search
   * @return vector of attachments.
   */
  vk::attachment::attachments_t common_search(std::string_view method, std::string_view query, std::int64_t count);

  std::unique_ptr<simdjson::dom::parser> parser;
  method_utils method_util;
  network_client net_client;
};
} // namespace document
} // namespace vk
#endif // VK_COMMON_DOCUMENT_H
