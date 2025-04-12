// #include <SDL2/SDL.h>
// #include <memory>

#include "entities/Object.h"

/// @brief create new object
Object::Object(SDL_Renderer *_renderer)
{
    renderer = _renderer;
};

Object::~Object() {};

void Object::setSize(const int width, const int height)
{
    rect.w = width;
    rect.h = height;
}

/// @brief Clip the spritesheet to a specific region
void Object::setClip(int width, int height, int x, int y)
{
    clip.w = width;
    clip.h = height;
    clip.x = x;
    clip.y = y;
}

void Object::setPosition(const int x, const int y)
{
    rect.x = x;
    rect.y = y;
}

int Object::getWidth()
{
    return rect.w;
}

int Object::getHeight()
{
    return rect.h;
}

int Object::getX()
{
    return rect.x;
}

int Object::getY()
{
    return rect.y;
}

bool Object::isDestroyed()
{
    return destroyed;
}

const SDL_Rect &Object::getRect()
{
    return rect;
}

void Object::setFlip(SDL_RendererFlip _flip)
{
    this->flip = _flip;
}

void Object::update(const int delta)
{
}

// void draw(const SDL_Rect &camera)
// {
//     if (renderer != nullptr && texture != nullptr)
//     {
//         SDL_Rect renderQuad = {rect.x - camera.x, rect.y - camera.y, rect.w, rect.h};
//         SDL_RenderCopyEx(renderer, texture.get(), &clip, &renderQuad, 0, nullptr, flip);
//     }
// }
void Object::draw()
{
    if (renderer != nullptr && texture != nullptr)
    {
        SDL_RenderCopyEx(renderer, texture.get(), &clip, &rect, 0, nullptr, flip);
    }
}