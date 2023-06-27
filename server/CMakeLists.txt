
add_executable(hyperkdb-server src/hyperkdb-server.cpp src/main.cpp)

install(TARGETS hyperkdb-server DESTINATION "."
        RUNTIME DESTINATION bin
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        )
