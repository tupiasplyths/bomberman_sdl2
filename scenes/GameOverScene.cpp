#include <SDL2/SDL.h>
#include <iostream>

#include "app.h"
#include "scenes/Scene.h"
#include "scenes/MenuScene.h"
#include "scenes/GameOverScene.h"

GameOverScene::GameOverScene(App *_app, std::string name) : Scene(_app, name)
{
    text = std::make_shared<Text>(app->getTextures()->getFont(), "Game Over", app->getRenderer());
    text->setSize(app->getWindowWidth() / 4, app->getWindowHeight() / 20);
    text->setPosition(app->getWindowWidth()/2 - text->getWidth(), app->getWindowHeight() / 2 - text->getHeight());
    addObject(text);
}

// void GameOverScene::onEvent(const SDL_Event &event)
// {   
// }

// void GameOverScene::onActivate()
// {
// }

void GameOverScene::update(const int delta) 
{
    untilNextSceneTimer += delta;
    printf("%d", untilNextSceneTimer);
    if (untilNextSceneTimer >= sceneTimer)
    {
        untilNextSceneTimer = 0;
        app->activateScene("menu");
        app->removeScene("gameover");
    }
}