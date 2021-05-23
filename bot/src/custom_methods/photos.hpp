#ifndef CPP_VK_LIB_PHOTOS_HPP
#define CPP_VK_LIB_PHOTOS_HPP

#include "cpp_vk_lib/methods/photos.hpp"
#include "cpp_vk_lib/string_utils/string_utils.hpp"

namespace bot {

class photos : private vk::method::photos
{
public:
    void create_comment(std::size_t owner_id, std::size_t photo_id, std::string_view message, const vk::attachment::attachments_t& attachments = {})
    {
        m_user_constructor.method("photos.createComment")
            .param("owner_id", std::to_string(owner_id))
            .param("photo_id", std::to_string(photo_id))
            .param("message", message);

        if (!attachments.empty())
        {
            std::vector<std::string> attachment_values;

            std::transform(attachments.begin(), attachments.end(), std::back_inserter(attachment_values),
                [](const std::shared_ptr<vk::attachment::base>& att) {
                    return att->value();
                }
            );

            m_user_constructor
                .param("attachments", vk::string_utils::join<std::string>(attachment_values));
        }

        m_user_constructor.execute();
    }
};
}// namespace bot

#endif// CPP_VK_LIB_PHOTOS_HPP
