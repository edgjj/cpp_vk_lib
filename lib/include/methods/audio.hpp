#ifndef VK_AUDIO_H
#define VK_AUDIO_H

#include "document/common_document.hpp"


namespace vk {
/*!
 * @brief The audio methods representation.
 *
 * Please, inherit this class to add new methods.
 */
class vk_export audio : protected service {
public:
  explicit audio(std::string_view user_token_) : service(user_token_) { };
  explicit audio() = default;
  ~audio() = default;

  std::string get_upload_server() const;
  void save(std::string_view artist, std::string_view title, std::string_view filename, std::string_view raw_server);
};
} // namespace vk

#endif // VK_AUDIO_H
