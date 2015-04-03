cmake_minimum_required (VERSION 2.6)

project (DiagRoboRIO)

include_directories (src/)
include_directories (src/mosquitto/)

file (GLOB SOURCES src/*.cpp)

set (CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} --std=c++11)

add_library (${PROJECT_NAME} STATIC ${SOURCES})

