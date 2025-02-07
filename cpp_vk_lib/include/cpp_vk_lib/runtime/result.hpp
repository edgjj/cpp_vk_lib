#ifndef RUNTIME_RESULT_HPP
#define RUNTIME_RESULT_HPP

#include <cstddef>
#include <string>
#include <utility>

namespace runtime {

/*!
 * Error object (Second) must have implicit or explicit operator bool().
 */
template <typename First, typename Second>
struct result : protected std::pair<First, Second>
{
    result() noexcept
        : result(First{}, Second{})
    {}

    result(First&& value) noexcept
        : result(std::forward<First>(value), Second{})
    {}

    result(First&& value, Second&& error) noexcept
        : std::pair<First, Second>(
              std::forward<First>(value),
              std::forward<Second>(error))
    {}

    void set_error(Second&& error) noexcept
    {
        this->second = std::forward<Second>(error);
    }

    void tie(First& value, Second& error) noexcept
    {
        error = this->second;
        if (!error) {
            value = std::forward<result<First, Second>>(*this).first;
        }
    }

    Second error() const noexcept
    {
        return this->second;
    }

    First value() const noexcept
    {
        return this->first;
    }
};

}// namespace runtime

#endif// RUNTIME_RESULT_HPP
