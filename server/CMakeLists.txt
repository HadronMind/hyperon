cmake_minimum_required(VERSION 3.15)
project(hyperkdb-server CXX)



add_executable(hyperkdb-server src/hyperkdb-server.cpp src/main.cpp)



install(TARGETS hyperkdb-server DESTINATION "."
        RUNTIME DESTINATION bin
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        )
