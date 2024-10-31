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

    void deltaXUpdate() {
        if(winX != 0) {
            this->xDelta = (xMax - xMin)/static_cast<float>(winX);
        }
    }

    void deltaYUpdate() {
        if(winY != 0) {
            this->yDelta = (yMax - yMin)/static_cast<float>(winY);
        }
    }

    void deltaUpdate() {
        deltaXUpdate();
        deltaYUpdate();
    }

    bool checkRenderer() {
        if(!renderer) {
            std::cerr << "Renderer not found\n";
        }
        return renderer != nullptr;
    }

public:
    Display(int w, int h) :
        Window(w, h),
        renderer{nullptr},
        winX{w},
        winY{h},
        xMin{-1.0},
        yMin{-1.0},
        xMax{1.0},
        yMax{1.0},
        xDelta{0},
        yDelta{0}
    {
        deltaUpdate();
        SDL_Window *win = getWindow();
        if(win) {
            renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_PRESENTVSYNC);
        }
        else {
            std::cerr << "Initialized display without window\n";
        }
    }

    void getSize(int *w, int *h) {
        getWSize(w, h);
    }

    void updateSize()
    {
        getWSize(&winX, &winY);
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
    
    void clear() {
        if(checkRenderer()) {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);
        }
    }

    void draw(JuliaSet *set) {
        if(!checkRenderer()) {
            return;
        }

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
