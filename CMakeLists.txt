cmake_minimum_required(VERSION 3.12)
project(TinyEngine)

include_directories(3rdpty)
set(CMAKE_CXX_STANDARD 11)

add_subdirectory(graph)
add_subdirectory(resource)

add_executable(TinyEngine main.cpp 3rdpty/glad/glad.c)
target_link_libraries(TinyEngine dl   glfw3  GL  X11  pthread  Xrandr  Xi graph resource)