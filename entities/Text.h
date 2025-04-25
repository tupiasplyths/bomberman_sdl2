#ifndef TEXT_H
#define TEXT_H

#include <SDL2/SDL_ttf.h>
#include "entities/Object.h"
#include "scenes/textures.h"
#include <string>

class Text : public Object
{
public:
    Text(std::shared_ptr<TTF_Font> font, const std::string &text, SDL_Renderer *renderer);
    void setText(const std::string &text);
    void setColor(const SDL_Color &color);
    void setFont(TTF_Font *font);

private:
    void loadText();
    std::shared_ptr<TTF_Font> font = nullptr;
    std::string text;
    SDL_Color color = {255, 255, 255, 255};
};

#endif // TEXT_H