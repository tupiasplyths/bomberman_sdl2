#include "entities/MovingEntities.h"

void MovingEntity::setMoving(bool moving)
{
    this->moving = moving;
}
bool MovingEntity::isMoving() const
{
    return moving;
}

void MovingEntity::setDead()
{
    moving = false;
    isDead = true;
}

bool MovingEntity::getDead()
{
    return isDead;
}

void MovingEntity::revertLastMove()
{
    // printf("Reverting last move\n");
    setPosition(getX() - prevX, getY() - prevY);
}