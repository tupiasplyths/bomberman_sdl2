#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__

#include <SDL2/SDL.h>
#include <memory>
#include <utility>
#include <vector>

#include "entities/Text.h"
#include "scenes/Scene.h"
#include "entities/Player.h"

class GameScene : public Scene
{
public:
    GameScene(App *_app);
    virtual void update(const int delta);
    virtual void onEvent(const SDL_Event &event);

private:
    void spawnPlayer();
    void spawnWall(const int posX, const int posY);
    void debug();
    std::shared_ptr<Player> player;
    void exit();
    void updateMovement(const bool keyPressed, const int keycode);
};

#endif // __GAMESCENE_H__