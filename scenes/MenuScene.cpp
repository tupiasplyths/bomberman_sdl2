#include <SDL2/SDL.h>
#include <iostream>

#include "app.h"
#include "scenes/Scene.h"
#include "scenes/MenuScene.h"
#include "scenes/GameScene.h"
// #include "entities/Sprite.h"

MenuScene::MenuScene(App *_app, std::string name) : Scene(_app, name)
{
    startText = std::make_shared<Text>(app->getTextures()->getFont(), "Start", app->getRenderer());
    startText->setColor(selected);
    startText->setSize(app->getWindowWidth() / 4, app->getWindowHeight() / 20);
    startText->setPosition(app->getWindowWidth() / 2 - startText->getWidth() / 2, app->getWindowHeight() / 2 - startText->getHeight());
    addObject(startText);

    exitText = std::make_shared<Text>(app->getTextures()->getFont(), "Exit", app->getRenderer());
    exitText->setSize(app->getWindowWidth() / 4, app->getWindowHeight() / 20);
    exitText->setPosition(app->getWindowWidth() / 2 - exitText->getWidth() / 2, app->getWindowHeight() / 2 + exitText->getHeight() - 30);
    addObject(exitText);
};

void MenuScene::onEvent(const SDL_Event &event)
{
    if (event.type == SDL_KEYDOWN)
    {
        switch (event.key.keysym.scancode)
        {
        case SDL_SCANCODE_DOWN:
        case SDL_SCANCODE_S:
            // std::cout << "Down" << std::endl;
            if (startItemSelected)
            {
                startText->setColor(default_color);
                exitText->setColor(selected);
                startItemSelected = false;
            }
            else
            {
                startText->setColor(selected);
                exitText->setColor(default_color);
                startItemSelected = true;
            }
            break;

        case SDL_SCANCODE_W:
        case SDL_SCANCODE_UP:
            // std::cout << "Up" << std::endl;
            if (startItemSelected)
            {
                startText->setColor(selected);
                exitText->setColor(default_color);
                startItemSelected = false;
            }
            else
            {
                startText->setColor(default_color);
                exitText->setColor(selected);
                startItemSelected = true;
            }
            break;
        case SDL_SCANCODE_RETURN:
            if (startItemSelected)
            {
                app->addScene("game", std::make_shared<GameScene>(app, "game"));
                app->activateScene("game");
                std::cout << "Starting game..." << std::endl;
            }
            else
            {
                std::cout << "Exit game" << std::endl;
                app->stop();
            }
            break;
        default:
            break;
        }
    }
}

void MenuScene::onActivate()
{
    startText->setColor(selected);
    exitText->setColor(default_color);
    startItemSelected = true;
}