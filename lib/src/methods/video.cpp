#include "methods/video.hpp"


vk::method::video::video()
  : method_util()
  , document()
{ }

vk::method::video::video(std::string_view user_token)
  : method_util(user_token.data())
  , document(user_token.data())
{ }

vk::attachment::attachments_t vk::method::video::search(
    std::string_view query,
    std::int64_t count
) const {
  return document.search("video.search", query, count);
}

void vk::method::video::save_by_link(std::string_view url) const {
  std::string response =
    method_util.call("video.save", method_util.user_args({{"link", url.data()}}));
}
