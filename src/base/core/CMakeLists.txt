# source files
file(GLOB base_srcs CONFIGURE_DEPENDS "*.cpp" "*.cc")
add_library(hyperkb_core_base STATIC ${base_srcs})
target_link_libraries(hyperkb_core_base fmt::fmt)
