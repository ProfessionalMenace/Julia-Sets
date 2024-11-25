cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-g -Wall -WExtra -WPedantic")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-O3")

project(Julia-Sets VERSION 1.0)

# EXECUTABLE
add_executable(application src/main.cpp)

# SDL2 LIBRARY
find_package(SDL2 REQUIRED)
target_link_libraries(application SDL2)

