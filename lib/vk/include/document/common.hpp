#ifndef VK_DOCUMENT_COMMON_HPP
#define VK_DOCUMENT_COMMON_HPP

#include "vk/include/attachment/attachment.hpp"
#include "vk/include/methods/utility/constructor.hpp"

#include <vector>

namespace simdjson {
namespace dom {
class parser;
class object;
}// namespace dom
}// namespace simdjson

namespace vk {
namespace document {
/*!
 * @brief The base class for @ref vk::docs, @ref vk::photos and @ref vk::video.
 */
class common
{
public:
    explicit common();
    explicit common(std::string_view user_token);
    ~common();

    /*!
     * @brief Upload file to server.
     * @return parsed JSON response.
     */
    simdjson::dom::object upload(std::string_view filename, std::string_view server, std::string_view field_name) const;
    /*!
     * @brief Search attachments of requested type.
     * @param method    - method name (photos.search, video.search or docs.search)
     * @param query     - search query
     * @param count     - maximum count of documents to search
     * @return vector of attachments.
     */
    std::vector<vk::attachment::attachment_ptr_t> search(std::string_view method, std::string_view query, int64_t count) const;

private:
    std::shared_ptr<simdjson::dom::parser> m_parser;
    mutable method::group_constructor m_group_constructor;
};

}// namespace document
}// namespace vk

#endif// VK_DOCUMENT_COMMON_HPP
