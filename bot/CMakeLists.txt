include_directories(../lib/include)
include_directories(../lib/include/cpp_vk_lib)

file(GLOB_RECURSE SRC "*.hpp" "*.cpp")
add_executable(bot ${SRC})

target_link_libraries(bot -Lbuild cpp_vk_lib pthread curl curlpp -L../dependencies/simdjson simdjson)
