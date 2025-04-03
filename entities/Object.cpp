#include <SDL2/SDL.h>
#include <memory>

class Object
{
protected:
    SDL_Renderer *renderer = nullptr;
    std::shared_ptr<SDL_Texture> texture = nullptr;
    SDL_Rect rect;
    SDL_Rect clip;
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    bool destroyed = false;

public:
    /// @brief create new object
    Object(SDL_Renderer *renderer)
    {
        renderer = renderer;
    };

    ~Object() {};

    void setSize(const int width, const int height)
    {
        rect.w = width;
        rect.h = height;
    }

    /// @brief Clip the spritesheet to a specific region
    void setClip(int width, int height, int x, int y)
    {
        clip.w = width;
        clip.h = height;
        clip.x = x;
        clip.y = y;
    }

    int getWidth()
    {
        return rect.w;
    }

    int getHeight()
    {
        return rect.h;
    }

    int getX()
    {
        return rect.x;
    }

    int getY()
    {
        return rect.y;
    }

    bool isDestroyed()
    {
        return destroyed;
    }

    const SDL_Rect &getRect()
    {
        return rect;
    }

    void setFlip(SDL_RendererFlip flip)
    {
        this->flip = flip;
    }

    virtual void update(const int delta) {
        //
    };

    // void update(double frame_rate)
    // {
    //     //
    // }

    // void draw(const SDL_Rect &camera)
    // {
    //     if (renderer != nullptr && texture != nullptr)
    //     {
    //         SDL_Rect renderQuad = {rect.x - camera.x, rect.y - camera.y, rect.w, rect.h};
    //         SDL_RenderCopyEx(renderer, texture.get(), &clip, &renderQuad, 0, nullptr, flip);
    //     }
    // }
    void draw()
    {
        if (renderer != nullptr && texture != nullptr)
        {
            SDL_RenderCopyEx(renderer, texture.get(), &clip, &rect, 0, nullptr, flip);
        }
    }
};