
# Set the minimum version of CMake that's required 
cmake_minimum_required(VERSION 3.12)

# Set the project name
project(HPS_SIMULATOR VERSION 0.1.0
                DESCRIPTION "The Heavy Photon Search simulation framework." 
                LANGUAGES CXX    
)

# Load additional macros used by this project. 
list(APPEND CMAKE_MODULE_PATH ${HPS_SIMULATOR_SOURCE_DIR}/cmake/)

# Load the BuildMacros module. If loaded correctly, the variable 
# 'build_macros_found' will be set to the path of the module.  Otherwise, it
# is set to NOTFOUND.
include(BuildMacros RESULT_VARIABLE build_macros_found)

# If an install location hasn't been set via CMAKE_INSTALL_PREFIX, set it to 
# a reasonable default ($PWD/install).  
if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/install CACHE PATH "" FORCE)
    message(STATUS "Install directory set to ${CMAKE_INSTALL_PREFIX}")
endif()

# Set the python installation path
set(PYTHON_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX}/python/HPS)
message(STATUS "Python install directory set to ${PYTHON_INSTALL_PREFIX}")

# Set the default release type to "Release". If a release type is specified 
# at the command line, it's respected.
set(default_build_type "Release")
if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
  set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE STRING "Choose the type of build." FORCE)
endif()

# Clear any variables cached during previous configuration cycles. 
clear_cache_variables()

# Start by building all of the classes needed for building the event bus and 
# ROOT dictionary. This is on by forcing the global "BUILD_EVENT_ONLY" option
# here.
set(BUILD_EVENT_ONLY ON CACHE BOOL "Build the SimCore library." FORCE)

add_subdirectory(SimCore ${CMAKE_BINARY_DIR}/SimCoreEvent)

# Once the event libraries have been built, turn off the global option. 
set(BUILD_EVENT_ONLY OFF CACHE BOOL "Build the SimCore library." FORCE)

# The framework has all the backend code needed to run all processors.
add_subdirectory(Framework)

add_subdirectory(DetDescr)

# SimCore allows the simulation to be run without biasing
add_subdirectory(SimCore)

# If enabled, build all test.  The test are assumed to reside inside of the
# directory "test" within each module.  The main
option(BUILD_TESTS "Build and link the run-test executable." OFF)
if(BUILD_TESTS)
    build_test()
endif()
