cmake_minimum_required(VERSION 3.17)
project(OpenGL_renderer)

set(CMAKE_CXX_STANDARD 20)

set(glew-cmake_BUID_STATIC ON)
set(glew-cmake_BUILD_SHARED OFF)

include_directories(third-party/glew/include)
include_directories(third-party/glm)

add_executable(${PROJECT_NAME} main.cpp src/models/sprite.hpp src/GL/vertexArray.hpp src/GL/shader.hpp src/GL/elementBuffer.hpp src/GL/texture.hpp src/GL/camera.hpp src/models/mesh.hpp src/window.hpp src/util.hpp)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)


add_subdirectory(third-party/glew)
add_subdirectory(third-party/glfw)
add_subdirectory(third-party/glm)

find_package(GLEW)

target_link_libraries(${PROJECT_NAME} libglew_static)
#target_link_libraries(${PROJECT_NAME} OpenGL)
target_link_libraries(${PROJECT_NAME} glfw)

find_package(OpenGL REQUIRED)

target_link_libraries(${PROJECT_NAME} OpenGL::GL)
