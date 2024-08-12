#mkdir build
#cd build 
#cmake ..
#make

cmake_minimum_required(VERSION 3.10)

project(MyProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${CMAKE_SOURCE_DIR}/src/include)

set(CLIENT_SOURCES
    src/client/client.cpp
    src/Conn.cpp
    src/msg.cpp
    src/read_full.cpp
    src/write_all.cpp
)

set(SERVER_SOURCES
    src/server/server.cpp
    src/Conn.cpp
    src/msg.cpp
    src/read_full.cpp
    src/write_all.cpp
)

add_executable(client.out ${CLIENT_SOURCES})
add_executable(server.out ${SERVER_SOURCES})

set_target_properties(client.out PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
set_target_properties(server.out PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})