#include <SDL2/SDL.h>
#include <memory>
#include <vector>

#include "scenes/Scene.h"
// #include "entities/Player.h"
#include "scenes/GameScene.h"
#include "app.h"

GameScene::GameScene(App *_app) : Scene(_app)
{
    spawnPlayer();
}

void GameScene::update(const int delta)
{
    Scene::update(delta);
}

void GameScene::spawnPlayer()
{
    player = std::make_unique<Player>(app->getRenderer(), app->getTextures()->getTexture(Texture::texture_name::PLAYER));
    player->setPosition(app->getWindowWidth() / 2, app->getWindowHeight() / 2);
    player->setSize(32, 48);
    player->setClip(0, 48, 32, 48);
    addObject(player);
}

void GameScene::onEvent(const SDL_Event &event)
{

}

void GameScene::exit()
{

}

void GameScene::updateMovement(const bool keyPressed, const int keycode)
{

}