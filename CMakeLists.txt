cmake_minimum_required(VERSION 3.12)
project(simple-ogl)


set(CMAKE_CXX_STANDARD 11)
include_directories(3rdpty)
add_subdirectory(graph)
add_subdirectory(resource)
add_subdirectory(scene)
add_subdirectory(3rdpty/imgui)

add_executable(ogl main.cpp)
target_link_libraries(ogl dl Xxf86vm glfw3 GLEW  GL  X11  pthread  Xrandr Xinerama Xcursor Xi graph resource scene imgui)

