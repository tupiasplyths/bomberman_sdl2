// #include "entities/Sprite.cpp"

class AnimationObject {
    AnimationObject(int positionX, int positionY, int width, int height) {

    }

    const int positionX = 0;
    const int positionY = 0;
    const int width = 0;
    const int height = 0;
};

class Animation {
    public:
        Animation() {};
        void update() {};

    private: 
        std::vector<AnimationObject> animation;
        int interval  = 100;
        int time = 0;
        bool isPlaying = false; 
};
