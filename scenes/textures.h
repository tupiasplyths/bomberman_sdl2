#ifndef TEXTURES_H
#define TEXTURES_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <memory>
#include <unordered_map>

class Texture
{
public:
    enum class texture_name : int
    {
        BOMB,
        PLAYER,
        BALLOOM,
        BRICK,
        WALL,
        GRASS,
        EXPLOSION,
        PORTAL,
    };
    void load(SDL_Renderer *renderer);
    std::shared_ptr<SDL_Texture> getTexture(Texture::texture_name name);
    std::shared_ptr<TTF_Font> getFont();
    struct EnumClassHash
    {
        template <typename T>
        std::size_t operator()(T t) const
        {
            return static_cast<std::size_t>(t);
        }
    };

private:
    int texture_width = 0;
    int texture_height = 0;
    std::shared_ptr<TTF_Font> font = nullptr;
    std::unordered_map<texture_name, std::shared_ptr<SDL_Texture>, EnumClassHash> textures;
    void loadFont();
    void loadTexture(SDL_Renderer *renderer, texture_name name, const char *filename);
};

#endif // TEXTURES_H