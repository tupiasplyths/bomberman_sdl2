#include <SDL2/SDL.h>
#include <app.hpp>
#include <vector>
#include <memory>
#include <entities/Object.cpp>

class Scene
{
    public:
        Scene(App *app);
        void addObject(std::shared_ptr<Object> object);
};