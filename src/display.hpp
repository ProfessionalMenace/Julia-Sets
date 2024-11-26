#include<SDL2/SDL.h>
#include <stdio.h>
#include<complex>

class Display {
private:
    float radius;
    int iterMax;
    std::complex<float> constant;
    int width, height;
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

    void draw(SDL_Renderer *renderer) {
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

    void print_constant() {
        printf("%+5f %+5f\n", this->constant.real(), this->constant.imag());
    }

    void update_size(int w, int h) {
        width = w;
        height = h;
        xDelta = (xMax - xMin) / static_cast<float>(w);
        yDelta = (yMax - yMin) / static_cast<float>(h);
    }

    void redraw(SDL_Renderer *renderer) {
        clear(renderer);
        draw(renderer);
    }
};
    
