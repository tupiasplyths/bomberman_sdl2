#include <SDL2/SDL.h>
#include <unordered_map>
#include "scenes/Scene.h"

class App
{
public:
    App();
    ~App();
    void run();
    void stop();
    void addScene(std::string name, std::shared_ptr<Scene> scene);
    void activateScene(const std::string name);

private:
    SDL_Window *main_window;
    // SDL_Surface *main_surface;
    SDL_Renderer *renderer;
    SDL_Event main_window_event;
    bool running = false;
    int window_width = 1280;
    int window_height = 720;
    std::unordered_map<std::string, std::shared_ptr<Scene>> scenes_list;
    std::shared_ptr<Scene> current_scene = nullptr;
};