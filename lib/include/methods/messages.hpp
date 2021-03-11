#ifndef VK_MESSAGES_H
#define VK_MESSAGES_H

#include "attachment/attachment.hpp"
#include "document/common.hpp"
#include "method_utils/method_utils.hpp"


namespace vk {
namespace keyboard {
class layout;
} // namespace keyboard
} // namespace vk

namespace vk {
struct conversation_member {
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
class messages {
public:

  messages(bool disable_mentions_flag_);
  messages() = delete;
  ~messages();
  static inline bool disable_mentions = true;
  static inline bool enable_mentions = false;

  void send                 (std::int64_t peer_id, std::string_view text) const;
  void send                 (std::int64_t peer_id, std::string_view text, attachment::attachments_t&& list) const;
  void send                 (std::int64_t peer_id, std::string_view text, std::map<std::string, std::string>&& raw_parameters) const;
  void send                 (std::int64_t peer_id, std::string_view text, const vk::keyboard::layout& layout) const;
  void remove_chat_user     (std::int64_t chat_id, std::int64_t user_id) const;
  void edit_chat            (std::int64_t chat_id, std::string_view new_title) const;
  void delete_chat_photo    (std::int64_t chat_id, std::int64_t group_id) const;
  void pin                  (std::int64_t peer_id, std::int64_t message_id, std::int64_t conversation_message_id) const;
  void set_chat_photo       (std::string_view filename, std::string_view raw_server) const;
  conversation_member_list get_conversation_members(std::int64_t peer_id) const;

private:
  std::unique_ptr<simdjson::dom::parser> parser;
  document::common common_document;
  bool disable_mentions_flag;
  method_utils method_util;
};
} // namespace method
} // namespace vk

#endif // VK_MESSAGES_H
