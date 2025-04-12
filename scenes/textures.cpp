#include "scenes/textures.h"
#include <iostream>

void Texture::load(SDL_Renderer *renderer)
{
    loadTexture(renderer, BOMB, "assets/textures/Bomb.png");
    loadTexture(renderer, PLAYER, "assets/textures/bomber1.png");
    loadTexture(renderer, BALLOOM, "assets/textures/balloom.png");
    loadTexture(renderer, BRICK, "assets/textures/Brick.png");
    loadTexture(renderer, WALL, "assets/textures/Wall.png");

    loadFont();
}

void Texture::loadFont()
{
    font = std::shared_ptr<TTF_Font>(TTF_OpenFont("assets/font.ttf", 32), TTF_CloseFont);
    if (!font)
    {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
    }
}

void Texture::loadTexture(SDL_Renderer *renderer, texture_name name, const std::string filename)
{
    textures[name] = std::shared_ptr<SDL_Texture>(IMG_LoadTexture(renderer, filename.c_str()), SDL_DestroyTexture);
    if (!textures[name])
    {
        std::cerr << "Failed to load texture: " << filename << " " << IMG_GetError() << std::endl;
    }
}

std::shared_ptr<TTF_Font> Texture::getFont()
{
    return font;
}