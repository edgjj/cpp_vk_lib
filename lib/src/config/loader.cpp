#include "simdjson.h"

#include "config/loader.hpp"


vk::config::loader* vk::config::loader::instance = nullptr;

vk::config::loader* vk::config::loader::load(std::string_view path) {
  if (!instance) {
    instance = new loader(path);
  }
  return instance;
}

vk::config::loader* vk::config::loader::get() {
  if (!instance) {
    throw std::runtime_error("Please, load config first.");
  }
  return instance;
}

vk::config::loader::loader(std::string_view path)
  : path_(path)
{
  simdjson::dom::parser parser;
  simdjson::dom::element element = parser.load(path.data());

  user_token_ = element["user_token"].get_string().take_value().data();
  access_token_ = element["access_token"].get_string().take_value().data();
  num_threads_ = element["num_threads"].get_int64();
}
