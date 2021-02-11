#ifndef STRING_UTIL_JOIN_IMPL_H
#define STRING_UTIL_JOIN_IMPL_H

#include <numeric>
#include <string>

#include "misc/cppdefs.hpp"


namespace vk {
namespace string_util {
template <typename T>
std::string join(std::initializer_list<T>&& elements, char delimiter = ',');
} // namespace string_util
} // namespace vk

namespace vk {
namespace string_util {
template <typename T> struct vk_hidden join_implementation {
private:
    using is_integral = std::true_type;
    using is_not_integral = std::false_type;

    template <typename binary_operation>
    static std::string common_implementation(std::initializer_list<T> elements, binary_operation operation) {
        return std::accumulate(elements.begin(), elements.end(), std::string(), operation);
    }

    static std::string create(std::initializer_list<T> elements, char delimiter) {
        return common_implementation(elements, [&delimiter](std::string& accumlator, T element){
            if constexpr (std::is_integral<T>()) {
                return accumlator.empty()
                    ? std::to_string(element)
                    : std::move(accumlator) + delimiter + std::to_string(element);
            } else {
                return accumlator.empty()
                    ? std::string(element)
                    : std::move(accumlator) + delimiter + std::string(element);
            }
        });
    }

    template <typename _T>
    friend std::string vk::string_util::join(std::initializer_list<_T>&& elements, char delimiter);
};
} // namespace string_util
} // namespace vk

#endif // STRING_UTIL_JOIN_IMPL_H
