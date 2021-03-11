include_directories(../lib/include)
include_directories(../lib/include/cpp_vk_lib)

add_executable(test main.cpp)

target_link_libraries(test -Lbuild cpp_vk_lib gtest pthread curl curlpp -L../dependencies/simdjson simdjson)
