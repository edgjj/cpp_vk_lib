include(../cmake/initialize_submodule.cmake)

initialize_submodule(dependencies/simdjson)
initialize_submodule(dependencies/spdlog)
initialize_submodule(dependencies/googletest)
initialize_submodule(dependencies/curlpp)

add_subdirectory(simdjson EXCLUDE_FROM_ALL)
add_subdirectory(spdlog)
add_subdirectory(googletest)
add_subdirectory(curlpp)
