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
#include "scenes/WinScene.h"
#include "entities/Text.h"
#include "app.h"

GameScene::GameScene(App *_app, std::string name) : Scene(_app, name)
{
    app->addScene("gameover", std::make_shared<GameOverScene>(app, "gameover"));
    app->addScene("win", std::make_shared<WinScene>(app, "win"));
    auto text = std::make_shared<Text>(app->getTextures()->getFont(), "GameScene", app->getRenderer());
    text->setSize(app->getWindowWidth() / 10, app->getWindowHeight() / 50);
    text->setPosition(0, app->getWindowHeight() - text->getHeight());
    chargeBar = std:: make_shared<Text>(app->getTextures()->getFont(), "||||||", app->getRenderer());
    
    
    generateMap();
    spawnPlayer();
    generateEnemies();
    addObject(text);
    backgroundCount++;
    // addObject(chargeBar);
    // backgroundCount++;
}

void GameScene::update(const int delta)
{
    Scene::update(delta);
    updateTimers(delta);
    updatePlayerCollision();
    updateEnemiesCollision();
    updateExplosionsCollision();
    updateBombMovement(delta);
    updateCharging();
}

void GameScene::onEvent(const SDL_Event &event)
{
    Scene::onEvent(event);

    if ((event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) && event.key.repeat == 0)
    {
        updateMovement(event.type == SDL_KEYDOWN ? true : false, event.key.keysym.scancode);
    }

    if (event.type == SDL_KEYDOWN)
    {
        // we should go to main menu by Escape key
        if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
        {
            exit();
        }
        if (event.key.keysym.scancode == SDL_SCANCODE_BACKSLASH)
        {
            debug();
        }
    }
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

    if (player->getDead() && explosionTimer < 200)
    {
        updatePlayerDeath(delta);
    }

    if (isCharging)
    {
        updateChargeTimer(delta);
    }
}

void GameScene::updateBombTimer(const int delta)
{
    if (pauseBombTimer || bombMoving)
    {
        return;
    }
    if (bombTimer > 0)
    {
        bombTimer -= delta;
    }
    else
    {
        spawnExplosion(bomb.get());
        removeObject(bomb);
        bomb = nullptr;
    }
}

void GameScene::updateChargeTimer(const int delta)
{
    chargeTimer += delta;
}

void GameScene::updateCharging()
{
    if (!isCharging)
    {
        // chargeBarWidth = 1;
        // chargeBar->setText(" ");
        removeObject(chargeBar);
        return;
    }

    if (chargeTimer > 2100)
    { // Max level (e.g., level 6: 6 * 350 = 2100)
        // chargeBarWidth = 48;
        chargeText = "||||||||||||";
    }
    else if (chargeTimer > 1750)
    { // Level 5
        // chargeBarWidth = 40;
        chargeText = "||||||||||  ";
    }
    else if (chargeTimer > 1400)
    { // Level 4
        // chargeBarWidth = 32;
        chargeText = "||||||||    ";
    }
    else if (chargeTimer > 1050)
    { // Level 3
        // chargeBarWidth = 24;
        chargeText = "||||||      ";
    }
    else if (chargeTimer > 700)
    { // Level 2
        // chargeBarWidth = 16;
        chargeText = "||||        ";
    }
    else if (chargeTimer > 350)
    { // Level 1
        // chargeBarWidth = 8;
        chargeText = "||          ";
    }
    else
    {
        // chargeBarWidth = 1;
        chargeText = " ";
    }

    chargeBar->setText(chargeText);
}

void GameScene::updateMovement(const bool keyPressed, const int keycode)
{
    if (player == nullptr)
        return;

    if (player->getDead())
        return;
    if (keyPressed)
    {
        switch (keycode)
        {
        case SDL_SCANCODE_W:
            player->setDirection(Player::directions::UP);
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
        case SDL_SCANCODE_SPACE:
            spawnBomb(player.get());
            break;
        case SDL_SCANCODE_O:
            printf("Pause bomb timer\n");
            pauseBombTimer = true;
            break;
        case SDL_SCANCODE_J:
            isCharging = true;
            pauseBombTimer = true;
            spawnChargeBar();
            break;
        default:
            break;
        }
    }
    else
    {
        switch (keycode)
        {
        case SDL_SCANCODE_J:
        {
            isCharging = false;
            pauseBombTimer = false;
            int level = chargeTimer / 350;
            printf("Charging level: %d\n", level);
            KickBomb(level);
            chargeTimer = 0;
            removeObject(chargeBar);
            break;
        }
        case SDL_SCANCODE_O:
            pauseBombTimer = false;
            break;
        default:
            player->setDirection(Player::directions::NONE);
            break;
        }
    }
}

