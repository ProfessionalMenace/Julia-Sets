#include<SDL2/SDL.h>
#include<iostream>
#include<complex>

class Display {
private:
    float radius;
    int iterMax;
    std::complex<float> constant;
    float xMin, xMax;
    float yMin, yMax;
    float xDelta, yDelta;
    
    int calculate(float re, float im) {
        std::complex<float> z(re,im);
        int iter = 0;
        while(std::norm(z) < radius && iter < iterMax) {
            z = z * z + constant;
            ++iter;
        }
        return iter;
    }

    void clear(SDL_Renderer *renderer) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
    }

    void draw(SDL_Renderer *renderer, int width, int height) {
        if(!renderer || xDelta == 0.0 || yDelta == 0.0) {
            return;
        }

        int i,j;
        float x, y;
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        for(i = 0, x = xMin; i < width; ++i, x+=xDelta) {
            for(j = 0, y = yMin; j < height; ++j, y+=yDelta) {
                if(calculate(x, y) == iterMax) {
                    SDL_RenderDrawPoint(renderer, i, j);
                }
            }
        }
        SDL_RenderPresent(renderer);
    }

public:
    Display(float r, int iterations) : radius{r}, iterMax{iterations} {}
    Display(float re, float im, float r, int iterations) :
        constant{re, im}, radius{r}, iterMax{iterations} {}

    void set_bounds(float a, float b, float c, float d) {
        xMin = a;
        yMin = b;
        xMax = c;
        yMax = d;
    }

    void set_constant(float re, float im) {
        constant = std::complex<float>(re, im);
    }

    void update_size(int width, int height) {
        xDelta = (xMax - xMin) / static_cast<float>(width);
        yDelta = (yMax - yMin) / static_cast<float>(height);
    }

    void redraw(SDL_Renderer *renderer, int width, int height) {
        clear(renderer);
        draw(renderer, width, height);
    }
};
    
