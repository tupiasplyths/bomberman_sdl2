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
}

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
    if (!isPlaying) return;
    if (!sprite || animation.size() < 1)
    {
        printf("sprite not set or too small\n");
        return;
    }
    time += delta;
    // printf("playing animation\n");
    if (time >= interval)
    {
        time = 0;
        AnimationObject obj = animation[currentObject];
        currentObject = (currentObject + 1) % (int)animation.size(); // go to the next frame of the sprites
        sprite->setClip(obj.width, obj.height, obj.positionX, obj.positionY);
        // currentObject++;
    }
};

AnimationObject::AnimationObject(int positionX, int positionY, int width, int height)
{
    this->positionX = positionX;
    this->positionY = positionY;
    this->width = width;
    this->height = height;
}
