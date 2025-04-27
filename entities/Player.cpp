#include "entities/Player.h"
#include "entities/Sprite.h"

Player::Player(std::shared_ptr<SDL_Texture> texture, SDL_Renderer *renderer) : MovingEntity(texture, renderer)
{
    if (!texture) printf("There's no texture\n");
    std::shared_ptr<Animation> upAnimation = std::make_shared<Animation>();
    std::shared_ptr<Animation> downAnimation = std::make_shared<Animation>();
    std::shared_ptr<Animation> leftAnimation = std::make_shared<Animation>();
    std::shared_ptr<Animation> rightAnimation = std::make_shared<Animation>();
    deathAnimation = std::make_shared<Animation>();

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

    animation[directions::UP] = upAnimation;
    animation[directions::DOWN] = downAnimation;
    animation[directions::LEFT] = leftAnimation;
    animation[directions::RIGHT] = rightAnimation;
    for (auto &anim : animation)
    {
        anim.second->setSprite(this);
    }
    deathAnimation->setSprite(this);
    addAnimation(animation[directions::UP]);
    addAnimation(animation[directions::DOWN]);
    addAnimation(animation[directions::LEFT]);
    addAnimation(animation[directions::RIGHT]);
    addAnimation(deathAnimation);

    upAnimation = nullptr;
    downAnimation = nullptr;
    leftAnimation = nullptr;
    rightAnimation = nullptr;
}

void Player::setDirection(directions _direction)
{
    
    // printf("%d\n", _direction);
    direction = _direction;
    setMoving(true);
    switch (_direction)
    {
    case directions::NONE:
        if (lastDirection != directions::NONE)
            animation[lastDirection]->stop();
        else 
        {
            animation[directions::DOWN]->play();
            animation[directions::DOWN]->reset();
        } 
        setMoving(false);
        break;
    default:
        if (direction != lastDirection && lastDirection != directions::NONE)
        {
            animation[lastDirection]->reset();
        }
        animation[direction]->play();
        lastDirection = direction;
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
    if (isDead)
    {
        deathAnimation->play();
    }
    if (isMoving())
    {
        const int moveDistance = speed * delta * getWidth();
        prevX = moveDistance * (isMovingHorizontal() ? (direction == directions::LEFT ? -1 : 1) : 0);
        prevY = moveDistance * (isMovingVertical() ? (direction == directions::UP ? -1 : 1) : 0);
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
    MovingEntity::update(delta);
}

// void Player::playDeathAnimation()
// {
//     printf("Playing death animation\n");
//     deathAnimation->play();
// }