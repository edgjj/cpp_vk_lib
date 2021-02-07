
####### Expanded from @PACKAGE_INIT@ by configure_package_config_file() #######
####### Any changes to this file will be overwritten by the next CMake run ####
####### The input file was simdjson-config.cmake.in                            ########

get_filename_component(PACKAGE_PREFIX_DIR "${CMAKE_CURRENT_LIST_DIR}/../../../" ABSOLUTE)

####################################################################################

include(CMakeFindDependencyMacro)
if(ON)
    set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
    find_dependency(Threads)
endif()
# Import targets.
include("${CMAKE_CURRENT_LIST_DIR}/simdjson-targets.cmake")
