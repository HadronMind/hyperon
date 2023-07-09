find_package(fmt REQUIRED)
include_directories(${fmt_INCLUDE_DIRS})

add_subdirectory(base)
add_subdirectory(link)

add_library(hyperkdb_core SHARED hyperkb.cc)
# target_include_directories(hyperkdb_core PUBLIC ${fmt_INCLUDE_DIRS})
target_link_libraries(hyperkdb_core hyperkb_core_base)
set_target_properties(hyperkdb_core PROPERTIES PUBLIC_HEADER "hyperkb.h")