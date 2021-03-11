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
class audio {
public:
  explicit audio();
  ~audio();

  std::string get_upload_server() const;
  void save(
    std::string_view artist,
    std::string_view title,
    std::string_view filename,
    std::string_view raw_server
  ) const;
private:
  std::unique_ptr<simdjson::dom::parser> parser;
  document::common common_document;
  method_utils method_util;
};
} // namespace method
} // namespace vk

#endif // VK_AUDIO_H
