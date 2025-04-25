#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>
#include <memory>
#include <vector>
#include "Object.h"
#include "Animation.h"


class Sprite : public Object
{
public:
    Sprite(std::shared_ptr<SDL_Texture> texture, SDL_Renderer *renderer);
    virtual void update(const int delta) override;
    void addAnimation(std::shared_ptr<Animation> animation);
    bool hasTexture();
private:
    std::vector<std::shared_ptr<Animation>> animations;
    // std::shared_ptr<SDL_Texture> texture;
    SDL_Rect clip;
    SDL_Rect rect;
};

#endif // SPRITE_H