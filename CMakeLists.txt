cmake_minimum_required(VERSION 3.15)
project(HyperKB CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

list (APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

add_subdirectory(core)
add_subdirectory(server)