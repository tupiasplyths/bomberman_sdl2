#include <SDL2/SDL.h>
#include <vector>
#include "entities/Object.h"

class App;

class Scene 
{
    protected:
        App *app;
    private:
        std::vector<std::shared_ptr<Object>> objects;
    public:
        Scene(App *app);
        void addObject(std::shared_ptr<Object> object);
        void removeObject(std::shared_ptr<Object> object);
        void update(const int delta);
        void draw();
};