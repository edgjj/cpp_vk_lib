#ifndef VK_MESSAGES_H
#define VK_MESSAGES_H

#include "attachment/attachment.hpp"
#include "document/common_document.hpp"
#include "method_utils/method_utils.hpp"


namespace vk {
namespace keyboard {
class layout;
} // namespace keyboard
} // namespace vk

namespace vk {
struct vk_export conversation_member {
  std::string first_name;
  std::string last_name;
  std::int64_t id;
  bool online;
};

using conversation_member_list = std::vector<conversation_member>;

namespace method {
/*!
 * @brief The messages methods representation.
 *
 * Please, inherit this class to add new methods.
 */
class vk_export messages {
public:
  explicit messages();
  ~messages();

  void send                 (std::int64_t peer_id, std::string_view text);
  void send                 (std::int64_t peer_id, std::string_view text, attachment::attachments_t&& list);
  void send                 (std::int64_t peer_id, std::string_view text, std::map<std::string, std::string>&& raw_parameters);
  void send                 (std::int64_t peer_id, std::string_view text, const vk::keyboard::layout& layout);
  void remove_chat_user     (std::int64_t chat_id, std::int64_t user_id);
  void edit_chat            (std::int64_t chat_id, std::string_view new_title);
  void delete_chat_photo    (std::int64_t chat_id, std::int64_t group_id);
  void pin                  (std::int64_t peer_id, std::int64_t message_id, std::int64_t conversation_message_id);
  void set_chat_photo       (std::string_view filename, std::string_view raw_server);
  conversation_member_list get_conversation_members(std::int64_t peer_id);
private:
  method_utils method_util;
  std::unique_ptr<simdjson::dom::parser> parser;
  document::common common_document;
};
} // namespace method
} // namespace vk

#endif // VK_MESSAGES_H