void GameScene::updateBombMovement(int delta)
{
    if (!bomb || !bombMoving)
    {
        return;
    }

    const int diffX = bomb->getX() - bombDesX;
    const int diffY = bomb->getY() - bombDesY;
    const int signX = (diffX > 0) ? 1 : ((diffX < 0) ? -1 : 0);
    const int signY = (diffY > 0) ? 1 : ((diffY < 0) ? -1 : 0);

    int distance = floor(bombSpeed * delta * 32);
    if (abs(diffX) <= distance && abs(diffY) <= distance)
    {
        bomb->setPosition(bombDesX, bombDesY);
        bombMoving = false;
        return;
    }
    int newX = bomb->getX() - int(floor(distance) * signX);
    int newY = bomb->getY() - int(floor(distance) * signY);
    bomb->setPosition(newX, newY);
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

void GameScene::updatePlayerCollision()
{
    if (player == nullptr || player->getDead())
    {
        return;
    }
    if (!player->isMoving())
    {
        return;
    }
    SDL_Rect playerRect = player->getRect();
    playerRect.y += playerRect.h / 4;
    playerRect.x += playerRect.w / 4;
    playerRect.w = static_cast<int>(playerRect.w * 0.5);
    playerRect.h = static_cast<int>(playerRect.h * 0.5);
    // Move hitbox to bottom of player
    for (const auto &collisionObject : collisions)
    {
        if (checkCollision(playerRect, collisionObject.second->getRect()))
        {
            // std::cout << "Collided with something" << std::endl;
            player->revertLastMove();
        }
    }
    if (portal != nullptr)
    {
        if (checkCollision(playerRect, portal->getRect()))
        {
            if (enemies.size() == 0)
            {
                app->activateScene("win");
                std::cout << "You win!" << std::endl;
            }
        }
    }
}

void GameScene::updatePlayerDeath(const int delta)
{
    if (playerDeathTimer <= 0)
    {
        removeObject(player);
        player = nullptr;

        app->activateScene("gameover");
        app->removeScene("game");
    }
    else
    {
        playerDeathTimer -= delta;
        // player->playDeathAnimation();
    }
}

void GameScene::updateEnemiesCollision()
{
    // iterate enemies for collision
    for (const auto &enemy : enemies)
    {
        // iterate drawables for collision
        for (const auto &collisionObject : collisions)
        {
            auto enemyRect = enemy->getRect();
            enemyRect.y += enemyRect.h / 4;
            enemyRect.x += enemyRect.w / 4;
            enemyRect.w = static_cast<int>(enemyRect.w * 0.7);
            enemyRect.h = static_cast<int>(enemyRect.h * 0.7);
            // check for block collision
            if (checkCollision(enemyRect, collisionObject.second->getRect()))
            {
                // stop moving on collision detection
                enemy->setMoving(false);
                // std::cout << "enemy hit something" << std::endl;
                enemy->revertLastMove();
            }
        }
        // check for bomb collision
        if (bomb && checkCollision(enemy->getRect(), bomb->getRect()))
        {
            // stop moving on collision detection
            enemy->setMoving(false);
            enemy->revertLastMove();
        }
        // check for player collision
        if (player != nullptr)
        {
            // smaller hit box for player
            SDL_Rect playerRect = player->getRect();
            playerRect.y += playerRect.h / 2;
            playerRect.x += playerRect.w / 2;
            playerRect.w = static_cast<int>(playerRect.w * 0.2);
            playerRect.h = static_cast<int>(playerRect.h * 0.2);
            if (checkCollision(playerRect, enemy->getRect()))
            {
                // player killed by enemy
                std::cout << "Player killed by enemy" << std::endl;
                player->setDead();
                exit();
            }
        }
    }
}

void GameScene::updateExplosionsCollision()
{
    for (const auto &explosion : explosions)
    {
        // check bricks
        auto itCollision = collisions.begin();
        while (itCollision != collisions.end())
        {
            if ((*itCollision).first == Tile::Brick)
            {
                auto brick = (*itCollision).second;
                if (checkCollision(brick->getRect(), explosion->getRect()))
                {
                    destroyBrick(brick);
                    // remove brick from collision array
                    itCollision = collisions.erase(itCollision);
                    continue;
                }
            }
            ++itCollision;
        }
        // check enemies
        auto itEnemies = enemies.begin();
        while (itEnemies != enemies.end())
        {
            SDL_Rect enemyRect = (*itEnemies)->getRect();
            enemyRect.w = static_cast<int>(enemyRect.w * 0.3);
            enemyRect.h = static_cast<int>(enemyRect.h * 0.3);
            if (checkCollision(enemyRect, explosion->getRect()))
            {
                removeObject(*itEnemies);
                (*itEnemies)->setDead();
                itEnemies = enemies.erase(itEnemies);
                std::cout << "Enemy exploded" << std::endl;
                continue;
            }
            ++itEnemies;
        }
        // check player
        if (player != nullptr && !player->getDead())
        {
            SDL_Rect playerRect = player->getRect();
            playerRect.y += playerRect.h / 2;
            playerRect.x += playerRect.w / 2;
            playerRect.w = static_cast<int>(playerRect.w * 0.2f);
            playerRect.h = static_cast<int>(playerRect.h * 0.2f);

            if (checkCollision(playerRect, explosion->getRect()))
            {
                std::cout << "Player exploded" << std::endl;
                // removeObject(player);
                player->setDead();
                // player = nullptr;
                // exit();
            }
        }
    }
}

void GameScene::spawnPlayer()
{
    std::cout << "Player spawned" << std::endl;
    player = std::make_unique<Player>(
        app->getTextures()->getTexture(Texture::texture_name::PLAYER),
        app->getRenderer());

    player->setPosition(playerStartPosX, playerStartPosY);
    player->setSize(32, 32);
    player->setClip(32, 48, 0, 48);
    addObject(player);
}

void GameScene::spawnChargeBar()
{
    if (player && chargeBar)
    {
        chargeBar->setSize(36, 10); // Set the height of the chargeBar text
        chargeBar->setPosition(player->getX() - 4, player->getY() - chargeBar->getHeight() - 5);
    }
    insertObject(chargeBar, backgroundCount);
    // std::cout << "Charge bar spawned\n" << "Charge Text: " << chargeText << std::endl;
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
    collisions.push_back(std::make_pair(Tile::Wall, wall));
}

void GameScene::spawnBrick(const int posX, const int posY)
{
    auto brick = std::make_shared<Sprite>(app->getTextures()->getTexture(Texture::texture_name::BRICK), app->getRenderer());
    brick->setPosition(posX, posY);
    brick->setSize(32, 32);
    brick->setClip(32, 32, 0, 0);
    addObject(brick);
    collisions.push_back(std::make_pair(Tile::Brick, brick));
}

void GameScene::spawnBalloom(const int posX, const int posY)
{
    auto balloom = std::make_shared<Enemy>(app->getTextures()->getTexture(Texture::texture_name::BALLOOM), app->getRenderer());
    balloom->setPosition(posX, posY);
    balloom->setSize(32, 32);
    balloom->setClip(32, 32, 0, 0);
    addObject(balloom);
    enemies.push_back(balloom);
    // std::cout << "Balloom spawned at" << balloom->getX() << ", " <<  balloom->getY() << std::endl;
    // std::cout << "Enemies count: " << enemies.size() << std::endl;
}

void GameScene::spawnPortal(Object *object)
{
    portal =
        std::make_shared<Sprite>(app->getTextures()->getTexture(Texture::texture_name::PORTAL), app->getRenderer());
    portal->setSize(32, 32);
    portal->setClip(32, 32, 0, 0);
    // std::cout << portal->hasTexture() << std::endl;
    portal->setPosition(object->getX(), object->getY());
    insertObject(portal, backgroundCount);
    std::cout << "Portal spawned at " << portal->getX() << " " << portal->getY() << std::endl;
}

void GameScene::spawnGrass(const int posX, const int posY)
{
    auto grass = std::make_shared<Sprite>(app->getTextures()->getTexture(Texture::texture_name::GRASS), app->getRenderer());
    grass->setPosition(posX, posY);
    grass->setSize(32, 32);
    grass->setClip(32, 32, 0, 0);
    addObject(grass);
    backgroundCount++;
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

    bombX = bombDiffX > 16 ? bombX + 32 - bombDiffX : bombX - bombDiffX;
    bombY = bombDiffY > 16 ? bombY + 32 - bombDiffY : bombY - bombDiffY;

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
        round(bomb->getY() / static_cast<float>(32)));
    gameMap[bombCellY][bombCellX] = Tile::Bomb;

    bombTimer = 1500;
    animation->play();
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
    explosionTimer = 600;
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
            case '\n':
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

void GameScene::generateEnemies()
{
    // we need enemy in random tile
    auto randCount = std::bind(std::uniform_int_distribution<int>(2, 4),
                               std::mt19937(static_cast<unsigned int>(getSeed())));
    auto randType = std::bind(std::uniform_int_distribution<int>(0, 1),
                              std::mt19937(static_cast<unsigned int>(getSeed())));
    auto randCellX = std::bind(std::uniform_int_distribution<int>(0, 16 - 1),
                               std::mt19937(static_cast<unsigned int>(getSeed())));
    auto randCellY = std::bind(std::uniform_int_distribution<int>(0, 16 - 1),
                               std::mt19937(static_cast<unsigned int>(getSeed())));
    // start enemies spawn
    for (int i = 0; i < randCount(); i++)
    {
        // loop random x, y until Tile is not Brick, Wall or EmptyGrass
        int cellX = randCellX();
        int cellY = randCellY();
        while (gameMap[cellX][cellY] == Tile::Brick || gameMap[cellX][cellY] == Tile::Wall
               //    || gameMap[cellX][cellY] == Tile::
        )
        {
            cellX = randCellX();
            cellY = randCellY();
        }
        // spawn enemy
        printf("X:  %d, Y: %d\n", cellX, cellY);
        // std::cout << as_integer(gameMap[cellX][cellY]) << std::endl;
        spawnBalloom(cellX * 32, cellY * 32);
    }
}

void GameScene::destroyBrick(std::shared_ptr<Object> brick)
{
    std::cout << "Brick destroyed" << std::endl;
    // spawn door if not exist
    if (portal == nullptr)
    {
        // left bricks count
        long bricksCount = std::count_if(collisions.begin(), collisions.end(),
                                         [](auto collision)
                                         { return collision.first == Tile::Brick; });
        // random for door spawn
        const auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
        auto randDoor = std::bind(std::uniform_int_distribution<int>(0, 4),
                                  std::mt19937(static_cast<unsigned int>(seed)));
        // spawn door if we can
        if (randDoor() == 0 || bricksCount <= 3)
        {
            spawnPortal(brick.get());
        }
    }
    // change brick to grass and remove it
    const int brickCellX = static_cast<int>(
        round(brick->getX() / static_cast<float>(32)));
    const int brickCellY = static_cast<int>(
        round(brick->getY() / static_cast<float>(32)));
    gameMap[brickCellY][brickCellX] = Tile::Grass;
    removeObject(brick);
}

bool GameScene::checkCollision(const SDL_Rect &rect1, const SDL_Rect &rect2) const
{
    return SDL_HasIntersection(&rect1, &rect2);
}

unsigned int GameScene::getSeed()
{
    return static_cast<unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count());
}

