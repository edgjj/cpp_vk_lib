include(../cmake/initialize_submodule.cmake)

initialize_submodule(modules/simdjson)
initialize_submodule(modules/spdlog)
initialize_submodule(modules/googletest)
initialize_submodule(modules/curlpp)
initialize_submodule(modules/asio)

add_subdirectory(simdjson EXCLUDE_FROM_ALL)
add_subdirectory(spdlog)
add_subdirectory(googletest)
add_subdirectory(curlpp)
