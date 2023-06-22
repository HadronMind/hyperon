cmake_minimum_required(VERSION 3.15)
project(TestBed CXX)

list (APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

find_package(Guile REQUIRED)

add_executable(guile_c src/guile_c.cc)
target_include_directories(guile_c PRIVATE ${GUILE_INCLUDE_DIRS})
target_link_libraries(guile_c PRIVATE ${GUILE_LIBRARIES})