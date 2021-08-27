#include "cpp_vk_lib/runtime/stacktrace_dump.hpp"

#include "spdlog/spdlog.h"

#include <cxxabi.h>
#include <execinfo.h>

void runtime::stacktrace_dump()
{
    // clang-format off
#if defined(__unix__ ) || defined(__unix) || \
   (defined(__APPLE__) && defined(__MACH__))
    void* address_list[100];
    int addresses_got = backtrace(address_list, sizeof(address_list) / sizeof(void*));
    if (addresses_got == 0) {
        spdlog::critical("  empty stack trace, exiting...");
        return;
    }
    char** symbol_list = backtrace_symbols(address_list, addresses_got);
    size_t maxframes = 256;
    char* funcname = static_cast<char*>(malloc(maxframes));
    for (int i = 1; i < addresses_got; ++i) {
        char* begin_name = 0, *begin_offset = 0, *end_offset = 0;
        for (char* symbol = symbol_list[i]; *symbol; ++symbol) {
            if (*symbol == '(') {
                begin_name = symbol;
            } else if (*symbol == '+') {
                begin_offset = symbol;
            } else if (*symbol == ')' && begin_offset) {
                end_offset = symbol;
                break;
            }
        }
        if (begin_name && begin_offset && end_offset && begin_name < begin_offset) {
            *begin_name++ = '\0';
            *begin_offset++ = '\0';
            *end_offset = '\0';
            int status = 0;
            char* demangled = abi::__cxa_demangle(begin_name, funcname, &maxframes, &status);
            if (status == 0) {
                funcname = demangled;
                spdlog::critical("  {}: {}+{}", symbol_list[i], funcname, begin_offset);
            } else {
                spdlog::critical("  {}: {}()+{}", symbol_list[i], begin_name, begin_offset);
            }
        } else {
            spdlog::critical("  {}", symbol_list[i]);
        }
    }
    free(funcname);
    free(symbol_list);
#endif// defined __unix__ || defined __APPLE__
    // clang-format on
}
