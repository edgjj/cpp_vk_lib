#ifndef VK_ATTACHMENT_HPP
#define VK_ATTACHMENT_HPP

#include "exception/exception.hpp"
#include "string_utils/string_utils.hpp"

#include <memory>
#include <string>
#include <vector>

namespace vk {
/*!
 * @namespace Different attachment types and cast function to it.
 */
namespace attachment {

class base
{
public:
    explicit base(std::string_view type, int32_t owner_id, int32_t id)
        : m_attachment_type(type)
        , m_owner_id(owner_id)
        , m_id(id) {}

    virtual ~base() = default;

    std::string value() const
    {
        return string_utils::format("{}{}_{}", m_attachment_type, m_owner_id, m_id);
    }

    const std::string& type() const noexcept
    {
        return m_attachment_type;
    }

private:
    std::string m_attachment_type;
    int32_t m_owner_id;
    int32_t m_id;
};

class photo : public base
{
public:
    explicit photo(int32_t owner_id, int32_t id)
        : base("photo", owner_id, id) {}
};

class video : public base
{
public:
    explicit video(int32_t owner_id, int32_t id)
        : base("video", owner_id, id) {}
};

class audio : public base
{
public:
    explicit audio(int32_t owner_id, int32_t id)
        : base("audio", owner_id, id) {}
};

class document : public base
{
public:
    explicit document(int32_t owner_id, int32_t id, std::string_view url)
        : base("doc", owner_id, id)
        , m_raw_url(url) {}

    const std::string& raw_url() const noexcept
    {
        return m_raw_url;
    }

private:
    std::string m_raw_url;
};

class wall : public base
{
public:
    explicit wall(int32_t id, int32_t from_id)
        : base("wall", from_id, id) {}
};

class audio_message : public base
{
public:
    explicit audio_message(int32_t owner_id, int32_t id, std::string_view raw_ogg, std::string_view raw_mp3)
        : base("audio_message", owner_id, id)
        , m_raw_ogg(raw_ogg)
        , m_raw_mp3(raw_mp3) {}

    const std::string& raw_ogg() const noexcept
    {
        return m_raw_ogg;
    }

    const std::string& raw_mp3() const noexcept
    {
        return m_raw_mp3;
    }

private:
    std::string m_raw_ogg;
    std::string m_raw_mp3;
};

template <typename Attachment>
std::shared_ptr<Attachment> cast(const std::shared_ptr<base>& pointer)
{
    if (auto* casted = static_cast<Attachment*>(pointer.get())) {
        return std::shared_ptr<Attachment>(pointer, casted);
    }

    throw exception::bad_cast_error<base, Attachment>();
}

using attachments_t = std::vector<std::shared_ptr<attachment::base>>;

}// namespace attachment
}// namespace vk

#endif// VK_ATTACHMENT_HPP
