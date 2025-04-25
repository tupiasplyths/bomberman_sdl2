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
    else
    {
        setFlip(SDL_FLIP_NONE);
    }
}

void Enemy::moveToCell(std::pair<int, int> pathToCell)
{
    path = pathToCell;
    movingToCell = true;

    newX = getX() - ((getX() - newX) % getWidth());
    newY = getY() - ((getY() - newY) % getHeight());
}

bool Enemy::isMovingToCell() const
{
    return movingToCell;
}

void Enemy::updateMovement(const int delta)
{
    if (isDead)
        return;

    const int diffX = getX() - newX;
    const int diffY = getY() - newY;
    int signX;
    int signY;
    if (diffX == 0)
    {
        signX = 0;
    }
    else if (diffX > 0)
    {
        signX = 1;
    }
    else
    {
        signX = -1;
    }

    if (diffY == 0)
    {
        signY = 0;
    }
    else if (diffY > 0)
    {
        signY = 1;
    }
    else
    {
        signY = -1;
    }

    const int distance = floor(baseSpeed * delta * getWidth());
    prevX = distance * -signX;
    prevY = distance * -signY;

    if (newX * signX <= distance && newY * signY <= distance)
    {
        movement->stop();
        setMoving(false);
        movingToCell = false;
        setPosition(newX, newY);
        return;
    }

    setPosition(getX() - int(floor(distance) * signX), getY() - int(floor(distance) * signY));
}

void Enemy::update(const int delta)
{
    MovingEntity::update(delta);
    if (isDead)
    {
        death->play();
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

void Enemy::generateNewPath()
{
    if (isDead)
        return;
    // create random func
    const auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    auto randPath = std::bind(std::uniform_int_distribution<int>(1, 10),
                              std::mt19937(static_cast<unsigned int>(seed)));
    auto randSign = std::bind(std::uniform_int_distribution<int>(-1, 1),
                              std::mt19937(static_cast<unsigned int>(seed)));

    // generate direction and cells
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