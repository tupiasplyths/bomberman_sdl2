#include <SDL2/SDL.h>
#include <memory>

class Object
{
    private:
        SDL_Renderer *renderer = nullptr;
        std::shared_ptr<SDL_Texture> texture = nullptr;
        SDL_Rect rect;
        SDL_Rect clip;
        SDL_RendererFlip flip  = SDL_FLIP_NONE;
    public:
        /// @brief create new object
        Object(SDL_Renderer *renderer)
        {
            this->renderer = renderer;
        };
        ~Object(){};

        void setSize(const int width, const int height)
        {
            rect->width = width;
            rect->height = height;
        }

        void update(double frame_rate);
        void draw();

};