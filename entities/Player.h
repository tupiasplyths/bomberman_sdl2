#ifndef _PLAYER_H_
#define _PLAYER_H_

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
    Player(SDL_Renderer *renderer, std::shared_ptr<SDL_Texture> texture);
    void setDirection(directions direction);
    virtual void update(const int delta) override;

private:
    directions direction = directions::NONE;
    directions lastDirection = directions::NONE;
    bool isMovingVertical();
    bool isMovingHorizontal();
    const float speed = 0.1f;
    std::shared_ptr<Animation> upAnimation;
    std::shared_ptr<Animation> downAnimation;
    std::shared_ptr<Animation> leftAnimation;
    std::shared_ptr<Animation> rightAnimation;
    std::shared_ptr<Animation> deathAnimation;
    std::shared_ptr<Animation> animation[4];
};

#endif // _PLAYER_H_