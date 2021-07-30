#ifndef VK_METHODS_MESSAGES_HPP
#define VK_METHODS_MESSAGES_HPP

#include "vk/include/document/common.hpp"
#include "vk/include/methods/utility/constructor.hpp"

namespace vk {
namespace keyboard {
class layout;
}// namespace keyboard
}// namespace vk

namespace vk {
struct conversation_member
{
    std::string first_name;
    std::string last_name;
    int64_t id;
    bool online;
};

using conversation_member_list = std::vector<conversation_member>;

namespace method {
/*!
 * @brief The messages methods representation.
 *
 * Please, inherit this class to add new methods.
 */
class messages
{
public:
    messages(bool disable_mentions_flag);
    messages() = delete;
    ~messages();

    static inline bool disable_mentions = true;
    static inline bool enable_mentions = false;

    void send(int64_t peer_id, std::string_view text) const;
    void send(int64_t peer_id, std::string_view text, attachment::attachments_t list) const;
    void send(int64_t peer_id, std::string_view text, std::map<std::string, std::string> raw_parameters) const;
    void send(int64_t peer_id, std::string_view text, std::string_view layout) const;
    void remove_chat_user(int64_t chat_id, int64_t user_id) const;
    void edit_chat(int64_t chat_id, std::string_view new_title) const;
    void create_chat(std::string_view title, int64_t group_id, std::vector<size_t> user_ids);
    void add_chat_user(int64_t chat_id, int64_t user_id);
    void delete_chat_photo(int64_t chat_id, int64_t group_id) const;
    void pin(int64_t peer_id, int64_t message_id, int64_t conversation_message_id) const;
    void set_chat_photo(std::string_view filename, std::string_view raw_server) const;
    conversation_member_list get_conversation_members(int64_t peer_id) const;

protected:
    bool m_disable_mentions_flag;
    std::shared_ptr<simdjson::dom::parser> m_parser;
    document::common m_document;
    mutable method::group_constructor m_group_constructor;
    mutable method::user_constructor m_user_constructor;
};

}// namespace method
}// namespace vk

#endif// VK_METHODS_MESSAGES_HPP
