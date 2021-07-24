#ifndef VK_STRING_UTILS_IMPLEMENTATION_LAZY_SPLIT_HPP
#define VK_STRING_UTILS_IMPLEMENTATION_LAZY_SPLIT_HPP

// Thanks some-coder366 for the idea.
// https://github.com/some-coder366/cpp-lazy-split/blob/master/split_iterators.cpp

#include <string_view>

namespace vk {
namespace string_utils {

struct end_split_iterator {};

template <typename StringType>
class split_iterator
{
public:
    split_iterator(StringType&& source, StringType&& delim)
        : src(std::forward<StringType>(source))
        , delimiter(std::forward<StringType>(delim))
        , first(0)
        , last(src.find(delimiter)) {}

    split_iterator& operator++() noexcept
    {
        first = last + delimiter.size();
        last = src.find(delimiter, first);
        return *this;
    }
    StringType operator*() const noexcept
    {
        if (last != StringType::npos) {
            return src.substr(first, last - first);
        }

        finished = true;

        return src.substr(first, src.size() - first);
    }
    friend bool operator!=(const split_iterator& iterator, end_split_iterator) noexcept
    {
        return !iterator.finished;
    }
    friend bool operator!=(end_split_iterator, const split_iterator& iterator) noexcept
    {
        return !iterator.finished;
    }

private:
    StringType src;
    StringType delimiter;
    size_t first;
    size_t last;
    mutable bool finished = false;
};

template <typename StringType>
class split_range
{
public:
    split_range(StringType source, StringType delim) noexcept
        : src(source)
        , delimiter(delim) {}

    auto begin() const noexcept
    {
        return split_iterator<StringType>(src, delimiter);
    }

    auto end() const noexcept
    {
        return end_split_iterator();
    }

private:
    StringType src;
    StringType delimiter;
};

}// namespace string_utils
}// namespace vk

#endif// VK_STRING_UTILS_IMPLEMENTATION_LAZY_SPLIT_HPP
