include_directories(../../lib/include)
include_directories(../../lib/include/cpp_vk_lib)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ../../build)
set(EXECUTABLE_OUTPUT_PATH ../../build)

file(GLOB_RECURSE SRC "*.hpp" "*.cpp")
add_executable(test_exception ${SRC})
find_library(cpp_vk_lib HINTS "../../lib")

target_link_libraries(test_exception cpp_vk_lib curl curlpp pthread gtest)
