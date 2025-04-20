#ifndef _MOVINGENTITIES_H
#define MOVINGENTITIES_H
#include "entities/Sprite.h"

class MovingEntity : public Sprite
{
public:
    using Sprite::Sprite;
    void setMoving(bool moving);
    bool isMoving() const;
protected:
    int prevX = 0;
    int prevY = 0;
private:
    bool moving = false;
};


#endif // _MOVINGENTITIES_H