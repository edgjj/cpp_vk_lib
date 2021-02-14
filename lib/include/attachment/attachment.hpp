#ifndef VK_ATTACHMENT_H
#define VK_ATTACHMENT_H

#include <string>
#include <memory>
#include <vector>

#include "misc/cppdefs.hpp"


namespace vk {
namespace attachment {
class vk_export base_attachment {
public:
    explicit
    base_attachment (std::int32_t owner_id_, std::int32_t id_)
        : owner_id(owner_id_), id(id_)
    { }
    virtual ~base_attachment() = default;
    virtual std::string value() const noexcept = 0;
    virtual std::string type()  const noexcept = 0;

protected:
    std::int32_t owner_id;
    std::int32_t id;
};

class vk_export photo_attachment : public base_attachment {
public:
    explicit
    photo_attachment(std::int32_t owner_id_, std::int32_t id_)
        : base_attachment(owner_id_, id_)
    { }
    std::string value() const noexcept override { return "photo" + std::to_string(owner_id) + '_' + std::to_string(id); }
    std::string type()  const noexcept override { return "photo"; }
};

class vk_export video_attachment : public base_attachment {
public:
    explicit
    video_attachment(std::int32_t owner_id_, std::int32_t id_)
        : base_attachment(owner_id_, id_)
    { }
    std::string value() const noexcept override { return "video" + std::to_string(owner_id) + '_' + std::to_string(id); }
    std::string type()  const noexcept override { return "video"; }
};

class vk_export audio_attachment : public base_attachment {
public:
    explicit
    audio_attachment(std::int32_t owner_id_, std::int32_t id_)
        : base_attachment(owner_id_, id_)
    { }
    std::string value() const noexcept override { return "audio" + std::to_string(owner_id) + '_' + std::to_string(id); }
    std::string type()  const noexcept override { return "audio"; }
};

class vk_export document_attachment : public base_attachment {
public:
    explicit
    document_attachment(std::int32_t owner_id_, std::int32_t id_, std::string_view url)
        : base_attachment(owner_id_, id_), _raw_url(url.data())
    { }
    std::string value()   const noexcept override { return "doc" + std::to_string(owner_id) + '_' + std::to_string(id); }
    std::string type()    const noexcept override { return "doc"; }
    std::string raw_url() const noexcept { return _raw_url; }

private:
    const char* _raw_url;
};

class vk_export audio_message_attachment : public base_attachment {
public:
    explicit
    audio_message_attachment(std::int32_t owner_id_, std::int32_t id_, std::string_view raw_ogg, std::string_view raw_mp3)
        : base_attachment(owner_id_, id_), _raw_ogg(raw_ogg.data()), _raw_mp3(raw_mp3.data())
    { }
    std::string value()   const noexcept override { return "audio_message" + std::to_string(owner_id) + '_' + std::to_string(id); }
    std::string type()    const noexcept override { return "audio_message"; }
    std::string raw_ogg() const noexcept { return _raw_ogg; }
    std::string raw_mp3() const noexcept { return _raw_mp3; }

private:
    const char* _raw_ogg;
    const char* _raw_mp3;
};

class vk_export wall_attachment : public base_attachment {
public:
    explicit
    wall_attachment(std::int32_t id_, std::int32_t from_id_)
        : base_attachment(from_id_, id_)
    { }
    std::string value()   const noexcept override { return "wall" + std::to_string(owner_id) + '_' + std::to_string(id); }
    std::string type()    const noexcept override { return "wall"; }
};

inline std::shared_ptr<photo_attachment> static_photo_cast(const std::shared_ptr<base_attachment>& pointer) noexcept {
    return std::static_pointer_cast<photo_attachment>(pointer);
}
inline std::shared_ptr<audio_attachment> static_audio_cast(const std::shared_ptr<base_attachment>& pointer) noexcept {
    return std::static_pointer_cast<audio_attachment>(pointer);
}
inline std::shared_ptr<video_attachment> static_video_cast(const std::shared_ptr<base_attachment>& pointer) noexcept {
    return std::static_pointer_cast<video_attachment>(pointer);
}
inline std::shared_ptr<document_attachment> static_document_cast(const std::shared_ptr<base_attachment>& pointer) noexcept {
    return std::static_pointer_cast<document_attachment>(pointer);
}
inline std::shared_ptr<audio_message_attachment> static_audio_message_cast(const std::shared_ptr<base_attachment>& pointer) noexcept {
    return std::static_pointer_cast<audio_message_attachment>(pointer);
}
inline std::shared_ptr<wall_attachment> static_wall_cast(const std::shared_ptr<base_attachment>& pointer) noexcept {
    return std::static_pointer_cast<wall_attachment>(pointer);
}

using attachments_t = std::vector<std::shared_ptr<attachment::base_attachment>>;
const inline std::shared_ptr<vk::attachment::base_attachment> undefined_attachment = std::make_shared<vk::attachment::photo_attachment>(-1, -1);
} // namespace attachment
} // namespace vk
#endif // VK_ATTACHMENT_H
