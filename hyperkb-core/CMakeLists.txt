cmake_minimum_required(VERSION 3.15)
project(hyperkdb-core CXX)




add_library(hyperkdb-core src/hyperkdb-core.cpp)
target_include_directories(hyperkdb-core PUBLIC include)



set_target_properties(hyperkdb-core PROPERTIES PUBLIC_HEADER "include/hyperkdb-core.h")
install(TARGETS hyperkdb-core)
