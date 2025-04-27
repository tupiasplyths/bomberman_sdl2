#ifndef WINSCENE_H
#define WINSCENE_H

#include <SDL2/SDL.h>
#include <memory>

#include "scenes/Scene.h"
#include "entities/Text.h"

class WinScene : public Scene
{
public:
    WinScene(App *_app, std::string name);
    virtual void update(const int delta);

private:
    int untilNextSceneTimer = 0;
    int sceneTimer = 1700;
    std::shared_ptr<Text> text;
    const SDL_Color default_color = {255, 255, 255, 255};
};

#endif // WINSCENE_H