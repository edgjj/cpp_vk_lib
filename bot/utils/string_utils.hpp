#ifndef BOT_STRING_UTILS_H
#define BOT_STRING_UTILS_H

#include <string>


namespace string_util {
std::string cut_first(std::string_view str) {
    return (str.find(' ') == std::string::npos) ? "" : str.substr(str.find_first_of(' ') + 1).data();
}

std::string get_first(std::string_view str) {
    return (str.find(' ') == std::string::npos) ? "" : std::string(str.substr(0, str.find(' ')));
}
} // namespace string_util

#endif // BOT_STRING_UTILS_H
