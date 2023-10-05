cmake_minimum_required(VERSION 3.5)

project(tcp_server LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(tcp_server main.cpp)
target_link_libraries(tcp_server pthread)
target_link_libraries(tcp_server /usr/lib/x86_64-linux-gnu/libsctp.a)

install(TARGETS tcp_server
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
