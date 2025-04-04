#include <SDL2/SDL.h>
#include <memory>

class Object
{
protected:
    SDL_Renderer* renderer = nullptr;
    std::shared_ptr<SDL_Texture> texture = nullptr;
    SDL_Rect rect;
    SDL_Rect clip;
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    bool destroyed = false;

public:
    Object(SDL_Renderer * renderer);
    virtual ~Object();
    void setSize(const int width, const int height);
    void setClip(int width, int height, int x, int y);
    int getWidth();
    int getHeight();
    int getX();
    int getY();
    bool isDestroyed();
    void setFlip(SDL_RendererFlip flip);
    virtual void update(const int delta) = 0;
    const SDL_Rect& getRect();
    void draw();
};