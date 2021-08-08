add_definitions(-DAPI_V="5.130")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -Wall -Wextra -Werror -Wunused -Wwrite-strings -Wimplicit-fallthrough -pedantic -O3")

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS YES CACHE BOOL "Export all symbols")

file(GLOB_RECURSE SRC "*.hpp" "*.cpp")

if (CPP_VK_LIB_STATIC_BUILD)
  add_library(cpp_vk_lib STATIC ${SRC})
else()
  add_library(cpp_vk_lib SHARED ${SRC})
endif()

target_link_libraries(cpp_vk_lib curl curlpp simdjson)

set (CMAKE_INCLUDE_CURRENT_DIR ON)
#target_include_directories(cpp_vk_lib PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(cpp_vk_lib PRIVATE ../dependencies/curlpp/include)
target_include_directories(cpp_vk_lib PRIVATE ../dependencies/spdlog/include)
include_directories(../dependencies/asio/asio/include)
