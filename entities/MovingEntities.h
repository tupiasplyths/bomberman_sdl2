#ifndef MOVINGENTITIES_H
#define MOVINGENTITIES_H

#include "entities/Sprite.h"

class MovingEntity : public Sprite
{
public:
    using Sprite::Sprite;
    void setMoving(bool moving);
    bool isMoving() const;
    void setDead();
    bool getDead();
    void revertLastMove();

protected:
    int prevX = 0;
    int prevY = 0;
    bool isDead = false;
private:
    bool moving = false;
};


#endif // MOVINGENTITIES_H