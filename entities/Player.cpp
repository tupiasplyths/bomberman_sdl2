#include "entities/Player.h"
#include "entities/Sprite.h"

Player::Player(std::shared_ptr<SDL_Texture> texture, SDL_Renderer *renderer) : MovingEntity(texture, renderer)
{
    upAnimation = std::make_shared<Animation>();
    downAnimation = std::make_shared<Animation>();
    leftAnimation = std::make_shared<Animation>();
    rightAnimation = std::make_shared<Animation>();
    deathAnimation = std::make_shared<Animation>();
    // animation = std::shared_ptr<Animation>[5];

    // move up
    upAnimation->addAnimationObject(AnimationObject(0, 0, 32, 48));
    upAnimation->addAnimationObject(AnimationObject(32, 0, 32, 48));
    upAnimation->addAnimationObject(AnimationObject(64, 0, 32, 48));
    upAnimation->addAnimationObject(AnimationObject(96, 0, 32, 48));
    // move down
    downAnimation->addAnimationObject(AnimationObject(0, 48, 32, 48));
    downAnimation->addAnimationObject(AnimationObject(32, 48, 32, 48));
    downAnimation->addAnimationObject(AnimationObject(64, 48, 32, 48));
    downAnimation->addAnimationObject(AnimationObject(96, 48, 32, 48));
    // move left
    leftAnimation->addAnimationObject(AnimationObject(0, 96, 32, 48));
    leftAnimation->addAnimationObject(AnimationObject(32, 96, 32, 48));
    leftAnimation->addAnimationObject(AnimationObject(64, 96, 32, 48));
    leftAnimation->addAnimationObject(AnimationObject(96, 96, 32, 48));
    // move right
    rightAnimation->addAnimationObject(AnimationObject(0, 144, 32, 48));
    rightAnimation->addAnimationObject(AnimationObject(32, 144, 32, 48));
    rightAnimation->addAnimationObject(AnimationObject(64, 144, 32, 48));
    rightAnimation->addAnimationObject(AnimationObject(96, 144, 32, 48));
    // die
    deathAnimation->addAnimationObject(AnimationObject(0, 192, 32, 48));
    deathAnimation->addAnimationObject(AnimationObject(32, 192, 32, 48));
    deathAnimation->addAnimationObject(AnimationObject(64, 192, 32, 48));
    deathAnimation->addAnimationObject(AnimationObject(96, 192, 32, 48));


    for (auto &anim : animation)
    {
        anim.second->setSprite(this);
    }
    animation[directions::UP] = upAnimation;
    animation[directions::DOWN] = downAnimation;
    animation[directions::LEFT] = leftAnimation;
    animation[directions::RIGHT] = rightAnimation;
    
}

void Player::setDirection(directions _direction)
{
    direction = _direction;
    setMoving(true);
    switch (_direction)
    {
    case directions::NONE:
        animation[direction]->reset();
        setMoving(false);
        break;
    default:
        if (direction != lastDirection)
        {
            animation[direction]->reset();
            lastDirection = direction;
        }
        animation[direction]->play();
        break;
    }
}

bool Player::isMovingVertical()
{
    return direction == directions::UP || direction == directions::DOWN;
}
bool Player::isMovingHorizontal()
{
    return direction == directions::LEFT || direction == directions::RIGHT;
}

void Player::update(const int delta)
{
    if (isMoving())
    {
        const int moveDistance = speed * delta * getWidth();
        if (isMovingVertical())
        {
            if (direction == directions::UP)
            {
                setPosition(getX(), getY() - moveDistance);
            }
            else
            {
                setPosition(getX(), getY() + moveDistance);
            }
        }
        else
        {
            if (direction == directions::LEFT)
            {
                setPosition(getX() - moveDistance, getY());
            }
            else
            {
                setPosition(getX() + moveDistance, getY());
            }
        }
    }
}