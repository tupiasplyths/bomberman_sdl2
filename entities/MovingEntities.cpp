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
    isDead = true;
}

bool MovingEntity::getDead()
{
    return isDead;
}

void MovingEntity::revertLastMove()
{
    setPosition(getX() - prevX, getY() - prevY);
}