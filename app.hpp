#include <SDL2/SDL.h>

class App
{
    public:
        App();
        ~App();
        void run();
        void update(double frame_rate);
        void draw();
        void stop();

    private:
        SDL_Window *main_window;
        // SDL_Surface *main_surface;
        SDL_Renderer *renderer;
        SDL_Event main_window_event;
        bool running = false;
        int window_width = 1280;
        int window_height = 720;
};