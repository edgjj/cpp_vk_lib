include_directories(../lib/include)
include_directories(../dependencies/simdjson/include)
include_directories(../dependencies)

set(SOURCES main.cpp)

add_executable(test ${SOURCES})

target_link_libraries(test -Lbuild cpp_vk_lib gtest pthread curl curlpp -L../dependencies/simdjson simdjson)
