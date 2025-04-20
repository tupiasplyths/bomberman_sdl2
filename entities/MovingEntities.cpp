#include "entities/MovingEntities.h"

void MovingEntity::setMoving(bool moving)
{
    this->moving = moving;
}
bool MovingEntity::isMoving() const
{
    return moving;
}