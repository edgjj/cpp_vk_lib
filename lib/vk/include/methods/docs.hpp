#ifndef VK_METHODS_DOCS_HPP
#define VK_METHODS_DOCS_HPP

#include "vk/include/exception/error_code.hpp"
#include "vk/include/document/common.hpp"
#include "vk/include/methods/utility/constructor.hpp"

namespace vk {
namespace method {
/*!
 * @brief The docs methods representation.
 *
 * Please, inherit this class to add new methods.
 */
class docs
{
public:
    docs(error_code& errc);
    docs(error_code& errc, std::string_view user_token);
    ~docs();

    void edit(int64_t owner_id, int64_t doc_id, std::string_view title, std::initializer_list<std::string> tags = {}) const;
    void remove(int64_t owner_id, int64_t doc_id) const;
    std::string get_upload_server(int64_t group_id) const;
    std::string get_wall_upload_server(int64_t group_id) const;
    std::string get_messages_upload_server(std::string_view type, int64_t peer_id) const;
    vk::attachment::attachments_t search(std::string_view query, int64_t count) const;
    std::shared_ptr<vk::attachment::audio_message> save_audio_message(std::string_view file, std::string_view raw_server) const;

protected:
    error_code& m_stored_error;
    std::shared_ptr<simdjson::dom::parser> m_parser;
    mutable method::group_constructor m_group_constructor;
    mutable method::user_constructor m_user_constructor;
    document::common m_document;
};

}// namespace method
}// namespace vk

#endif// VK_METHODS_DOCS_HPP
