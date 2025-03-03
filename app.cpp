#include <SDL2/SDL.h>
#include <iostream>

#include "app.hpp"

const int WINDOW_HEIGHT = 1280;
const int WINDOW_WIDTH = 720;
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

    main_surface = SDL_GetWindowSurface(main_window);
    if (!main_surface)
    {
        std::cout << "Failed to get window surface" << std::endl;
        std::cout << SDL_GetError() << std::endl;
        return;
    }
}

App::~App()
{
    SDL_FreeSurface(main_surface);
    SDL_DestroyWindow(main_window);
}

void App::run()
{
    while (true)
    {
        while (SDL_PollEvent(&main_window_event))
        {
            switch (main_window_event.type)
            {
            case SDL_QUIT:
                return;
            }
        }
        // update(FRAME_RATE);
        // draw();
    }
}

void App::update(double frame_rate)
{
}

void App::draw()
{
}