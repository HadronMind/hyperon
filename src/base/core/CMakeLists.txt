# source files
file(GLOB base_srcs CONFIGURE_DEPENDS "*.cpp" "*.cc")
add_library(hyperon_core_base STATIC ${base_srcs})
target_link_libraries(hyperon_core_base fmt::fmt)
