project(lazyfoo_sdl2 CXX)
cmake_minimum_required(VERSION 3.19)

set(CMAKE_CXX_FLAGS "-Wall")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(lazyfoo_sdl2
        src/main.cpp)

target_link_libraries(lazyfoo_sdl2 ${SDL2_LIBRARIES})