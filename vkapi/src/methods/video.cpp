#include "vkapi/include/methods/video.hpp"

vk::attachment::attachment_list vk::video::search(std::string_view query, long count) const
{
  return common_search("video.search", query, count);
}
