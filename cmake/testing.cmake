find_library(cpp_vk_lib HINTS "${CMAKE_CURRENT_SOURCE_DIR}/lib")
include_directories(cpp_vk_lib)
include_directories(dependencies/spdlog/include)

enable_testing()

function (add_vk_test test_name test_path)
  add_executable(${test_name} ${test_path})
  target_link_libraries(${test_name} cpp_vk_lib gtest)
  add_test(${test_name} ${test_name})
endfunction()

file (GLOB test_files "${CMAKE_CURRENT_SOURCE_DIR}/test/*.cpp")
foreach (file ${test_files})
  get_filename_component(test_name ${file} NAME_WE)
  add_vk_test(${test_name} ${file})
endforeach()
