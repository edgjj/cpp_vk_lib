#ifndef BOT_STRING_UTILS_H
#define BOT_STRING_UTILS_H

#include <string>


namespace bot {
namespace string_util {

inline std::string cut_first(std::string_view str) {
  return (str.find(' ') == std::string::npos) ? "" : str.substr(str.find_first_of(' ') + 1).data();
}

inline std::string get_first(std::string_view str) {
  return (str.find(' ') == std::string::npos) ? str.data() : std::string(str.substr(0, str.find(' ')));
}
} // namespace string_util
} // namespace bot

#endif // BOT_STRING_UTILS_H
