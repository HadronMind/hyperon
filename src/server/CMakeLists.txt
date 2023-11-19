add_executable(hyperkbd hyperkb_server.cpp)

install(
  TARGETS hyperkbd
  DESTINATION "."
  RUNTIME DESTINATION bin
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib)
