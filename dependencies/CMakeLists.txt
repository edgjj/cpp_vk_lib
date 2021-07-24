include(../cmake/initialize_submodule.cmake)

initialize_submodule(dependencies/simdjson)
initialize_submodule(dependencies/spdlog)
initialize_submodule(dependencies/googletest)

add_subdirectory(simdjson EXCLUDE_FROM_ALL)
add_subdirectory(spdlog)
add_subdirectory(googletest)
