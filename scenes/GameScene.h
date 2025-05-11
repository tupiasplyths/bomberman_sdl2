#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <SDL2/SDL.h>
#include <memory>
#include <utility>
#include <vector>
#include <chrono>

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

    GameScene(App *_app, std::string name);
    virtual void update(const int delta) override;
    virtual void onEvent(const SDL_Event &event);
    bool checkCollision(const SDL_Rect &rect1, const SDL_Rect &rect2) const;
    template <typename Enumeration>
    auto as_integer(Enumeration const value)
        -> typename std::underlying_type<Enumeration>::type
    {
        return static_cast<typename std::underlying_type<Enumeration>::type>(value);
    }

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
    void updateTimers(const int delta);
    void updateBombTimer(const int delta);
    void updateExplosionTimer(const int delta);
    void updateChargeTimer(const int delta);
    void updateMovement(const bool keyPressed, const int keycode);
    void updateBombMovement(int delta);
    void updatePlayerCollision();
    void updateEnemiesCollision();
    void updateExplosionsCollision();
    void destroyBrick(std::shared_ptr<Object> object);
    void updatePlayerDeath(const int delta);
    void KickBomb(int level);
    void moveBomb(Player::directions dir, int distance);
    bool isNextToBomb();
    float bombSpeedArr[6] = {0.005f, 0.006f, 0.008f, 0.009f, 0.01f, 0.014f}; // storing bomb speed levels
    unsigned int getSeed();
    void debug();
    int playerStartPosX = 0;
    int playerStartPosY = 0;
    std::vector<std::shared_ptr<Enemy>> enemies;
    std::shared_ptr<Player> player;
    std::shared_ptr<Sprite> bomb = nullptr;
    std::shared_ptr<Sprite> portal = nullptr;
    std::vector<std::shared_ptr<Object>> explosions;
    std::vector<std::pair<Tile, std::shared_ptr<Object>>> collisions;
    void exit();
    int bombDesX = -1; // bomb X destination for kicking
    int bombDesY = -1; // bomb Y destination for kicking
    int backgroundCount = 0; // background count for inserting objects
    int chargeTimer = 0;
    int bombTimer = 0;
    int explosionTimer = 0;
    int playerDeathTimer = 750;
    bool pauseBombTimer = false; // pause bomb timer when bomb is moving or player charging
    bool isCharging = false;
    bool bombMoving = false;
    float bombSpeed = 0; // bomb movement speed after kicked
};

#endif // GAMESCENE_H