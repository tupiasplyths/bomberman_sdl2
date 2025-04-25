#include <SDL2/SDL.h>
#include <memory>
#include <vector>
#include <string>
#include <iostream>

#include "scenes/Scene.h"
#include "entities/Player.h"
#include "scenes/GameScene.h"
#include "app.h"

GameScene::GameScene(App *_app) : Scene(_app)
{
    std::cout << app->getTextures()->getTexture(Texture::texture_name::WALL) << std::endl;
    spawnPlayer();
    spawnWall(512, 256);
    auto text = std::make_shared<Text>(app->getTextures()->getFont(), "GameScene", app->getRenderer());
    text->setSize(app->getWindowWidth() / 16, app->getWindowHeight() / 80);
    addObject(text);
}

void GameScene::update(const int delta)
{
    Scene::update(delta);
}

void GameScene::spawnPlayer()
{
    std::cout << "Player spawned" << std::endl;
    player = std::make_unique<Player>
    (
        app->getTextures()->getTexture(Texture::texture_name::PLAYER),
        app->getRenderer()
    );
    player->setPosition(app->getWindowWidth() / 2, app->getWindowHeight() / 2);
    player->setSize(32, 48);
    player->setClip(0, 48, 32, 48);
    addObject(player);
}

void GameScene::onEvent(const SDL_Event &event)
{
    Scene::onEvent(event);
    if ((event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) && event.key.repeat == 0)
    {
        updateMovement(event.type == SDL_KEYDOWN? true : false, event.key.keysym.scancode);
    }
}

void GameScene::exit()
{
    app->activateScene("menu");
    app->removeScene("game");
    std::cout << "Game scene exited" << std::endl;
}

void GameScene::updateMovement(const bool keyPressed, const int keycode)
{
    if (player == nullptr) return;
    if (keyPressed)
    {
        switch (keycode)
        {
            case SDL_SCANCODE_W:
                player->setDirection(Player::directions::UP);
                std::cout << "move up" << std::endl;
                break;
            case SDL_SCANCODE_A:
                player->setDirection(Player::directions::LEFT);
                break;
            case SDL_SCANCODE_S:
                player->setDirection(Player::directions::DOWN);
                break;
            case SDL_SCANCODE_D:
                player->setDirection(Player::directions::RIGHT);
                break;
            case SDL_SCANCODE_ESCAPE:
                exit();
                break;
            case SDL_SCANCODE_BACKSLASH:
                debug();
                break;
            default:
                break;
        }
    }
    else 
    {
        player->setDirection(Player::directions::NONE);
    }
}

void GameScene::spawnWall(const int posX, const int posY)
{
    auto wall = std::make_shared<Sprite>(app->getTextures()->getTexture(Texture::texture_name::WALL), app->getRenderer());
    wall->setPosition(posX, posY);
    wall->setSize(32, 32);
    wall->setClip(0, 0, 32, 32);
    addObject(wall);
    std::cout << "Wall spawned" << std::endl;
}

void GameScene::debug()
{
    std::cout << player->getX() << " " << player->getY() << std::endl;
}