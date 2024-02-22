cmake_minimum_required(VERSION 3.15)
project(Hyperon CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(TEST_ON OFF)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

find_package(fmt REQUIRED)
find_package(nlohmann_json REQUIRED)
include_directories(${fmt_INCLUDE_DIRS} ${nlohmann_json_INCLUDE_DIRS})

add_subdirectory(src)
if(TEST_ON)
  add_subdirectory(tests)
endif()
