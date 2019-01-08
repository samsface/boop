cmake_minimum_required(VERSION 3.10)
project(boop_test)

include_directories("libs")
include_directories("libs/arduino")
include_directories("main")

file(GLOB_RECURSE sources main/*.hpp)
file(GLOB_RECURSE test_sources test/*.cpp)

###############################################################################

add_executable(boop-test ${sources} ${test_sources})

set_target_properties(
  boop-test
  PROPERTIES
  CXX_STANDARD 17
  CXX_EXTENSIONS OFF
)
