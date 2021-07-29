include_directories(../dependencies)
include_directories(../dependencies/curlpp/include)
include_directories(../dependencies/spdlog/include)

include_directories(include/cpp_vk_lib)

add_definitions(-DAPI_V="5.130")

set(extra_warnings TRUE)
set(find_leaks FALSE)

set(common_flags "-fPIC -Wall -Wextra -pedantic -Wshadow -Wunused-parameter")

if (${find_leaks})
  set(find_leaks_flags "-fsanitize=leak -fstack-protector")
else()
  set(find_leaks_flags "")
endif()

if (${extra_warnings})
  set(extra_warnings_flags "-Wcast-qual -Wnon-virtual-dtor -Wreturn-type -Wsign-promo -Wno-unused -Wcast-align -Woverloaded-virtual -Wno-parentheses")
else()
  set(extra_warnings_flags "")
endif()

set(CMAKE_CXX_FLAGS "${common_flags} ${extra_warnings_flags} ${find_leaks_flags} -O2 -flto")

add_library(lib-simdjson INTERFACE)
target_compile_features(lib-simdjson INTERFACE cxx_std_17)
target_include_directories(lib-simdjson INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCDIR}>)
install(TARGETS lib-simdjson EXPORT simdjson-config INCLUDES DESTINATION dependencies)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS YES CACHE BOOL "Export all symbols")

file(GLOB_RECURSE SRC "*.hpp" "*.cpp")

if(WIN32)
  add_library(cpp_vk_lib STATIC ${SRC})
else()
  add_library(cpp_vk_lib SHARED ${SRC})
endif()

IF(WIN32)
  target_link_libraries(cpp_vk_lib
  	PRIVATE spdlog::spdlog_header_only
    CURL::libcurl
    unofficial::curlpp::curlpp
    simdjson::simdjson
    simdjson::simdjson-flags
    simdjson::simdjson-headers
  )
ELSE()
  target_link_libraries(cpp_vk_lib curl curlpp simdjson)
ENDIF()
