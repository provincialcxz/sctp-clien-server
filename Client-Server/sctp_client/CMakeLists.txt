cmake_minimum_required(VERSION 3.5)

project(tcp_client LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(tcp_client main.cpp)
target_link_libraries(tcp_client pthread)
target_link_libraries(tcp_client /usr/lib/x86_64-linux-gnu/libsctp.a)

install(TARGETS tcp_client
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
