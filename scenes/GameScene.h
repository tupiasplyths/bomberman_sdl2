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

private:
    
};

#endif // __GAMESCENE_H__