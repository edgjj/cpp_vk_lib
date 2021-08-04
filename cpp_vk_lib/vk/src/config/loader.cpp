#include "vk/include/config/loader.hpp"

#include "runtime/include/misc/cppdefs.hpp"

#include "simdjson.h"
#include "spdlog/spdlog.h"

#include <fstream>

namespace {

class loader
{
public:
    VK_DISABLE_COPY_MOVE(loader)

    static loader* load(std::string_view path);
    static loader* load_string(std::string_view string);
    static loader* get();

    std::string& user_token_instance()        noexcept;
    const std::string& username()       const noexcept;
    const std::string& password()       const noexcept;
    const std::string& user_token()     const noexcept;
    const std::string& access_token()   const noexcept;
    const std::string& log_path()       const noexcept;
    int64_t num_workers()               const noexcept;

private:
    loader(std::string_view path);

    std::string m_username{};
    std::string m_password{};
    std::string m_user_token{};
    std::string m_access_token{};
    std::string m_log_path{};
    int64_t m_num_workers{};

    static loader* instance;
};

}// anonymous namespace

loader::loader(std::string_view path)
{
    simdjson::dom::parser parser;
    const simdjson::dom::element element = parser.load(path.data());

    m_username = element["oauth"]["login"];
    m_password = element["oauth"]["password"];
    m_user_token = element["api"]["user_token"].get_c_str().take_value();
    m_access_token = element["api"]["access_token"].get_c_str().take_value();
    m_log_path = element["environment"]["log_path"].get_c_str().take_value();
    m_num_workers = element["environment"]["num_workers"].get_int64();

    spdlog::info("config loaded successfully");
}

loader* loader::instance = nullptr;

loader* loader::load(std::string_view path)
{
    if (!instance) {
        instance = new loader(path);
    }

    return instance;
}

loader* loader::load_string(std::string_view string)
{
    std::ofstream{"created_config.json"} << string;
    return load("created_config.json");
}

loader* loader::get()
{
    if (!instance) {
        throw std::runtime_error("Please, load config first.");
    }

    return instance;
}

std::string& loader::user_token_instance() noexcept { return m_user_token; }
const std::string& loader::username() const noexcept { return m_username; }
const std::string& loader::password() const noexcept { return m_password; }
const std::string& loader::user_token() const noexcept { return m_user_token; }
const std::string& loader::access_token() const noexcept { return m_access_token; }
const std::string& loader::log_path() const noexcept { return m_log_path; }
int64_t loader::num_workers() const noexcept { return m_num_workers; }

void vk::config::load(std::string_view path) { loader::load(path); }
void vk::config::load_string(std::string_view string) { loader::load_string(string); }
void vk::config::set_user_token(std::string_view token) { loader::get()->user_token_instance() = token; }

std::string vk::config::password()     { return loader::get()->password(); }
std::string vk::config::username()     { return loader::get()->username(); }
std::string vk::config::user_token()   { return loader::get()->user_token(); }
std::string vk::config::access_token() { return loader::get()->access_token(); }
std::string vk::config::log_path()     { return loader::get()->log_path(); }
int64_t vk::config::num_workers()      { return loader::get()->num_workers(); }
