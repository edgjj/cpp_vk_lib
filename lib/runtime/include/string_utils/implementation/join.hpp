#ifndef RUNTIME_STRING_UTILS_IMPLEMENTATION_JOIN_HPP
#define RUNTIME_STRING_UTILS_IMPLEMENTATION_JOIN_HPP

#include <numeric>
#include <string>

namespace runtime {
namespace string_utils {

template <typename T, typename Container>
std::string join(Container&& elements, char delimiter = ',');

template <typename T>
std::string join(std::initializer_list<T> elements, char delimiter = ',');

}// namespace string_utils
}// namespace runtime

namespace runtime {
namespace string_utils {

template <typename T>
struct join_impl
{
public:
    join_impl() = delete;

private:
    template <typename Container, typename BinaryOperation>
    static std::string implementation(Container&& elements, BinaryOperation operation)
    {
        return std::accumulate(elements.begin(), elements.end(), std::string(), operation);
    }

    template <typename Container>
    static std::string common_create(Container&& elements, char delimiter)
    {
        return implementation(elements, [&delimiter](std::string& accumlator, T element) {
            if constexpr (std::is_integral_v<T>) {
                return accumlator.empty() ? std::to_string(element) : std::move(accumlator) + delimiter + std::to_string(element);
            } else {
                return accumlator.empty() ? std::string(element) : std::move(accumlator) + delimiter + std::string(element);
            }
        });
    }

    template <typename Container>
    static std::string create(Container&& elements, char delimiter)
    {
        return common_create<Container&&>(std::forward<Container>(elements), delimiter);
    }

    template <typename mT, typename Container>
    friend std::string string_utils::join(Container&& elements, char delimiter);

    template <typename mT>
    friend std::string string_utils::join(std::initializer_list<mT> elements, char delimiter);
};

}// namespace string_utils
}// namespace runtime

#endif// RUNTIME_STRING_UTILS_IMPLEMENTATION_JOIN_HPP
