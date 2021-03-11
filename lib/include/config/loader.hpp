#ifndef VK_CONFIG_LOADER_H
#define VK_CONFIG_LOADER_H

#include <string>

#include "misc/cppdefs.hpp"


namespace vk {
namespace config {
/*!
 * @brief Config class with its helper functions.
 *
 * Implemented as singleton to avoid multiply and senseless JSON file read.
 * Please, don't try to use this class directly, use non-member functions instead.
 */
class loader {
public:
  loader(const loader&) = delete;
  loader(loader&&) = delete;
  loader& operator=(const loader&) = delete;
  loader& operator=(loader&&) = delete;

  static loader* load(std::string_view path);
  static loader* get();
  static void deallocate();

  std::string& user_token_instance() noexcept { return user_token_; }
  std::string user_token()     const noexcept { return user_token_; }
  std::string access_token()   const noexcept { return access_token_; }
  std::string error_logpath()  const noexcept { return error_logpath_; }
  std::string event_logpath()  const noexcept { return event_logpath_; }
  std::int64_t num_threads()   const noexcept { return num_threads_; }

private:
  loader(std::string_view path);

  std::string user_token_;
  std::string access_token_;
  std::string error_logpath_;
  std::string event_logpath_;
  std::int8_t num_threads_;

  static loader* instance;
};

inline void load(std::string_view path) { loader::load(path); }
inline void deallocate() { loader::deallocate(); }
inline void set_user_token(std::string_view token) { loader::get()->user_token_instance() = token; }
inline std::string user_token()     noexcept { return loader::get()->user_token(); }
inline std::string access_token()   noexcept { return loader::get()->access_token(); }
inline std::string error_logpath()  noexcept { return loader::get()->error_logpath(); }
inline std::string event_logpath()  noexcept { return loader::get()->event_logpath(); }
inline std::int64_t num_threads()   noexcept { return loader::get()->num_threads(); }

} // namespace config
} // namespace vk

#endif // VK_CONFIG_LOADER_H
