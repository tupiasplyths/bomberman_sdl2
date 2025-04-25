#include <SDL2/SDL.h>
#include <memory>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#include "scenes/Scene.h"
#include "entities/Player.h"
#include "scenes/GameScene.h"
#include "entities/Enemy.h"
#include "scenes/GameOverScene.h"
#include "app.h"

GameScene::GameScene(App *_app, std::string name) : Scene(_app, name)
{
    auto text = std::make_shared<Text>(app->getTextures()->getFont(), "GameScene", app->getRenderer());
    text->setSize(app->getWindowWidth() / 16, app->getWindowHeight() / 80);
    text->setPosition(0, app->getWindowHeight() - text->getHeight());
    addObject(text);
    // std::shared_ptr<SDL_Texture> tmp = app->getTextures()->getTexture(Texture::texture_name::WALL);
    // std::cout << tmp << std::endl;
    // std::shared_ptr<Sprite> wall1 = std::make_shared<Sprite>(tmp, app->getRenderer());
    // wall1->setSize(32, 32);
    // std::cout << wall1->hasTexture() << std::endl;
    // wall1->setPosition(256, 256);
    // wall1->draw();
    // addObject(wall1);
    generateMap();
    spawnPlayer();
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
    player->setPosition(playerStartPosX, playerStartPosY);
    player->setSize(32, 48);
    player->setClip(32, 48, 0, 48);
    addObject(player);
}

void GameScene::spawnWall(const int posX, const int posY)
{
    auto wall = std::make_shared<Sprite>(app->getTextures()->getTexture(Texture::texture_name::WALL), app->getRenderer());
    if (!wall->hasTexture()) 
    {
        printf("Err: texture is null\n");
    }
    else 
        printf("Texture \n");
    wall->setPosition(posX, posY);
    wall->setSize(32, 32);
    wall->setClip(32, 32, 0, 0);
    addObject(wall);
}

void GameScene::spawnBrick(const int posX, const int posY)
{
    auto brick = std::make_shared<Sprite>(app->getTextures()->getTexture(Texture::texture_name::BRICK), app->getRenderer());
    brick->setPosition(posX, posY);
    brick->setSize(32, 32);
    brick->setClip(32, 32, 0, 0);
    addObject(brick);
}

void GameScene::spawnBalloom(const int posX, const int posY)
{
    auto balloom = std::make_shared<Enemy>(app->getTextures()->getTexture(Texture::texture_name::BALLOOM), app->getRenderer());
    balloom->setPosition(posX, posY);
    balloom->setSize(32, 32);
    balloom->setClip(32, 32, 0, 0);
    addObject(balloom);
    enemies.push_back(balloom);
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
    if (player->getDead())
    {
        app->addScene("gameover", std:: make_shared<GameOverScene>(app, "gameover"));
        app->activateScene("gameover");
        app->removeScene("game");
    } 
    for (auto &enemy : enemies)
    {
        if (checkCollision(player->getRect(), enemy->getRect()))
        {
            player->setDead();
            player->setDirection(Player::directions::NONE);
            break;
        }
    }

    if (keyPressed)
    {
        switch (keycode)
        {
            case SDL_SCANCODE_W:
                player->setDirection(Player::directions::UP);
                // std::cout << "move up" << std::endl;
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
                // debug();
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

// void GameScene::debug()
// {
//     std::cout << player->getX() << " " << player->getY() << std::endl;
// }

void GameScene::spawnGrass(const int posX, const int posY)
{
    auto grass = std::make_shared<Sprite>(app->getTextures()->getTexture(Texture::texture_name::GRASS), app->getRenderer());
    grass->setPosition(posX, posY);
    grass->setSize(32, 32);
    grass->setClip(32, 32, 0, 0);
    addObject(grass);
}

void GameScene::generateMap()
{
    std::ifstream file("assets/textures/maps/Level1.txt");
    if (!file.is_open())
    {
        std::cerr << "Error: Could not open map file!" << std::endl;
        return;
    }
    std::string line;
    int x = 0;
    int y = 0;
    while (std::getline(file, line))
    {
        for (int x = 0; x < line.length(); x++)
        {
            switch (line[x])
            {
            case 'W':
                spawnWall(x * 32, y * 32);
                break;
            case 'B':
                spawnBrick(x * 32, y * 32);
                break;
            case '1':
                playerStartPosX = x * 32;
                playerStartPosY = y * 32;
                spawnGrass(x * 32, y * 32);
                break;
            case 'b':
                spawnGrass(x * 32, y * 32);
                spawnBalloom(x * 32, y * 32);
                break;
            case '0':
                spawnGrass(x * 32, y * 32);
                break;
            case ' ':
                // x--;
                break;
            default:
                std::cout << "Unknown character in map file: " << line[x] << std::endl;
                break;
            }
        }
        y++;
    }
    file.close();
}

bool GameScene::checkCollision(const SDL_Rect &rect1, const SDL_Rect &rect2) const
{
    return SDL_HasIntersection(&rect1, &rect2);
}