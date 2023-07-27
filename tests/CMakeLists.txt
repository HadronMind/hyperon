find_package(Guile REQUIRED)

add_executable(guile_unittest guile_c.cc)
target_include_directories(guile_unittest PRIVATE ${GUILE_INCLUDE_DIRS})
target_link_libraries(guile_unittest PRIVATE ${GUILE_LIBRARIES})