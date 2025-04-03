#pragma once
#include <SDL2/SDL.h>
#include <memory>
#include <vector>
#include "Object.cpp"
#include "Animation.h"

// Forward declare Animation class
class Animation;

class Sprite : public Object
{
public:
    Sprite(std::shared_ptr<SDL_Texture> texture, SDL_Renderer *renderer);
    virtual void update(const int delta) override;

private:
    std::vector<std::shared_ptr<Animation>> animations;
    std::shared_ptr<SDL_Texture> texture;
    SDL_Rect clip;
    SDL_Rect rect;
};