void GameScene::exit()
{
    // app->activateScene("menu");
    app->activateScene("gameover");
    app->removeScene("game");
    std::cout << "Game scene exited" << std::endl;
}

void GameScene::debug()
{
    int i = 0;
    for (auto &enemy : enemies)
    {
        std::cout << "Enemy " << i << " at: " << enemy->getX() << ", " << enemy->getY() << std::endl;
        std::cout << "new: " << enemy->newX << ", " << enemy->newY << std::endl;
        i++;
    }
}

void GameScene::KickBomb(int level)
{
    if (player == nullptr || !bomb)
    {
        return;
    }
    if (!isNextToBomb())
    {
        return;
    }
    if (level > 6)
    {
        level = 6;
    }
    if (level == 0)
    {
        return;
    }

    Player::directions dir = player->getLastDirection();
    int distance = level * 32;
    bombSpeed = bombSpeedArr[level-1];
    moveBomb(dir, distance);
    // chargeTimer = 0;
}

void GameScene::moveBomb(Player::directions dir, int distance)
{
    if (bomb == nullptr)
    {
        return;
    }
    bombMoving = true;
    bombDesX = bomb->getX();
    bombDesY = bomb->getY();
    switch (dir)
    {
    case Player::UP:
        bombDesY -= distance;
        break;
    case Player::DOWN:
        bombDesY += distance;
        break;
    case Player::LEFT:
        bombDesX -= distance;
        break;
    case Player::RIGHT:
        bombDesX += distance;
        break;
    default:
        break;
    }
}

bool GameScene::isNextToBomb()
{
    if (player == nullptr)
    {
        return false;
    }

    int playerX = player->getX();
    int playerY = player->getY();
    int bombX = bomb->getX();
    int bombY = bomb->getY();

    int distanceX = abs(playerX - bombX);
    int distanceY = abs(playerY - bombY);

    // Check if the player is adjacent to the bomb (up, down, left, or right)
    if ((distanceX < 32) && distanceY < 32)
    {
        return true;
    }

    return false;
}