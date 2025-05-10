#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <unordered_map>
#include "Animation.h"
#include "entities/MovingEntities.h"

class Player : public MovingEntity
{
public:
    enum directions : int
    {
        UP,
        DOWN,
        LEFT,
        RIGHT,
        NONE,
    };
    struct EnumClassHash
    {
        template<typename T> std::size_t operator()(T t) const
        {
            return static_cast<std::size_t>(t);
        }
    };
    // Player(std::shared_ptr<SDL_Texture> texture, SDL_Renderer *renderer);
    Player(std::shared_ptr<SDL_Texture> texture, SDL_Renderer *renderer);
    void setDirection(directions direction);
    virtual void update(const int delta) override;

private:
    directions direction = directions::NONE;
    directions lastDirection = directions::NONE;
    bool isMovingVertical();
    bool isMovingHorizontal();
    const float speed = 0.007f;
    std::shared_ptr<Animation> deathAnimation;
    std::unordered_map<directions, std::shared_ptr<Animation>, EnumClassHash> animation;
    std::shared_ptr<Animation> animations;
};



#endif // _PLAYER_H_