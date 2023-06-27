find_package(fmt REQUIRED)

add_library(hyperkdb_core src/hyperkb.cc)
target_include_directories(hyperkdb_core PUBLIC src ${fmt_INCLUDE_DIRS})

set_target_properties(hyperkdb_core PROPERTIES PUBLIC_HEADER "hyperkb.h")
install(TARGETS hyperkdb_core)

# add_subdirectory(test_package)