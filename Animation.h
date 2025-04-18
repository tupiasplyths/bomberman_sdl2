#pragma once
#include <vector>

class Sprite;

class AnimationObject
{
public:
    AnimationObject(int positionX, int positionY, int width, int height);
    const int positionX;
    const int positionY;
    const int width;
    const int height;
};

class Animation
{
public:
    Animation();
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
