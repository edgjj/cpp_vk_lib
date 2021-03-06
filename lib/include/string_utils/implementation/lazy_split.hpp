#ifndef STRING_UTIL_LAZY_SPLIT_IMPL_H
#define STRING_UTIL_LAZY_SPLIT_IMPL_H

// Thanks some-coder366 for the idea.
// https://github.com/some-coder366/cpp-lazy-split/blob/master/split_iterators.cpp

#include <string_view>

#include "misc/cppdefs.hpp"


namespace vk {
namespace string_utils {

struct end_split_iterator { };

template <typename _String_type> class vk_export split_iterator {
public:
  split_iterator(_String_type source, _String_type delim)
    : src(source), delimiter(delim), first(0), last(src.find(delimiter))
   { }
  split_iterator& operator++() noexcept {
    first = last + delimiter.size();
    last = src.find(delimiter, first);
    return *this;
  }
  _String_type operator*() const noexcept {
    if (last != _String_type::npos) { return src.substr(first, last - first); }
    finished = true;
    return src.substr(first, src.size() - first);
  }
  friend bool operator!=(const split_iterator& iterator, end_split_iterator) noexcept {
    return !iterator.finished;
  }
  friend bool operator!=(end_split_iterator, const split_iterator& iterator) noexcept {
    return !iterator.finished;
  }

private:
  _String_type src;
  _String_type delimiter;
  std::size_t first;
  std::size_t last;
  mutable bool finished = false;
};

template <typename _String_type>
class vk_export split_range {
public:
  split_range(_String_type source, _String_type delim) noexcept
    : src(source), delimiter(delim)
  { }
  auto begin() const noexcept { return split_iterator<_String_type>(src, delimiter); }
  auto end() const noexcept { return end_split_iterator(); }

private:
  _String_type src;
  _String_type delimiter;
};
} // namespace string_util
} // namespace vk

#endif // STRING_UTIL_LAZY_SPLIT_IMPL_H
