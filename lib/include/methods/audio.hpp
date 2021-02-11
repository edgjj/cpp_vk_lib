#ifndef VK_AUDIO_H
#define VK_AUDIO_H

#include "document/common_document.hpp"


namespace vk {
class vk_export audio : private base_object {
public:
    explicit audio(std::string_view user_token_) : base_object(user_token_) { };
    explicit audio() = default;
    ~audio() = default;

    std::string get_upload_server() const;
    void save(std::string_view artist, std::string_view title, std::string_view filename, std::string_view raw_server);
};
} // namespace vk

#endif // VK_AUDIO_H
