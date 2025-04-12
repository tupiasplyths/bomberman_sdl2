#include <SDL2/SDL.h>
#include <vector>
#include <algorithm>
#include "Scene.h"

Scene::Scene(App * _app)
{
    this->app = _app;
}
void Scene::addObject(std::shared_ptr<Object> object)
{
    objects.push_back(object);
}

void Scene::removeObject(std::shared_ptr<Object> object)
{
    objects.erase(std::remove(objects.begin(), objects.end(), object), objects.end());
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