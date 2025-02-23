cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 23)
project("Julia Sets")

find_package(glfw)
find_package(OpenGL REQUIRED)
find_package(imgui REQUIRED)

# EXECUTABLE
add_executable(application src/main.cpp)

# LIBRARY
target_link_libraries(application glfw)
target_link_libraries(application OpenGL)
target_link_libraries(application imgui)

