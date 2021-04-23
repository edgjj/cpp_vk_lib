#ifndef VK_AUDIO_H
#define VK_AUDIO_H

#include "document/common.hpp"

namespace vk {
namespace method {
/*!
 * @brief The audio methods representation.
 *
 * Please, inherit this class to add new methods.
 */
class audio
{
  public:
    explicit audio();
    explicit audio(std::string_view user_token);

    audio(const audio&) = default;
    audio(audio&&) = default;
    audio& operator=(const audio&) = default;
    audio& operator=(audio&&) = default;
    ~audio();

    std::string get_upload_server() const;
    void save(std::string_view artist, std::string_view title, std::string_view filename, std::string_view raw_server) const;

  protected:
    std::shared_ptr<simdjson::dom::parser> parser;
    document::common document;
    method::utility method_util;
};
}// namespace method
}// namespace vk

#endif// VK_AUDIO_H
