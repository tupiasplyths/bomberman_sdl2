#include "app.h"
#include "scenes/Scene.h"
#include <SDL2/SDL.h>
#include <iostream>
#include "scenes/GameOverScene.h"

GameOverScene::GameOverScene(App *_app, std::string name) : Scene(_app, name)
{
    text = std::make_shared<Text>(app->getTextures()->getFont(), "Game Over", app->getRenderer());
    text->setSize(app->getWindowWidth() / 8, app->getWindowHeight() / 40);
    text->setPosition(0, app->getWindowHeight() - text->getHeight());
    addObject(text);
}

void GameOverScene::onEvent(const SDL_Event &event)
{   
}

void GameOverScene::onActivate()
{
}
