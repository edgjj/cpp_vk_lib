#include "lib/include/methods/video.hpp"


vk::attachment::attachments_t vk::video::search(std::string_view query, std::int64_t count)
{
    return common_search("video.search", query, count);
}

void vk::video::save_by_link(std::string_view url)
{
    std::string response = call("video.save", user_params({{"link", url.data()}}));
}
