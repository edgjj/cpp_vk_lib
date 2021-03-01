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

void vk::config::loader::deallocate() {
  if (instance)
    delete instance;
}

vk::config::loader::loader(std::string_view path)
  : path_(path)
{
  simdjson::dom::parser parser;
  simdjson::dom::element element = parser.load(path.data());

  user_token_ = element["api_keys"]["user_token"].get_c_str().take_value();
  access_token_ = element["api_keys"]["access_token"].get_c_str().take_value();
  error_logpath_ = element["environment"]["error_logpath"].get_c_str().take_value();
  event_logpath_ = element["environment"]["event_logpath"].get_c_str().take_value();
  num_threads_ = element["num_threads"].get_int64();
}
