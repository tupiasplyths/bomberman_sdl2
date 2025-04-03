#include <SDL2/SDL.h>
#include <memory>
#include <vector>
// #include "Object.cpp"
// #include "Animation.h"
#include "entities/Sprite.h"

Sprite::Sprite(std::shared_ptr<SDL_Texture> texture, SDL_Renderer *renderer) : Object(renderer)
    {
        this->texture = texture;
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
        for (auto &animation : animations)
        {
            animation->update(delta);
        }
    }
