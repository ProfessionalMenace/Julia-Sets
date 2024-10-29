#include <SDL2/SDL.h>
#include "julia.hpp"

class Window {
private:
    SDL_Window *window;
    SDL_Renderer *renderer;
public:
    Window(int w, int h)
        :window(nullptr),
        renderer(nullptr)
    {
        SDL_Init(SDL_INIT_VIDEO);
        SDL_CreateWindowAndRenderer(w, h, SDL_WINDOW_RESIZABLE, &window, &renderer);
        if(!window || !renderer){ exit(1); }
    }
    
    ~Window() {
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(renderer);
        SDL_Quit();
    }

    void clear() {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
    }

    void juliaDraw(float re, float im, float xMin, float xMax, float yMin, float yMax) {
        int winX;
        int winY;
        SDL_GetWindowSize(window, &winX, &winY);
        float xDelta = (abs(xMax - xMin))/static_cast<float>(winX);
        float yDelta = (abs(yMax - yMin))/static_cast<float>(winY);
        JuliaSet set(re, im, 4.0, 25);
        std::complex<float> z;

        float x, y;
        int i,j;
        for(i = 0, x = xMin; i < winX; ++i, x+=xDelta) {
            for(j = 0, y = yMin; j < winY; ++j, y+=yDelta) {
                z = std::complex<float>(x, y);
                if(set.isMember(z)) {
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                    SDL_RenderDrawPoint(renderer, i, j); 
                }
            }
        }
        SDL_RenderPresent(renderer);
    }

    void run(float re, float im) {
        bool quit = false;
        bool drawn = false;
        SDL_Event event;

        while (!quit) {
            if(!drawn) {
                clear();
                juliaDraw(re, im, -1.2, 1.2, -1.2, 1.2);
                drawn = true;
            }

            SDL_WaitEvent(&event);

            switch (event.type)
            {
                case SDL_QUIT:
                    quit = true;
                    break;

                case SDL_WINDOWEVENT:
                    if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
                        drawn = false;
                    }
                    break;
            }
        }
    }
};
