cmake_minimum_required(VERSION 3.2)
project(OS_HW9)

set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -std=c99")

set(CLIENT_SOURCE_FILES main.c)
set(SERVER_SOURCE_FILES server.c)
add_executable(client ${CLIENT_SOURCE_FILES})
add_executable(server ${SERVER_SOURCE_FILES})