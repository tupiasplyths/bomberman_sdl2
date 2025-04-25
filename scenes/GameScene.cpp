#include <SDL2/SDL.h>
#include <memory>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <chrono>
#include <random>
#include <algorithm>
#include <functional>

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
    generateEnemies();
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

void GameScene::update(const int delta)
{
    Scene::update(delta);
    updateTimers(delta);
}

void GameScene::updateTimers(const int delta)
{
    if (bomb != nullptr)
    {
        updateBombTimer(delta);
    }

    if (explosions.size() > 0)
    {
        updateExplosionTimer(delta);
    }
}

void GameScene::updateBombTimer(const int delta)
{
    if (bombTimer > 0)
    {
        bombTimer -= delta;
    }
    else
    {
        std::cout << "Bomb exploded" << std::endl;
        spawnExplosion(bomb.get());
        removeObject(bomb);
        bomb = nullptr;
    }
}

void GameScene::updateExplosionTimer(const int delta)
{
    if (explosionTimer > 0)
    {
        explosionTimer -= delta;
    }
    else
    {
        for (auto &explosion : explosions)
        {
            removeObject(explosion);
            // change to grass
            const int explosionX = static_cast<int>(
                round((explosion->getX() / static_cast<float>(32))));
            const int explosionY = static_cast<int>(
                round((explosion->getY() / static_cast<float>(32))));
            gameMap[explosionY][explosionX] = Tile::EmptyGrass;
        }
        explosions.clear();
    }
}

