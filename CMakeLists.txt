cmake_minimum_required(VERSION 3.12)
project(simple-ogl)

include_directories(3rdpty)
set(CMAKE_CXX_STANDARD 11)

add_subdirectory(graph)
add_subdirectory(resource)

add_executable(ogl main.cpp 3rdpty/glad/glad.c)
target_link_libraries(ogl dl Xxf86vm glfw3  GL  X11  pthread  Xrandr Xinerama Xcursor Xi graph resource)