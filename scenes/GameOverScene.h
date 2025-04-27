#ifndef GAMEOVERSCENE_H
#define GAMEOVERSCENE_H

#include <SDL2/SDL.h>
#include <memory>

#include "scenes/Scene.h"
#include "entities/Text.h"

class GameOverScene : public Scene
{
public:
    GameOverScene(App *_app, std::string name);
    // void onEvent(const SDL_Event &event);
    // void onActivate();
    virtual void update(const int delta);

private:
    int untilNextSceneTimer = 0;
    int sceneTimer = 1700;
    std::shared_ptr<Text> text;
    const SDL_Color default_color = {255, 255, 255, 255};
};

#endif // GAMEOVERSCENE_H