#ifndef VK_MESSAGES_H
#define VK_MESSAGES_H

#include "api/service.hpp"
#include "attachment/attachment.hpp"


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

/*!
 * @brief The messages methods representation.
 *
 * Please, inherit this class to add new methods.
 */
class vk_export messages : protected service {
public:
  explicit messages(std::string_view user_token_) : service(user_token_) { };
  explicit messages() = default;
  ~messages() = default;

  void send                 (std::int64_t peer_id, std::string_view text);
  void send                 (std::int64_t peer_id, std::string_view text, const attachment::attachments_t& list);
  void send                 (std::int64_t peer_id, std::string_view text, std::map<std::string, std::string>&& raw_parameters);
  void send                 (std::int64_t peer_id, std::string_view text, const vk::keyboard::layout& layout);
  void remove_chat_user     (std::int64_t chat_id, std::int64_t user_id);
  void edit_chat            (std::int64_t chat_id, std::string_view new_title);
  void delete_chat_photo    (std::int64_t chat_id, std::int64_t group_id);
  void set_chat_photo       (std::string_view filename, std::string_view raw_server);
  void pin                  (std::int64_t peer_id, std::int64_t message_id);
  conversation_member_list get_conversation_members(std::int64_t peer_id);
};
} // namespace vk

#endif // VK_MESSAGES_H
