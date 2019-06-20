cmake_minimum_required(VERSION 3.14)
project(Dynamixel_1_0_protocol)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES main.cpp
        dynamixel_protocol_1.cpp
        serial_linux.cpp)

add_executable(Dynamixel_1_0_protocol ${SOURCES})
