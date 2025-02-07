find_library(cpp_vk_lib PATHS "../cpp_vk_lib")
include_directories(../cpp_vk_lib/include)
include_directories(../modules/spdlog/include)
include_directories(../modules/asio/asio/include)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ../)
set(EXECUTABLE_OUTPUT_PATH ../)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../)

function (add_vk_example bin_name path)
    if (CMAKE_SYSTEM_NAME STREQUAL "FreeBSD")
        add_compile_options(-Wno-deprecated -Wno-deprecated-declarations)
    endif()
    add_executable(${bin_name} ${path})
    target_link_libraries(${bin_name} PRIVATE simdjson)
    target_link_libraries(${bin_name} PUBLIC cpp_vk_lib)
endfunction()

file (GLOB examples LIST_DIRECTORIES FALSE "*.cpp")
foreach (file ${examples})
    get_filename_component(name ${file} NAME_WE)
    add_vk_example(${name} ${file})
endforeach()
