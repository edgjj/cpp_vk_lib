#ifndef VK_MESSAGES_H
#define VK_MESSAGES_H

#include <map>
#include "api/base_object.hpp"
#include "attachment/attachment.hpp"


namespace vk {
struct VK_EXPORT conversation_member {
    std::string first_name;
    std::string last_name;
    std::int64_t id;
    bool online;
};

using conversation_member_list = std::vector<conversation_member>;

class VK_EXPORT messages : private base_object {
public:
    explicit messages(std::string_view user_token_) : base_object(user_token_) { };
    explicit messages() = default;
    ~messages() = default;

    void send               (std::int64_t peer_id, std::string_view text);
    void send               (std::int64_t peer_id, std::string_view text, const attachment::attachments_t& list);
    void send               (std::int64_t peer_id, std::string_view text, std::map<std::string, std::string>&& raw_parameters);
    void remove_chat_user   (std::int64_t chat_id, std::int64_t user_id);
    void edit_chat          (std::int64_t chat_id, std::string_view new_title);
    void delete_chat_photo  (std::int64_t chat_id, std::int64_t group_id);
    void set_chat_photo     (std::string_view filename, std::string_view raw_server);
    void pin                (std::int64_t peer_id, std::int64_t message_id);
    conversation_member_list get_conversation_members(std::int64_t peer_id);
};
} // namespace vk

#endif // VK_MESSAGES_H
