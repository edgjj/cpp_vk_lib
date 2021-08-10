#ifndef RUNTIME_STRING_UTILS_IMPLEMENTATION_JOIN_HPP
#define RUNTIME_STRING_UTILS_IMPLEMENTATION_JOIN_HPP

#include <numeric>
#include <string>

namespace runtime::string_utils::implementation {

template <typename Container, typename BinaryOperation>
static std::string join_implementation(Container&& elements, BinaryOperation operation)
{
    return std::accumulate(elements.begin(), elements.end(), std::string(), operation);
}

template <typename T, typename Container>
static std::string create_joined_string(Container&& elements, char delimiter)
{
    return join_implementation(elements, [&delimiter](std::string& accumlator, T element) {
        if constexpr (std::is_integral_v<T>) {
            return accumlator.empty() ? std::to_string(element) : accumlator + delimiter + std::to_string(element);
        } else {
            return accumlator.empty() ? std::string(element) : accumlator + delimiter + std::string(element);
        }
    });
}

template <typename T, typename Container>
static std::string join(Container&& elements, char delimiter)
{
    return create_joined_string<T, Container&&>(std::forward<Container>(elements), delimiter);
}

}// namespace runtime::string_utils::implementation

#endif// RUNTIME_STRING_UTILS_IMPLEMENTATION_JOIN_HPP
