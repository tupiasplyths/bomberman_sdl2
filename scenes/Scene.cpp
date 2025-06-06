#include <SDL2/SDL.h>
#include <vector>
#include <algorithm>
#include "Scene.h"

Scene::Scene(App * _app, std::string name)
{
    this->name = name;
    this->app = _app;
}
void Scene::addObject(std::shared_ptr<Object> object)
{
    objects.push_back(object);
    // printf("Added object to scene\nCurrent objects in scene: %d\n", (int)objects.size());
}

void Scene::removeObject(std::shared_ptr<Object> object)
{
    objects.erase(std::remove(objects.begin(), objects.end(), object), objects.end());
}

void Scene::insertObject(std::shared_ptr<Object> object, int position)
{
    objects.insert(objects.begin() + position, object);
    printf("Inserted object at %d\nCurrent objects in scene: %d\n", position, (int)objects.size());
}

void Scene::update(const int delta)
{
    for (auto &object : objects)
    {
        object->update(delta);
    }
}

void Scene::draw()
{
    for (auto &object : objects)
    {
        object->draw();
    }
}

void Scene::onEvent(const SDL_Event & /*event*/)
{
}

void Scene::onActivate() 
{
}