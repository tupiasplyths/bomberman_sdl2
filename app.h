#ifndef APP_H
#define APP_H

#include <SDL2/SDL.h>
#include <unordered_map>
#include "scenes/Scene.h"
#include "scenes/textures.h"

class App
{
public:
    App();
    ~App();
    void run();
    void stop();
    void addScene(std::string name, std::shared_ptr<Scene> scene);
    void activateScene(const std::string name);
    SDL_Renderer *getRenderer() const;
    int getWindowWidth();
    int getWindowHeight();
    Texture *getTextures() const;
    void update(const int delta);
    void draw();
    
private:
    SDL_Window *main_window;
    // SDL_Surface *main_surface;
    SDL_Renderer *renderer;
    SDL_Event main_window_event;
    bool running = false;
    int window_width = 1280;
    int window_height = 720;
    Texture *texture;
    std::unordered_map<std::string, std::shared_ptr<Scene>> scenes_list;
    std::shared_ptr<Scene> current_scene = nullptr;
    int last_tick = 0;
};

#endif // APP_H