cmake_minimum_required(VERSION 3.19)

project(cpp_vk_lib DESCRIPTION "C++ vk library" LANGUAGES CXX)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ../build)
set(EXECUTABLE_OUTPUT_PATH ../build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../build)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_MACOSX_RPATH OFF)
set(CMAKE_THREAD_PREFER_PTHREAD ON)
set(THREADS_PREFER_PTHREAD_FLAG ON)
set(CMAKE_VERBOSE_MAKEFILE OFF)

set(BUILD_SHARED_LIBS ON CACHE BOOL "Link simdjson as shared library")

set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 0)
set(PROJECT_VERSION_PATCH 1)

add_subdirectory(dependencies)
add_subdirectory(lib)

find_library(cpp_vk_lib HINTS "lib")
include_directories(lib/include)
include_directories(lib/include/cpp_vk_lib)
include_directories(dependencies/spdlog/include)

enable_testing()

function (add_vk_test test_name test_path)
  add_executable(${test_name} ${test_path})
  target_link_libraries(${test_name} cpp_vk_lib gtest)
  add_test(${test_name} ${test_name})
endfunction()

file (GLOB test_files "test/*.cpp")
foreach (file ${test_files})
  get_filename_component(test_name ${file} NAME_WE)
  add_vk_test(${test_name} ${file})
endforeach()
