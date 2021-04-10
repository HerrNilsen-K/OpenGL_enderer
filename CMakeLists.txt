cmake_minimum_required(VERSION 3.16)
project(OpenGL_renderer)

set(CMAKE_CXX_STANDARD 20)

set(glew-cmake_BUID_STATIC ON)
set(glew-cmake_BUILD_SHARED OFF)

include_directories(third-party/glew/include)
include_directories(third-party/glm)
include_directories(third-party/stb)

add_library(${PROJECT_NAME} INTERFACE)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)


add_subdirectory(third-party/glew)
add_subdirectory(third-party/glfw)
add_subdirectory(third-party/glm)

target_link_libraries(${PROJECT_NAME} INTERFACE libglew_static)
target_link_libraries(${PROJECT_NAME} INTERFACE glfw)

find_package(OpenGL REQUIRED)

target_link_libraries(${PROJECT_NAME} INTERFACE OpenGL::GL)
