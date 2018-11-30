cmake_minimum_required(VERSION 3.12)
project(simple-ogl)


set(CMAKE_CXX_STANDARD 11)
include_directories(3rdpty)

add_subdirectory(graph)
add_subdirectory(resource)

add_executable(ogl main.cpp  Application.h TestTexture2DArray.h TestCEGUI.h)
target_link_libraries(ogl dl Xxf86vm glfw3 GLEW  GL  X11  pthread  Xrandr Xinerama Xcursor Xi CEGUIBase-0 CEGUIOpenGLRenderer-0 graph resource)