#ifndef BACKTRACE_H
#define BACKTRACE_H

#ifdef __linux__
    #include <cxxabi.h>
    #include <execinfo.h>
#endif

#include <iostream>
#include <vector>

namespace vk {
namespace processing {
/*!
 * @brief Backtrace viewer, used in exceptions.
 */
class backtrace_view
{
  public:
    backtrace_view(const backtrace_view&) = delete;
    backtrace_view(backtrace_view&&) = delete;
    backtrace_view& operator=(const backtrace_view&) = delete;
    backtrace_view& operator=(backtrace_view&&) = delete;
    explicit backtrace_view() noexcept
    {
        generate();
        std::cerr << std::endl;
    }
    ~backtrace_view()
    {
        free(symbol_list);
    }

  private:
#if defined __linux__
    void generate()
    {
        std::cerr << "<backtrace>" << std::endl;
        int backtrace_size = ::backtrace(address_list, sizeof(address_list) / sizeof(void*));
        if (backtrace_size == 0)
        {
            std::cerr << indent << "<empty>" << std::endl;
            return;
        }
        symbol_list = ::backtrace_symbols(address_list, backtrace_size);
        address_loop(backtrace_size);
    }
#else
    void generate()
    {
        std::cerr << "<backtrace>" << std::endl;
        std::cerr << indent << "<empty>" << std::endl;
    }
#endif
    void address_loop(size_t backtrace_size) noexcept
    {
        for (size_t i = 1; i < backtrace_size; i++)
        {
            get_address_info(i);
            print(i);
        }
    }
    void get_address_info(size_t i) noexcept
    {
        for (char* p = symbol_list[i]; *p; ++p)
        {
            switch (*p)
            {
                case '(':
                    begin_name = p;
                    break;
                case '+':
                    begin_offset = p;
                    break;
                case ')':
                    end_offset = p;
                    return;
            }
        }
    }
    void print(size_t i) noexcept
    {
        if (begin_name && begin_offset && end_offset && begin_name < begin_offset)
        {
            char* func_name = new char[max_func_length];
            *begin_name++ = '\0';
            *begin_offset++ = '\0';
            *end_offset++ = '\0';
            print_impl(func_name, i);
        }
        else
        {
            std::cerr << indent << symbol_list[i] << std::endl;
        }
    }
#if defined __linux__
    void print_impl(char* func_name, size_t i) noexcept
    {
        int status = 0;
        char* ret = abi::__cxa_demangle(begin_name, func_name, &max_func_length, &status);
        std::cerr << indent << symbol_list[i] << ": ";
        if (status == 0)
        {
            std::cerr << ret << '+';
        }
        else
        {
            std::cerr << begin_name << "()+";
        }
        std::cerr << begin_offset << std::endl;
        delete[] func_name;
    }
#else
    constexpr void print_impl(char* func_name, size_t i) noexcept
    {
        (void)func_name;
        (void)i;
    }
#endif

    static constexpr const char* indent = "  ";
    static constexpr size_t max_frames = 16;
    size_t max_func_length = 256;
#ifdef __linux__
    void* address_list[max_frames];
#endif
    char** symbol_list = nullptr;
    char* begin_name = nullptr;
    char* begin_offset = nullptr;
    char* end_offset = nullptr;
};
}// namespace processing
}// namespace vk

#endif// BACKTRACE_H
