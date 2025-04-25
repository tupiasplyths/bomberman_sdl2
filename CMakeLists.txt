cmake_minimum_required(VERSION 3.12)

project (bomberman_sdl2)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

find_package(SDL2_TTF REQUIRED)
include_directories(${SDL2_TTF_INCLUDE_DIR})

find_package(SDL2_IMAGE REQUIRED)
include_directories(${SDL2_IMAGE_INCLUDE_DIR})

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
# target_include_directories(bomberman PRIVATE E:/msys2/mingw64/include)
# include_directories(${CMAKE_SOURCE_DIR})
# include_directories(${CMAKE_SOURCE_DIR}/scenes)
# include_directories(${CMAKE_SOURCE_DIR}/entities)

set(CMAKE_CXX_STANDARD 17)

# find_file(SDL2_INCLUDE_DIR NAME SDL.h HINTS SDL2)
# find_library(SDL2_LIBRARY NAME SDL2)
# find_file(SDL2_TTF_INCLUDE_DIR NAME SDL_ttf.h HINTS SDL2_ttf)
# find_file(SDL2_IMAGE_INCLUDE_DIR NAME SDL_image.h HINTS SDL2_image)

# find_library(SDL2_TTF_LIBRARY NAME SDL2_ttf)
# find_library(SDL2_IMAGE_LIBRARY NAME SDL2_image)

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
    ${CMAKE_CURRENT_SOURCE_DIR}/entities/MovingEntities.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/entities/Enemy.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/entities/Object.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/entities/Text.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/entities/Sprite.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/entities/Player.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/scenes/textures.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/scenes/Scene.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/scenes/MenuScene.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/scenes/GameScene.cpp
)

add_executable(bomberman ${SOURCES})

# target_link_libraries(
#     bomberman
#     ${SDL2_LIBRARIES}
#     ${SDL2_TTF_LIBRARIES}
#     ${SDL2_IMAGE_LIBRARY}
# )

target_link_libraries(
    bomberman 
    SDL2::SDL2main 
    SDL2::SDL2
    SDL2_ttf::SDL2_ttf
    SDL2_image::SDL2_image
    -static
)

# target_link_libraries(bomberman ${SDL2_LIBRARIES} -lSDL2_ttf -lSDL2_image)

install(TARGETS bomberman
    RUNTIME DESTINATION .
    BUNDLE DESTINATION .
)