find_library(cpp_vk_lib PATHS "../cpp_vk_lib")

include_directories(../cpp_vk_lib/include)
include_directories(../modules/spdlog/include)
include_directories(../modules/asio/asio/include)

set(EXECUTABLE_OUTPUT_PATH ..)

if (CMAKE_SYSTEM_NAME STREQUAL "FreeBSD")
    add_compile_options(-Wno-deprecated -Wno-deprecated-declarations)
endif()

add_executable(sender sender.cpp)
target_link_libraries(sender cpp_vk_lib)

add_executable(receiver receiver.cpp)
target_link_libraries(receiver cpp_vk_lib)

add_executable(curl curl.cpp)
target_link_libraries(curl cpp_vk_lib pthread)
