#include <SDL2/SDL.h>

class App
{
    public:
        App();
        ~App();
        void run();
        void update(double frame_rate);
        void draw();

    private:
        SDL_Window *main_window;
        SDL_Surface *main_surface;
        SDL_Event main_window_event;
};