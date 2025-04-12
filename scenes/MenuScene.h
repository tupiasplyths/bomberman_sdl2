#ifndef MENUSCENE_H
#define MENUSCENE_H

#include <SDL2/SDL.h>
#include <memory>

#include "scenes/Scene.h"
#include "entities/Text.h"

class MenuScene : public Scene
{
public:
    MenuScene(App *_app);
    void onEvent(const SDL_Event &event);
    void onActivate();

private:
    std::shared_ptr<Text> startText;
    std::shared_ptr<Text> exitText;
    const SDL_Color default_color = {255, 255, 255, 255};
    const SDL_Color selected = {255, 0, 0, 255};
    bool startItemSelected = false;
};

#endif // MENUSCENE_H