#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <SDL2/SDL.h>
#include <memory>
#include <utility>
#include <vector>

#include "entities/Text.h"
#include "scenes/Scene.h"
#include "entities/Player.h"
#include "entities/Enemy.h"

class GameScene : public Scene
{
public:
    enum class Tile
    {
        Wall,
        Grass,
        Brick,
        EmptyGrass,
        Bomb,
        Explosion
    };
    const int explosionPositions[5][2] = {{0, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, 0}}; // cell's position of bang

    GameScene(App * _app, std::string name);
    virtual void update(const int delta);
    virtual void onEvent(const SDL_Event &event);
    bool checkCollision(const SDL_Rect &rect1, const SDL_Rect &rect2) const;

private:
    Tile gameMap[16][16];
    void spawnPlayer();
    void spawnWall(const int posX, const int posY);
    void spawnGrass(const int posX, const int posY);
    void spawnBrick(const int posX, const int posY);
    void spawnBalloom(const int posX, const int posY);
    void spawnBomb(Object *object);
    void spawnExplosion(Object *object);
    void spawnPortal(Object *object);
    void generateMap();
    void generateEnemies();
    void debug();
    int playerStartPosX = 0;
    int playerStartPosY = 0;
    std::vector<std::shared_ptr<Enemy>> enemies;
    std::shared_ptr<Player> player;
    std::shared_ptr<Sprite> bomb = nullptr;
    std::shared_ptr<Sprite> portal = nullptr;
    void exit();
    void updateMovement(const bool keyPressed, const int keycode);
    int backgroundCount = 0;
    int bombTimer = 0;
    int explosionTimer = 0;
};

#endif // GAMESCENE_H