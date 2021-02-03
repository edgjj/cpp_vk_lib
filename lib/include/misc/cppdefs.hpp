#ifndef VK_CPPDEFS_H
#define VK_CPPDEFS_H

#if defined (__GNUC__)
#   define _DECL_VK_EXPORT __attribute__((visibility("default")))
#   define _DECL_VK_IMPORT __attribute__((visibility("default")))
#   define _DECL_VK_HIDDEN __attribute__((visibility("hidden")))
#elif defined (_MSC_VER) || defined (WIN64) || defined (_WIN64) || defined (WIN32) || defined (_WIN32)
#   define _DECL_VK_EXPORT __declspec(dllexport)
#   define _DECL_VK_IMPORT __declspec(dllimport)
#   define _DECL_VK_HIDDEN
#else
#   warning Unknown dynamic link import/export semantics.
#   define _DECL_VK_EXPORT
#   define _DECL_VK_IMPORT
#   define _DECL_VK_HIDDEN
#endif

#if defined(VK_CPPDEFS_H)
#   define VK_EXPORT _DECL_VK_EXPORT
#else
#   define VK_EXPORT _DECL_VK_IMPORT
#endif
#   define VK_HIDDEN _DECL_VK_HIDDEN

#define DISABLE_COPY(type)                      \
    type(const type&) = delete;                 \
    type& operator = (const type&) = delete;    \

#define DISABLE_MOVE(type)                      \
    type(type&&) = delete;                      \
    type& operator = (type&&) = delete;         \

#define DEBUG_WATCH(LABEL, EXPR) \
    std::cerr << #LABEL << ": " << EXPR << std::endl;

#define DEBUG_TRACE(expr) \
    std::cerr << __FILE__ << ':' << __LINE__ << ": <" << __FUNCTION__ << "> " << #expr << " = " << expr << std::endl;

#define VK_ALWAYS_INLINE [[gnu::always_inline]]

#endif // VK_CPPDEFS_H
