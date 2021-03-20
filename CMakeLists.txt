cmake_minimum_required(VERSION 3.17)
project(OpenGL_renderer)

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME} main.cpp src/models/sprite.hpp src/GL/vertexArray.hpp src/GL/shader.hpp src/GL/elementBuffer.hpp src/GL/texture.hpp src/GL/camera.hpp src/models/mesh.hpp src/window.hpp src/util.hpp)

#add_executable(program main.cpp )

#target_link_libraries(program ${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME} GLEW)
target_link_libraries(${PROJECT_NAME} OpenGL)
target_link_libraries(${PROJECT_NAME} glfw)
