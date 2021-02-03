cmake_minimum_required(VERSION 3.5)

project(worker LANGUAGES CXX)

set(LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)
set(ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)
set(RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/execute)

include_directories(../)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS
    "-O2 -Wall"
)
add_executable(
    worker main.cpp
)
set_target_properties(
    worker PROPERTIES
    CMAKE_BUILD_WITH_INSTALL_RPATH TUE
    LINKER_LANGUAGES CXX
    LINK_FLAGS "-Wl,-rpath,.."
    SKIP_BUILD_RPATH FALSE
)
target_link_libraries(worker -L.. cpp_vk_lib pthread curl curlpp simdjson)
