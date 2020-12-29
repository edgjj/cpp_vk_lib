#include "vkapi/include/methods/video.hpp"

vk::attachment::attachment_list vk::video::search(std::string_view query, long count)
{
  return common_search("docs.search", query, count);
}
