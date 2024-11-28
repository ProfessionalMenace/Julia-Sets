#include<SDL2/SDL.h>
#include <stdio.h>
#include<complex>

class Display {
private:
    SDL_Renderer *mRenderer;
    float mRadius;
    int mIterMax;
    std::complex<float> mConstant;
    int mWidth, mHeight;
    float mXMin, mXMax;
    float mYMin, mYMax;
    float mXDelta, mYDelta;
    
    int calculate(float re, float im) {
        std::complex<float> z(re,im);
        int iter = 0;
        while(std::norm(z) < mRadius && iter < mIterMax) {
            z = z * z + mConstant;
            ++iter;
        }
        return iter;
    }

    void clear() {
        SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
        SDL_RenderClear(mRenderer);
    }

    void draw() {
        int i,j;
        float x, y;
        SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
        for(i = 0, x = mXMin; i < mWidth; ++i,  x+= mXDelta) {
            for(j = 0, y = mYMin; j < mHeight; ++j, y += mYDelta) {
                if(calculate(x, y) == mIterMax) {
                    SDL_RenderDrawPoint(mRenderer, i, j);
                }
            }
        }
        SDL_RenderPresent(mRenderer);
    }

public:
    Display(SDL_Renderer *renderer, int IterMax, float radius) : 
        mRenderer{renderer},
        mIterMax{IterMax},
        mRadius{radius}
    {}
    
    void set_bounds(float a, float b, float c, float d) {
        mXMin = a;
        mYMin = b;
        mXMax = c;
        mYMax = d;
    }

    void set_constant(float re, float im) {
        mConstant = std::complex<float>(re, im);
    }

    void print_constant() {
        printf("%+5f %+5f\n", this->mConstant.real(), this->mConstant.imag());
    }

    void update_size(int width, int height) {
        mWidth = width;
        mHeight = height;
        mXDelta = (mXMax - mXMin) / static_cast<float>(width);
        mYDelta = (mYMax - mYMin) / static_cast<float>(height);
    }

    void redraw() {
        clear();
        draw();
    }
};
    
