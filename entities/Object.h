#ifndef OBJECT_H
#define OBJECT_H

#include <SDL2/SDL.h>
#include <memory>

class Object
{
protected:
    SDL_Renderer *renderer = nullptr; // renderer using
    std::shared_ptr<SDL_Texture> texture = nullptr; // object's texture
    SDL_Rect rect;                         // for object position and size
    SDL_Rect clip;                         // for texture clipping
    SDL_RendererFlip flip = SDL_FLIP_NONE; // for texture flipping
    bool destroyed = false;

public:
    Object(SDL_Renderer *renderer);
    virtual ~Object();
    void setSize(const int width, const int height);
    void setClip(int width, int height, int x, int y);
    void setPosition(const int x, const int y);
    int getWidth();
    int getHeight();
    int getX();
    int getY();
    bool isDestroyed();
    void setFlip(SDL_RendererFlip flip);
    virtual void update(const int delta);
    const SDL_Rect &getRect();
    void draw();
};

#endif // OBJECT_H