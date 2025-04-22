#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <vector>
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
    // Player(std::shared_ptr<SDL_Texture> texture, SDL_Renderer *renderer);
    Player(std::shared_ptr<SDL_Texture> texture, SDL_Renderer *renderer);
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
    std::unordered_map<directions, std::shared_ptr<Animation>> animation;
};

#endif // _PLAYER_H_