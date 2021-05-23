#ifndef VK_ATTACHMENT_H
#define VK_ATTACHMENT_H

#include <memory>
#include <string>
#include <vector>

#include "exception/exception.hpp"

namespace vk {
/*!
 * @namespace Different attachment types and cast function to it.
 */
namespace attachment {

class base
{
public:
    explicit base(std::string_view type_, std::int32_t owner_id_, std::int32_t id_)
      : m_attachment_type(type_)
      , m_owner_id(owner_id_)
      , m_id(id_)
    {}

    virtual ~base() = default;

    std::string value() const noexcept
    {
        return m_attachment_type + std::to_string(m_owner_id) + '_' + std::to_string(m_id);
    }

    std::string_view type() const noexcept
    {
        return m_attachment_type;
    }

private:
    std::string m_attachment_type;
    std::int32_t m_owner_id;
    std::int32_t m_id;
};

class photo : public base
{
public:
    explicit photo(std::int32_t owner_id_, std::int32_t id_)
      : base("photo", owner_id_, id_)
    {}
};

class video : public base
{
public:
    explicit video(std::int32_t owner_id_, std::int32_t id_)
      : base("video", owner_id_, id_)
    {}
};

class audio : public base
{
public:
    explicit audio(std::int32_t owner_id_, std::int32_t id_)
      : base("audio", owner_id_, id_)
    {}
};

class document : public base
{
public:
    explicit document(std::int32_t owner_id, std::int32_t id, std::string_view url)
      : base("doc", owner_id, id)
      , m_raw_url(url)
    {}

    std::string_view raw_url() const noexcept
    {
        return m_raw_url;
    }

private:
    std::string m_raw_url;
};

class wall : public base
{
public:
    explicit wall(std::int32_t id, std::int32_t from_id)
      : base("wall", from_id, id)
    {}
};

class audio_message : public base
{
public:
    explicit audio_message(std::int32_t owner_id, std::int32_t id, std::string_view raw_ogg, std::string_view raw_mp3)
      : base("audio_message", owner_id, id)
      , m_raw_ogg(raw_ogg)
      , m_raw_mp3(raw_mp3)
    {}

    std::string_view raw_ogg() const noexcept
    {
        return m_raw_ogg;
    }

    std::string_view raw_mp3() const noexcept
    {
        return m_raw_mp3;
    }

private:
    std::string m_raw_ogg;
    std::string m_raw_mp3;
};

template<typename Base, typename Derived>
std::shared_ptr<Derived> static_pointer_cast(const std::shared_ptr<Base>& pointer)
{
    if (auto* casted = static_cast<Derived*>(pointer.get()))
    {
        return std::shared_ptr<Derived>(pointer, casted);
    }

    throw exception::bad_cast_error<Base, Derived>();
}

template <typename Attachment>
std::shared_ptr<Attachment> cast(const std::shared_ptr<base>& pointer)
{
    return ::vk::attachment::static_pointer_cast<base, Attachment>(pointer);
}

using attachments_t = std::vector<std::shared_ptr<attachment::base>>;

}// namespace attachment
}// namespace vk

#endif// VK_ATTACHMENT_H
