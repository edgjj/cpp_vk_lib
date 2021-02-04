include_directories(../lib/include)
include_directories(../dependencies/simdjson/include)
include_directories(../dependencies)

add_executable(
    worker main.cpp
)

target_link_libraries(worker -Lshared cpp_vk_lib pthread curl curlpp -L../dependencies/simdjson simdjson)
