#ifndef _MOVINGENTITIES_H
#define MOVINGENTITIES_H
#include "entities/Sprite.h"

class MovingEntity : public Object
{
public:
    using Sprite::Sprite;
    void setMoving(bool moving);
    bool isMoving() const;
private:
    bool moving = false;
};


#endif // _MOVINGENTITIES_H