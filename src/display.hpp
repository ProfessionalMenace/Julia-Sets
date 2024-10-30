#include<SDL2/SDL.h>
#include"julia.hpp"

class Display{
private:
    int winX, winY;
    float xMin, xMax;
    float yMin, yMax;
    float xDelta, yDelta;

    void deltaXUpdate() {
        this->xDelta = (xMax - xMin)/static_cast<float>(winX);
    }

    void deltaYUpdate() {
        this->yDelta = (yMax - yMin)/static_cast<float>(winY);
    }

    void deltaUpdate() {
        deltaXUpdate();
        deltaYUpdate();
    }
public:
    void winResize(int w, int h)
    {
        winX = w;
        winY = h;
        deltaUpdate();
    }
    void newXBounds(float min, float max) {
        xMin = min;
        xMax = max;
        deltaXUpdate();
    }

    void newYBounds(float min, float max) {
        yMin = min;
        yMax = max;
        deltaYUpdate();
    }

    void newBounds(float xMin, float yMin, float xMax, float yMax) {
        newXBounds(xMin, xMax);
        newYBounds(yMin, yMax);
    }

    void draw(SDL_Renderer *renderer, JuliaSet *set) {
        std::complex<float> z;
        int i,j;
        float x, y;
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        for(i = 0, x = xMin; i < winX; ++i, x+=xDelta) {
            for(j = 0, y = yMin; j < winY; ++j, y+=yDelta) {
                z = std::complex<float>(x, y);
                if(set->isMember(z)) {
                    SDL_RenderDrawPoint(renderer, i, j);
                }
            }
        }
        SDL_RenderPresent(renderer);
    }
};
