cmake_minimum_required(VERSION 3.12)

project (bomberman_sdl2)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_CXX_STANDARD 17)

find_file(SDL2_INCLUDE_DIR NAME SDL.h HINTS SDL2)
find_library(SDL2_LIBRARY NAME SDL2)

if(MSVC)
    add_compile_options(/std:c++17 /W4 /MT )
else()
    add_compile_options(-std=c++17 -Wall -Wextra -Wshadow -Wnon-virtual-dtor -Wunused -Wpedantic -pedantic-errors -Wconversion)
endif()

set (
    SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/game.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/app.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Animation.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/entities/Creature.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/entities/Enemy.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/entities/Object.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/entities/Sprite.cpp
)

add_executable(bomberman ${SOURCES})

target_link_libraries(bomberman ${SDL2_LIBRARIES})