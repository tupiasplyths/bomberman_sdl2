#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2/SDL.h>
#include <vector>
#include <string>
#include "entities/Object.h"

class App;

class Scene 
{
    protected:
        App *app;
    private:
        std::vector<std::shared_ptr<Object>> objects;
    public:
        Scene(App *app, std::string name);
        void addObject(std::shared_ptr<Object> object);
        void removeObject(std::shared_ptr<Object> object);
        void insertObject(std::shared_ptr<Object> object, int pos);
        void draw();
        virtual void onEvent(const SDL_Event &event);
        void onActivate();
        void update(const int delta);
        std::string name;
};

#endif // TEXTURE_H