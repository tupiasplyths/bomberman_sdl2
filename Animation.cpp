#include "entities/Sprite.h"
#include "Animation.h"

void Animation::addAnimationObject(AnimationObject object)
{
    animation.push_back(object);
}

void Animation::setSprite(Sprite *_sprite)
{
    sprite = _sprite;
}

void  Animation::setAnimationInterval(int milisec)
{
    interval = milisec;
}

void Animation::play()
{
    if (isPlaying)
    {
        return;
    }
    isPlaying = true;
    time = interval;
};

void Animation::stop()
{
    isPlaying = false;
};

void Animation::reset()
{
    stop();
    currentObject = 0;
    time = 0;
};

void Animation::update(const int delta)
{
    if (!isPlaying || !sprite)
    {
        return;
    }
    time -= delta;
    if (time <= 0)
    {
        time = interval;
        AnimationObject obj = animation[currentObject];
        sprite->setClip(obj.width, obj.height, obj.positionX, obj.positionY);
        // currentObject++;
        currentObject = (currentObject + 1) % animation.size(); // go to the next frame of the sprites
    }
};

