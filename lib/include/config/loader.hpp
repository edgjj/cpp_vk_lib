#ifndef VK_CONFIG_LOADER_H
#define VK_CONFIG_LOADER_H

#include <string>

#include "misc/cppdefs.hpp"


namespace vk {
namespace config {

class vk_export loader {
public:
  static loader* load(std::string_view path) noexcept(false);
  static loader* get() noexcept(false);
  std::string& user_token_instance() noexcept { return user_token_; }
  std::string user_token() const noexcept { return user_token_; }
  std::string access_token() const noexcept { return access_token_; }
  std::int64_t num_threads() const noexcept { return num_threads_; }

private:
  loader(std::string_view path);

  std::string path_;

  std::string user_token_;
  std::string access_token_;
  std::int8_t num_threads_;

  static loader* instance;
};

inline void load(std::string_view path) { loader::load(path); }
inline std::string user_token() { return loader::get()->user_token(); }
inline void set_user_token(std::string_view token) { loader::get()->user_token_instance() = token; }
inline std::string access_token() { return loader::get()->access_token(); }
inline std::int64_t num_threads() { return loader::get()->num_threads(); }

} // namespace config
} // namespace vk

#endif // VK_CONFIG_LOADER_H
