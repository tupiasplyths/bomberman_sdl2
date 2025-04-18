#include <SDL2/SDL.h>
#include <iostream>

#include "app.hpp"
#include "scenes/Scene.h"
#include "scenes/MenuScene.cpp"


const int WINDOW_HEIGHT = 720;
const int WINDOW_WIDTH = 1280;
const double FRAME_RATE = 1.0 / 60.0;

App::App()
{
    main_window = SDL_CreateWindow("App", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 1);
    if (!main_window)
    {
        std::cout << "Failed to create window" << std::endl;
        std::cout << SDL_GetError() << std::endl;
        return;
    }

    renderer = SDL_CreateRenderer(main_window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) 
    {
        std::cout << "Failed to create renderer" << std::endl;
        std::cout << SDL_GetError() << std::endl;
        return;
    }

//     main_surface = SDL_GetWindowSurface(main_window);
//     if (!main_surface)
//     {
//         std::cout << "Failed to get window surface" << std::endl;
//         std::cout << SDL_GetError() << std::endl;
//         return;
//     }
}

App::~App()
{
    // SDL_FreeSurface(main_surface);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(main_window);
    SDL_Quit();
}

void App::addScene(std::string name, std::shared_ptr<Scene> scene)
{
    const auto find_scene = scenes_list.find(name);
    if (find_scene != scenes_list.end() && find_scene->second) 
    {
        std::cout << "Scene already exists" << std::endl;
        return;
    }
    scenes_list[name] = scene;
}

void App::activateScene(const std::string name)
{
    const auto find_scene = scenes_list.find(name);
    if (find_scene == scenes_list.end() || !find_scene->second)
    {
        std::cout << "Scene not found" << std::endl;
        return;
    }
    current_scene = find_scene->second;
    current_scene->onActivate();
}

void App::run()
{
    if (running) 
    {
        return;
    }
    running = true;

    addScene("menu", std::make_shared<MenuScene>(this));
    activateScene("menu");
    SDL_Event event;
    while (running)
    {
        while (SDL_PollEvent(&event))
        {

            switch (event.type)
            {
            case SDL_QUIT:
                stop();
                break;
            }
        }
        // update(FRAME_RATE);
        // draw();
    }
}

void App::stop()
{
    running = false;
}

