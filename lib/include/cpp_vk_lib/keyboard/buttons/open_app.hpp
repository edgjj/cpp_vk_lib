#ifndef VK_OPEN_APP_BUTTON_H
#define VK_OPEN_APP_BUTTON_H

#include "string_utils/string_utils.hpp"

namespace vk {
namespace keyboard {
namespace button {

class open_app
{
public:
    open_app(std::int64_t app_id_, std::int64_t owner_id_, std::string_view hash_, std::string_view label_)
      : m_app_id(app_id_)
      , m_owner_id(owner_id_)
      , m_hash(hash_)
      , m_label(label_)
    {}
    std::string serialize() const
    {
        return string_utils::format(
            R"({"action":{"type":"open_app","app_id":{},"owner_id":{},"hash":"{}","label":"{}"}})",
            m_app_id,
            m_owner_id,
            m_hash,
            m_label);
    }

private:
    std::int64_t m_app_id;
    std::int64_t m_owner_id;
    std::string m_hash;
    std::string m_label;
};
}// namespace button
}// namespace keyboard
}// namespace vk

#endif// VK_OPEN_APP_BUTTON_H
