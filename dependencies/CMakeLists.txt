include(../cmake/initialize_submodule.cmake)

initialize_submodule(dependencies/simdjson)
initialize_submodule(dependencies/spdlog)

add_subdirectory(simdjson EXCLUDE_FROM_ALL)
add_subdirectory(spdlog)
