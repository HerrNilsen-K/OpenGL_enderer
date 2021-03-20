cmake_minimum_required(VERSION 3.17)
project(OpenGL_renderer)

set(CMAKE_CXX_STANDARD 20)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(third-party/glfw)

add_executable(${PROJECT_NAME} main.cpp src/models/sprite.hpp src/GL/vertexArray.hpp src/GL/shader.hpp src/GL/elementBuffer.hpp src/GL/texture.hpp src/GL/camera.hpp src/models/mesh.hpp src/window.hpp src/util.hpp)


target_link_libraries(${PROJECT_NAME} GLEW)
target_link_libraries(${PROJECT_NAME} OpenGL)
target_link_libraries(${PROJECT_NAME} glfw)

find_package(OpenGL REQUIRED)
target_link_libraries(${PROJECT_NAME} OpenGL::GL)
