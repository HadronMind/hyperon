add_executable(hyperond hyperon_server.cpp)

install(
  TARGETS hyperond
  DESTINATION "."
  RUNTIME DESTINATION bin
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib)
