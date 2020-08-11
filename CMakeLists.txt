
# Set the minimum version of CMake that's required 
cmake_minimum_required(VERSION 3.12)

# Set the project name
project(HPS_SIMULATOR VERSION 0.1.0
                DESCRIPTION "The Heavy Photon Search simulation framework." 
                LANGUAGES CXX    
)

# If an install location hasn't been set via CMAKE_INSTALL_PREFIX, set it to 
# a reasonable default ($PWD/install).  
if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/install CACHE PATH "" FORCE)
    message(STATUS "Install directory set to ${CMAKE_INSTALL_PREFIX}")
endif()

# Load additional macro commands 
list(APPEND CMAKE_MODULE_PATH ${HPS_SIMULATOR_SOURCE_DIR}/cmake/)
message(STATUS ${CMAKE_MODULE_PATH})

# Load the BuildMacros module. If loaded correctly, the variable 
# 'build_macros_found' will be set to the path of the module.  Otherwise, it
# is set to NOTFOUND.
include(BuildMacros RESULT_VARIABLE build_macros_found)

# Set the default release type to "Release". If a release type is specified 
# at the command line, it's respected.
set(default_build_type "Release")
if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
  set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE STRING "Choose the type of build." FORCE)
endif()

add_subdirectory(Event)
add_subdirectory(Framework)

# If enabled, build all test.  The test are assumed to reside inside of the
# directory "test" within each module.  The main
option(BUILD_TESTS "Build and link the run-test executable." OFF)
if(BUILD_TESTS)
    build_test()
endif()

# install python init file for top-level LDMX module
file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/python/__init__.py 
    "\"\"\"Python package to configure ldmx-sw\"\"\"")
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/python/__init__.py DESTINATION lib/python/HPS)
