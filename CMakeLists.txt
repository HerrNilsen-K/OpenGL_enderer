cmake_minimum_required(VERSION 3.17)
project(3cardRenderer)

set(CMAKE_CXX_STANDARD 20)

add_library(${PROJECT_NAME} src/buffer.cpp src/buffer.hpp src/vertexArray.cpp src/vertexArray.hpp src/shader.cpp src/shader.hpp src/elementBuffer.cpp src/elementBuffer.hpp)

add_executable(program main.cpp)

target_link_libraries(program ${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME} GLEW)
target_link_libraries(${PROJECT_NAME} OpenGL)
target_link_libraries(${PROJECT_NAME} glfw)
