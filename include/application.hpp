#include<SDL2/SDL.h>
#include"display.hpp"

class Application {
    private:
    Display display;
    JuliaSet set;

    public:
    Application(int w, int h, float radius, int it);
    Application(int w, int h);
    void updateSet(JuliaSet *set);
    void run(JuliaSet set);
};
