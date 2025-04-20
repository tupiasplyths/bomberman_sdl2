#include "entities/Player.h"

Player::Player(SDL_Renderer *renderer, std::shared_ptr<SDL_Texture> texture) : MovingEntity(renderer, texture)
{
    animation = std::make_shared<Animation>();
    // move up
    animation->addAnimationObject(AnimationObject(0, 0, 32, 48));
    animation->addAnimationObject(AnimationObject(32, 0, 32, 48));
    animation->addAnimationObject(AnimationObject(64, 0, 32, 48));
    animation->addAnimationObject(AnimationObject(96, 0, 32, 48));
    // move down
    animation->addAnimationObject(AnimationObject(0, 48, 32, 48));
    animation->addAnimationObject(AnimationObject(32, 48, 32, 48));
    animation->addAnimationObject(AnimationObject(64, 48, 32, 48));
    animation->addAnimationObject(AnimationObject(96, 48, 32, 48));
    // move left
    animation->addAnimationObject(AnimationObject(0, 96, 32, 48));
    animation->addAnimationObject(AnimationObject(32, 96, 32, 48));
    animation->addAnimationObject(AnimationObject(64, 96, 32, 48));
    animation->addAnimationObject(AnimationObject(96, 96, 32, 48));
    // move right
    animation->addAnimationObject(AnimationObject(0, 144, 32, 48));
    animation->addAnimationObject(AnimationObject(32, 144, 32, 48));
    animation->addAnimationObject(AnimationObject(64, 144, 32, 48));
    animation->addAnimationObject(AnimationObject(96, 144, 32, 48));
    // die
    animation->addAnimationObject(AnimationObject(0, 192, 32, 48));
    animation->addAnimationObject(AnimationObject(32, 192, 32, 48));
    animation->addAnimationObject(AnimationObject(64, 192, 32, 48));
    animation->addAnimationObject(AnimationObject(96, 192, 32, 48));

    animation->setSprite(this);
    addAnimation(animation);
}
