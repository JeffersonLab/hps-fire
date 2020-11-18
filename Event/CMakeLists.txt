# Set the minimum version of CMake that's required
cmake_minimum_required(VERSION 3.12)

# Set the project name
project(
  Event
  VERSION 2.3.0
  DESCRIPTION "Event"
  LANGUAGES CXX)

# Setup the library
setup_library(name Event
              register_target)

