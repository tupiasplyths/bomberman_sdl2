#include <SDL2/SDL.h>
#include <memory>
#include <vector>
// #include "Object.cpp"
// #include "Animation.h"
#include "entities/Sprite.h"

Sprite::Sprite(std::shared_ptr<SDL_Texture> _texture, SDL_Renderer *_renderer) : Object(_renderer)
{
    this->texture = _texture;
    int width, height;
    SDL_QueryTexture(this->texture.get(), NULL, NULL, &width, &height);
    clip.x = 0;
    clip.y = 0;
    clip.h = height;
    clip.w = width;
    rect.x = 0;
    rect.y = 0;
    rect.w = width;
    rect.h = height;
}
void Sprite::update(const int delta)
{
    // printf("Sprite update\n");
    for (auto &animation : animations)
    {
        animation->update(delta);
    }
}

void Sprite::addAnimation(std::shared_ptr<Animation> animation)
{
    animations.push_back(animation);
}