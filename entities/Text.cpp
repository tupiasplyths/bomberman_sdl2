#include <iostream>
#include "entities/Text.h"

Text::Text(std::shared_ptr<TTF_Font> font, const std::string &text, SDL_Renderer *renderer) : Object(renderer)
{
    this->font = font;
    this->text = text;
    loadText();
}

void Text::setText(const std::string &text)
{
    this->text = text;
    loadText();
}
void Text::setColor(const SDL_Color &color)
{
    this->color = color;
    loadText();
}
void Text::setFont(TTF_Font *font)
{
    this->font = std::shared_ptr<TTF_Font>(font, TTF_CloseFont);
    loadText();
}
void Text::loadText()
{
    if (!font)
    {
        std::cerr << "Font is not loaded" << std::endl;
        return;
    }
    SDL_Surface *surface = TTF_RenderUTF8_Solid(font.get(), text.c_str(), color);
    if (!surface)
    {
        std::cerr << "Failed to create surface: " << TTF_GetError() << std::endl;
        return;
    }
    texture = std::shared_ptr<SDL_Texture>(SDL_CreateTextureFromSurface(renderer, surface), SDL_DestroyTexture);
    if (!texture)
    {
        std::cerr << "Failed to create texture: " << SDL_GetError() << std::endl;
        return;
    }

    int height, width;
    SDL_QueryTexture(texture.get(), NULL, NULL, &width, &height);

    clip.x = 0;
    clip.y = 0;
    clip.w = width;
    clip.h = height;
    SDL_FreeSurface(surface);
}
