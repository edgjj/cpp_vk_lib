#include "config/loader.hpp"

#include "simdjson.h"

vk::config::loader* vk::config::loader::instance = nullptr;

vk::config::loader* vk::config::loader::load(std::string_view path)
{
    if (!instance) {
        instance = new loader(path);
    }

    return instance;
}

vk::config::loader* vk::config::loader::get()
{
    if (!instance) {
        throw std::runtime_error("Please, load config first.");
    }

    return instance;
}

vk::config::loader::loader(std::string_view path)
{
    simdjson::dom::parser parser;
    const simdjson::dom::element element = parser.load(path.data());

    m_username = element["oauth"]["login"];
    m_password = element["oauth"]["password"];
    m_user_token = element["api"]["user_token"].get_c_str().take_value();
    m_access_token = element["api"]["access_token"].get_c_str().take_value();
    m_error_log_path = element["environment"]["error_log_path"].get_c_str().take_value();
    m_event_log_path = element["environment"]["event_log_path"].get_c_str().take_value();
    m_num_workers = element["environment"]["num_workers"].get_int64();
}
