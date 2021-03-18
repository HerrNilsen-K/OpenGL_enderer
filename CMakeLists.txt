cmake_minimum_required(VERSION 3.17)
project(OpenGL_renderer)

set(CMAKE_CXX_STANDARD 20)

add_library(${PROJECT_NAME} src/GL/buffer.cpp src/GL/buffer.hpp src/GL/vertexArray.cpp src/GL/vertexArray.hpp src/GL/shader.cpp src/GL/shader.hpp src/GL/elementBuffer.cpp src/GL/elementBuffer.hpp src/GL/texture.cpp src/GL/texture.hpp src/GL/camera.cpp src/GL/camera.hpp src/mesh.cpp src/mesh.hpp src/window.cpp src/window.hpp)

add_executable(program main.cpp sprite.cpp sprite.hpp)

target_link_libraries(program ${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME} GLEW)
target_link_libraries(${PROJECT_NAME} OpenGL)
target_link_libraries(${PROJECT_NAME} glfw)
