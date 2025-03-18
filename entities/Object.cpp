#include <SDL2/SDL.h>
#include <memory>

class Object
{
    protected:
        SDL_Renderer *renderer = nullptr;
        std::shared_ptr<SDL_Texture> texture = nullptr;
        SDL_Rect rect;
        SDL_Rect clip;
        SDL_RendererFlip flip  = SDL_FLIP_NONE;
        bool destroyed = false;
    public:
        /// @brief create new object
        Object(SDL_Renderer *renderer)
        {
            this->renderer = renderer;
        };
        ~Object(){};

        void setSize(const int width, const int height)
        {
            this->rect.w = width;
            this->rect.h = height;
        }

        void setClip(int width, int height, int x, int y) {
            this->clip.w = width;
            this->clip.h = height;
            this->clip.x = x;
            this->clip.y = y;
        }

        int getWidth() {
            return rect.w;
        }

        int getHeight() {
            return rect.h;
        }

        int getX() {
            return rect.x;
        }

        int getY() {
            return rect.y;
        }

        bool isDestroyed() {
            return this->destroyed;
        }

        const SDL_Rect& getRect() {
            return rect;
        }

        void setFlip(SDL_RendererFlip flip) {
            this->flip = flip;
        }

        void update(const unsigned int frame_rate){
            // 
        };

        void update(double frame_rate) {
            // 
        }
        void draw(const SDL_Rect& camera) {
            if (renderer != nullptr && texture != nullptr) {
                SDL_Rect renderQuad = {rect.x - camera.x, rect.y - camera.y, rect.w, rect.h};
                SDL_RenderCopyEx(renderer, texture.get(), &clip, &renderQuad, 0, nullptr, flip);
            }
        }

};