#include "config/loader.hpp"

#include "simdjson.h"

vk::config::loader* vk::config::loader::instance = nullptr;

vk::config::loader* vk::config::loader::load(std::string_view path)
{
    if (!instance)
    {
        instance = new loader(path);
    }
    return instance;
}

vk::config::loader* vk::config::loader::get()
{
    if (!instance)
    {
        throw std::runtime_error("Please, load config first.");
    }
    return instance;
}

vk::config::loader::loader(std::string_view path)
{
    simdjson::dom::parser parser;
    simdjson::dom::element element = parser.load(path.data());

    username_ = element["oauth"]["login"];
    password_ = element["oauth"]["password"];
    user_token_ = element["api"]["user_token"].get_c_str().take_value();
    access_token_ = element["api"]["access_token"].get_c_str().take_value();
    error_logpath_ = element["environment"]["error_logpath"].get_c_str().take_value();
    event_logpath_ = element["environment"]["event_logpath"].get_c_str().take_value();
    num_workers_ = element["environment"]["num_workers"].get_int64();
}
