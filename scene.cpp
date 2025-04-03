#include <SDL2/SDL.h>
#include <vector>
#include <memory>
#include <algorithm>
#include "app.hpp"
#include "entities/Object.cpp"

class Scene
{
    private: 
        std::vector<std::shared_ptr<Object>> objects;
    protected:
        App *app;
    public:
        Scene(App *app);
        void addObject(std::shared_ptr<Object> object) 
        {
            objects.push_back(object);
        }

        void removeObject(std::shared_ptr<Object> object)
        {
            objects.erase(std::remove(objects.begin(), objects.end(), object), objects.end());
        }

        void update(const int delta) {
            for (auto &object : objects)
            {
                object->update(delta);
            }
        }

        void draw()
        {
            for (auto &object : objects)
            {
                object->draw();
            }
        }
};