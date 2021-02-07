#ifndef SEPARATED_LIST_IMPL_H
#define SEPARATED_LIST_IMPL_H

#include <numeric>
#include <string>


namespace vk
{
namespace string_util
{
template <typename T>
std::string separated_list(std::initializer_list<T>&& elements, char delimiter = ',');
} // namespace string_util
} // namespace vk

namespace vk
{
namespace string_util
{
template <typename T> struct separated_list_implementation
{
private:
    using is_integral = std::true_type;
    using is_not_integral = std::false_type;

    template <typename Binary_operation>
    static std::string common_implementation(std::initializer_list<T> elements, Binary_operation operation)
    {
        return std::accumulate(elements.begin(), elements.end(), std::string(), operation);
    }

    static std::string create(std::initializer_list<T> elements, char delimiter, is_integral)
    {
        return common_implementation(
            elements, [&delimiter](std::string& accumlator, T element){
                return accumlator.empty()
                    ? std::to_string(element)
                    : std::move(accumlator) + delimiter + std::to_string(element);
            }
        );
    }

    static std::string create(std::initializer_list<T> elements, char delimiter, is_not_integral)
    {
        return common_implementation(
            elements, [&delimiter](std::string& accumlator, T element){
                return accumlator.empty()
                    ? std::string(element)
                    : std::move(accumlator) + delimiter + std::string(element);
            }
        );
    }

    friend std::string vk::string_util::separated_list(std::initializer_list<T>&& elements, char delimiter);
};
} // namespace string_util
} // namespace vk

#endif // SEPARATED_LIST_IMPL_H
