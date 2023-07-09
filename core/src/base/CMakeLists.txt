# source files
file(GLOB base_srcs CONFIGURE_DEPENDS "*.h" "*.cc")
list(FILTER base_srcs EXCLUDE REGEX ".*_[unittest|ut].cc$")

# Ut files
file(GLOB base_ut_srcs CONFIGURE_DEPENDS "*_unittest.cc" "*_ut.cc")

add_library(hyperkb_core_base STATIC ${base_srcs})
target_link_libraries(hyperkb_core_base fmt::fmt)
