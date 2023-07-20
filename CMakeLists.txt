cmake_minimum_required(VERSION 3.15)
project(HyperKB CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(TEST_ON OFF)

list (APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

find_package(fmt REQUIRED)
include_directories(${fmt_INCLUDE_DIRS})

add_subdirectory(core)
add_subdirectory(server)
if(TEST_ON)
add_subdirectory(tests)
endif()