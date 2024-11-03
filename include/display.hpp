#include<SDL2/SDL.h>
#include<iostream>
#include"window.hpp"
#include"julia.hpp"

class Display : Window {
private:
    SDL_Renderer *renderer;
    int winX, winY;
    float xMin, xMax;
    float yMin, yMax;
    float xDelta, yDelta;

    void deltaXUpdate();
    void deltaYUpdate();
    void deltaUpdate();
    bool checkRenderer();
public:
    Display(int w, int h);
    void getSize(int *w, int *h);
    void updateSize();
    void newXBounds(float min, float max);
    void newYBounds(float min, float max);
    void newBounds(float xMin, float yMin, float xMax, float yMax);    
    void clear();
    void draw(JuliaSet *set);
};
