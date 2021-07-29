include_directories(../dependencies/curlpp/include)
include_directories(../dependencies/spdlog/include)

include_directories(include/cpp_vk_lib)

add_definitions(-DAPI_V="5.130")

set(EXTRA_WARNS TRUE)
set(FIND_LEAKS  FALSE)

if (${FIND_LEAKS})
  set(find_leaks_flags "-fsanitize=leak -fstack-protector")
else()
  set(find_leaks_flags "")
endif()

if (${EXTRA_WARNS})
  set(extra_warnings_flags "-Wcast-qual -Wnon-virtual-dtor -Wreturn-type -Wsign-promo -Wno-unused -Wcast-align -Woverloaded-virtual -Wno-parentheses")
else()
  set(extra_warnings_flags "")
endif()

set(CMAKE_CXX_FLAGS "${extra_warnings_flags} ${find_leaks_flags} -fPIC -Wall -Wextra -pedantic -Wshadow -Wunused-parameter -O2 -flto")

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS YES CACHE BOOL "Export all symbols")

file(GLOB_RECURSE SRC "*.hpp" "*.cpp")

add_library(cpp_vk_lib SHARED ${SRC})

#if (WIN32)
#    set_target_properties(cpp_vk_lib PROPERTIES
#        LINK_FLAGS "/WHOLEARCHIVE"
#    )
#elseif (APPLE)
#    set_target_properties(cpp_vk_lib PROPERTIES
#        LINK_FLAGS "-Wl,-all_load"
#    )
#else ()
#    set_target_properties(cpp_vk_lib PROPERTIES
#        LINK_FLAGS "-Wl,--whole-archive"
#    )
#endif ()

target_link_libraries(cpp_vk_lib curl curlpp simdjson)
