#ifndef ANIMATION_H
#define ANIMATION_H

#include <vector>

class Sprite;

class AnimationObject
{
public:
    AnimationObject(int positionX, int positionY, int width, int height);
    int positionX;
    int positionY;
    int width;
    int height;
};

class Animation
{
public:
    void addAnimationObject(AnimationObject object);
    void setSprite(Sprite *_sprite);
    void setAnimationInterval(int milisec);
    void play();
    void stop();
    void reset();
    void update(const int delta);

private:
    std::vector<AnimationObject> animation;
    int interval = 100;
    int time = 0;
    bool isPlaying = false;
    int currentObject = 0;
    Sprite *sprite = nullptr;
};

#endif // ANIMATION_H