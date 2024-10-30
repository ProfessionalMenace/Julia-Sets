#include<SDL2/SDL.h>
#include"display.hpp"

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

    void run(float re, float im) {
        bool quit = false;
        bool drawn = false;
        SDL_Event event;
        // rendering
        JuliaSet set(re, im, 4.0, 25); 
        Display display;
        display.newBounds(-1.2, -1.2, 1.2, 1.2);
        
        int w, h;
        while (!quit) {
            if(!drawn) {
                clear();
                SDL_GetWindowSize(window, &w, &h);
                display.winResize(w, h);
                display.draw(renderer, &set); 
                drawn = true;
            }

            SDL_WaitEvent(&event);

            switch (event.type)
            {
                case SDL_QUIT:
                    quit = true;
                    break;

                case SDL_WINDOWEVENT:
                    switch (event.window.event) {
                        case SDL_WINDOWEVENT_RESIZED:
                        case SDL_WINDOWEVENT_MAXIMIZED:
                        case SDL_WINDOWEVENT_RESTORED:
                            drawn = false;
                            break;
                    }
                break;
            }
        }
    }
};
