#include <chrono>
#include <random>
#include <functional>

#include "entities/Enemy.h"

Enemy::Enemy(std::shared_ptr<SDL_Texture> texture, SDL_Renderer *renderer) : MovingEntity(texture, renderer)
{
    movement = std::make_shared<Animation>();
    movement->addAnimationObject(AnimationObject(0, 0, 32, 48));
    movement->addAnimationObject(AnimationObject(32, 0, 32, 48));
    movement->addAnimationObject(AnimationObject(64, 0, 32, 48));
    movement->addAnimationObject(AnimationObject(96, 0, 32, 48));

    death = std::make_shared<Animation>();
    death->addAnimationObject(AnimationObject(0, 192, 32, 48));
    death->addAnimationObject(AnimationObject(32, 192, 32, 48));
    death->addAnimationObject(AnimationObject(64, 192, 32, 48));
    death->addAnimationObject(AnimationObject(96, 192, 32, 48));

    movement->setSprite(this);
    death->setSprite(this);
    addAnimation(movement);
    addAnimation(death);
}

void Enemy::moveTo(const int x, const int y)
{
    movement->play();
    setMoving(true);
    newX = getX() + x;
    newY = getY() + y;

    if (x < 0)
    {
        setFlip(SDL_FLIP_HORIZONTAL);
    }
    else if (x > 0)
    {
        setFlip(SDL_FLIP_NONE);
    }
}

bool Enemy::isMovingToCell() const
{
    return movingToCell;
}

void Enemy::updateMovement(const int delta)
{
    if (isDead)
    {
        return;
    }
    // X < new X => sign = -1 => distance is > 0
    const int diffX = getX() - newX;
    const int diffY = getY() - newY;
    const int signX = (diffX > 0) ? 1 : ((diffX < 0) ? -1 : 0);
    const int signY = (diffY > 0) ? 1 : ((diffY < 0) ? -1 : 0);

    const int distance = floor(baseSpeed * delta * getWidth());
    prevX = distance * -signX;
    prevY = distance * -signY;
    if (abs(diffX) <= distance && abs(diffY) <= distance)
    {
        // printf("reached\n");
        movement->stop();
        setMoving(false);
        movingToCell = false;
        setPosition(newX, newY);
        return;
    }
    int desX = getX() - int(floor(distance) * signX);
    int desY = getY() - int(floor(distance) * signY);

    setPosition(desX, desY);
}

void Enemy::update(const int delta)
{
    MovingEntity::update(delta);
    if (isDead && deathAnimationTimer < 1000)
    {
        deathAnimationTimer += delta;
        death->play();
        return;
    }
    if (isMoving())
    {
        updateMovement(delta);
    }
    else if (movingToCell)
    {
        moveTo(path.first * getWidth(), path.second * getHeight());
    }
    else
    {
        generateNewPath();
    }
}

unsigned int Enemy::getSeed()
{
    return static_cast<unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count());
}

void Enemy::generateNewPath()
{
    if (isDead)
        return;
    auto randPath = std::bind(std::uniform_int_distribution<int>(1, 5),
                              std::mt19937(static_cast<unsigned int>(getSeed())));
    auto randSign = std::bind(std::uniform_int_distribution<int>(-1, 1),
                              std::mt19937(static_cast<unsigned int>(getSeed())));
    const int randUpDown = randPath();
    const int randUpDownSign = randSign();
    if (randUpDownSign != 0)
    {
        moveTo(0, randUpDown * randUpDownSign * getHeight());
        return;
    }
    const int randLeftRight = randPath();
    const int randLeftRightSign = randSign();
    if (randLeftRightSign != 0)
    {
        moveTo(randLeftRight * randLeftRightSign * getWidth(), 0);
    }
}
