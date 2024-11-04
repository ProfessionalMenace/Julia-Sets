cmake_minimum_required(VERSION 3.10)
set (CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-g -Wall -WExtra -WPedantic")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-O3")

project(Julia-Sets VERSION 1.0)

# HEADERS AND SOURCES
add_library(${PROJECT_NAME} STATIC 
    src/application.cpp
    src/display.cpp
    src/window.cpp 
)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)

# SDL2 LIBRARY
find_package(SDL2 REQUIRED)
target_link_libraries(${PROJECT_NAME} SDL2)

# EXECUTABLE
add_executable(executable src/main.cpp)
target_link_libraries(executable PRIVATE ${PROJECT_NAME})

