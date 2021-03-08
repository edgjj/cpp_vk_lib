#ifndef VK_DOCS_H
#define VK_DOCS_H

#include "document/common.hpp"


namespace vk {
namespace method {
/*!
 * @brief The docs methods representation.
 *
 * Please, inherit this class to add new methods.
 */
class docs : protected document::common {
public:
  explicit docs();
  ~docs();

  void edit                               (std::int64_t owner_id, std::int64_t doc_id, std::string_view title, std::initializer_list<std::string>&& tags = { }) const;
  void remove                             (std::int64_t owner_id, std::int64_t doc_id) const;
  std::string get_upload_server           (std::int64_t group_id) const;
  std::string get_wall_upload_server      (std::int64_t group_id) const;
  std::string get_messages_upload_server  (std::string_view type, std::int64_t peer_id) const;
  vk::attachment::attachments_t search    (std::string_view query, std::int64_t count) const;
  std::shared_ptr<vk::attachment::audio_message> save_audio_message(std::string_view file, std::string_view raw_server) const;
private:
  method_utils method_util;
  std::unique_ptr<simdjson::dom::parser> parser;
};
} // namespace method
} // namespace vk

#endif // VK_DOCS_H
