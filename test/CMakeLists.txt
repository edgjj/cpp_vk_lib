include_directories(../lib/include)
include_directories(../lib/include/cpp_vk_lib)

add_executable(test main.cpp)

find_library(cpp_vk_lib HINTS "../lib")

target_link_libraries(test cpp_vk_lib curl curlpp pthread gtest)
