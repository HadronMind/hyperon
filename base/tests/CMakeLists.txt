find_package(hyperkdb_core CONFIG REQUIRED)

add_executable(example src/example.cpp)
target_link_libraries(example hyperkdb_core::hyperkdb_core)
