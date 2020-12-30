#pragma once

#include "vkapi/include/events/message_new.hpp"
#include "vkapi/include/methods/messages.hpp"
#include "vkapi/include/methods/docs.hpp"
#include "vkapi/include/methods/video.hpp"
#include "vkapi/include/methods/photos.hpp"


void search_docs(const vk::event::message_new& update, vk::messages& messages)
{
  vk::docs docs;
  vk::attachment::attachment_list media = docs.search(update.text(), 10);

  (media.empty())
    ? messages.send(update.peer_id(), "no docs")
    : messages.send(update.peer_id(), "docs: ", media);
}


void search_videos(const vk::event::message_new& update, vk::messages& messages)
{
  vk::video video;
  vk::attachment::attachment_list media = video.search(update.text(), 10);

  (media.empty())
    ? messages.send(update.peer_id(), "no videos")
    : messages.send(update.peer_id(), "videos: ", media);
}


void search_photos(const vk::event::message_new& update, vk::messages& messages)
{
  vk::photos photos;
  vk::attachment::attachment_list media = photos.search(update.text(), 10);

  (media.empty())
    ? messages.send(update.peer_id(), "no photos")
    : messages.send(update.peer_id(), "photos: ", media);
}
