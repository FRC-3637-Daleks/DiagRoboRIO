cmake_minimum_required (VERSION 2.6)

project (DiagRoboRIO)

include_directories (src/)
include_directories (src/mosquitto/)

file (GLOB SOURCES src/*.cpp)
file (GLOB INCLUDES src/*.h)
file (GLOB MOSQUITTO_INCLUDE src/mosquitto/*.h)

set (CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} --std=c++11)

add_library (${PROJECT_NAME} SHARED ${SOURCES})

install (TARGETS ${PROJECT_NAME}  DESTINATION /usr/local/lib)
install (DIRECTORY DESTINATION /usr/local/include/${PROJECT_NAME})
install (DIRECTORY DESTINATION /usr/local/include/${PROJECT_NAME}/mosquitto)
install (FILES ${INCLUDES} DESTINATION /usr/local/include/${PROJECT_NAME})
install (FILES ${MOSQUITTO_INCLUDE} DESTINATION /usr/local/include/${PROJECT_NAME}/mosquitto)


add_custom_target (doc
	doxygen Doxyfile
        COMMENT "Generating API documentation with Doxygen" VERBATIM
)