void GameScene::spawnWall(const int posX, const int posY)
{
    auto wall = std::make_shared<Sprite>(app->getTextures()->getTexture(Texture::texture_name::WALL), app->getRenderer());
    if (!wall->hasTexture()) 
    {
        printf("Err: texture is null\n");
    }
    wall->setPosition(posX, posY);
    wall->setSize(32, 32);
    wall->setClip(32, 32, 0, 0);
    addObject(wall);
    backgroundCount++;
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

void GameScene::spawnBomb(Object *object)
{
    if (bomb || !object)
    {
        return;
    }
    std::cout << "Bomb placed" << std::endl;

    int bombX = object->getX();
    int bombY = object->getY();

    const int bombDiffX = bombX % 32;
    const int bombDiffY = bombY % 32;

    bombX = bombDiffX > 16? bombX + 32 - bombDiffX : bombX - bombDiffX;
    bombY = bombDiffY > 16? bombY + 32 - bombDiffY : bombY - bombDiffY;

    bomb = std::make_shared<Sprite>(app->getTextures()->getTexture(Texture::texture_name::BOMB), app->getRenderer());
    bomb->setPosition(bombX, bombY);
    bomb->setSize(32, 32);
    insertObject(bomb, backgroundCount);

    auto animation = std::make_shared<Animation>();
    animation->addAnimationObject(AnimationObject(0, 0, 32, 32));
    animation->addAnimationObject(AnimationObject(32, 0, 32, 32));
    animation->addAnimationObject(AnimationObject(64, 0, 32, 32));
    animation->addAnimationObject(AnimationObject(96, 0, 32, 32));

    animation->setSprite(bomb.get());
    bomb->addAnimation(animation);

    const int bombCellX = static_cast<int>(
        round(bomb->getX() / static_cast<float>(32)));
    const int bombCellY = static_cast<int>(
        round(bomb->getY()  / static_cast<float>(32)));
    gameMap[bombCellY][bombCellX] = Tile::Bomb;

    bombTimer = 1500;
    animation->play();
}

void GameScene::onEvent(const SDL_Event &event)
{
    Scene::onEvent(event);
    if (player->getDead())
    {
        // app->addScene("gameover", std:: make_shared<GameOverScene>(app, "gameover"));
        // app->activateScene("gameover");
        app->activateScene("menu");
        app->removeScene("game");
        return;
    }
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
    
    for (auto &enemy : enemies)
    {
        if (checkCollision(player->getRect(), enemy->getRect()))
        {
            std::cout << "Player hit by enemy" << std::endl; 
            player->setDead();
            player->setDirection(Player::directions::NONE);
            return;
        }
    }

    if (keyPressed)
    {
        switch (keycode)
        {
            case SDL_SCANCODE_W:
                if (player->getDead()) break;
                player->setDirection(Player::directions::UP);
                // std::cout << "move up" << std::endl;
                break;
            case SDL_SCANCODE_A:
                if (player->getDead())
                    break;
                player->setDirection(Player::directions::LEFT);
                break;
            case SDL_SCANCODE_S:
                if (player->getDead())
                    break;
                player->setDirection(Player::directions::DOWN);
                break;
            case SDL_SCANCODE_D:
                if (player->getDead())
                    break;
                player->setDirection(Player::directions::RIGHT);
                break;
            case SDL_SCANCODE_SPACE:
                if (player->getDead()) return;
                spawnBomb(player.get());
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

void GameScene::spawnExplosion(Object *object)
{
    const int bombCellX = static_cast<int>(
        round(bomb->getX() / static_cast<float>(32)));
    const int bombCellY = static_cast<int>(
        round(bomb->getY() / static_cast<float>(32)));
    gameMap[bombCellY][bombCellX] = Tile::Grass;
    // create bangs in position
    for (unsigned int i = 0; i < 5; i++)
    {
        auto explosion = std::make_shared<Sprite>(app->getTextures()->getTexture(Texture::texture_name::EXPLOSION), app->getRenderer());
        explosion->setSize(32, 32);
        explosion->setPosition(object->getX() + explosionPositions[i][0] * 32,
                               object->getY() + explosionPositions[i][1] * 32);
        addObject(explosion);
        explosions.push_back(explosion);
        const int explosionX = static_cast<int>(
            round(explosion->getX() / static_cast<float>(32)));
        const int explosionY = static_cast<int>(
            round(explosion->getY() / static_cast<float>(32)));
        gameMap[explosionY][explosionX] = Tile::Explosion;
        // animation
        auto animation = std::make_shared<Animation>();
        for (unsigned int j = 1; j < 12; j++)
        {
            animation->addAnimationObject(AnimationObject(32 * j, 0, 32, 32));
        }
        animation->setSprite(explosion.get());
        explosion->addAnimation(animation);
        animation->play();
    }
    // update timer
    explosionTimer = 800;
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
    backgroundCount++;
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
                gameMap[y][x] = Tile::Wall;
                break;
            case 'B':
                spawnGrass(x * 32, y * 32);
                spawnBrick(x * 32, y * 32);
                gameMap[y][x] = Tile::Brick;
                break;
            case '1':
                spawnGrass(x * 32, y * 32);
                gameMap[y][x] = Tile::Grass;
                playerStartPosX = x * 32;
                playerStartPosY = y * 32;
                break;
            case 'b':
                gameMap[y][x] = Tile::Grass;
                spawnGrass(x * 32, y * 32);
                // spawnBalloom(x * 32, y * 32);
                break;
            case '0':
                gameMap[y][x] = Tile::Grass;
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

void GameScene::generateEnemies()
{
    // we need enemy in random tile
    const auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    auto randCount = std::bind(std::uniform_int_distribution<int>(3, 6),
                               std::mt19937(static_cast<unsigned int>(seed)));
    auto randType = std::bind(std::uniform_int_distribution<int>(0, 1),
                              std::mt19937(static_cast<unsigned int>(seed)));
    auto randCellX = std::bind(std::uniform_int_distribution<int>(0, 16 - 1),
                               std::mt19937(static_cast<unsigned int>(seed)));
    auto randCellY = std::bind(std::uniform_int_distribution<int>(0, 16 - 1),
                               std::mt19937(static_cast<unsigned int>(seed)));
    // start enemies spawn
    for (int i = 0; i < randCount(); i++)
    {
        // try to find suitable tile
        int cellX = randCellX();
        int cellY = randCellY();
        while (gameMap[cellX][cellY] == Tile::Brick || gameMap[cellX][cellY] == Tile::Wall ||
               gameMap[cellX][cellY] == Tile::EmptyGrass)
        {
            cellX = randCellX();
            cellY = randCellY();
        }
        // spawn enemy
        spawnBalloom(cellX * 32, cellY * 32);
    }
}