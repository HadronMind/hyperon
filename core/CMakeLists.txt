cmake_minimum_required(VERSION 3.15)
project(hyperkdb_core CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(hyperkdb_core src/hyperkdb.cpp)
target_include_directories(hyperkdb_core PUBLIC include)

set_target_properties(hyperkdb_core PROPERTIES PUBLIC_HEADER "include/hyperkb/core/hyperkdb.h")
install(TARGETS hyperkdb_core)
