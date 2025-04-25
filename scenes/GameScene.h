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
    GameScene(App * _app, std::string name);
    virtual void update(const int delta);
    virtual void onEvent(const SDL_Event &event);
    bool checkCollision(const SDL_Rect &rect1, const SDL_Rect &rect2) const;

private:
    void spawnPlayer();
    void spawnWall(const int posX, const int posY);
    void spawnGrass(const int posX, const int posY);
    void spawnBrick(const int posX, const int posY);
    void spawnBalloom(const int posX, const int posY);
    void spawnBomb(Object *object);
    void spawnExplosion(Object *object);
    void spawnPortal(Object *object);
    void generateMap();
    void debug();
    int playerStartPosX = 0;
    int playerStartPosY = 0;
    std::vector<std::shared_ptr<Enemy>> enemies;
    std::shared_ptr<Player> player;
    std::shared_ptr<Sprite> bomb = nullptr;
    std::shared_ptr<Sprite> portal = nullptr;
    void exit();
    void updateMovement(const bool keyPressed, const int keycode);
};

#endif // GAMESCENE_H