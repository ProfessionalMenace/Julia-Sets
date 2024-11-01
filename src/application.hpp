#include<SDL2/SDL.h>
#include"display.hpp"

class Application {
    private:
    Display display;
    
    public:
    Application(int w, int h) : display(w, h) {}

    void run(float re, float im) {
        bool quit = false;
        bool drawn = false;
        SDL_Event event;
        // rendering
        JuliaSet set(re , im, 4.0, 50); 
        display.newBounds(-1.2, -1.2, 1.2, 1.2);
        
        int w, h;
        int x, y;
        while (!quit) {
            if(!drawn) {
                display.clear();
                display.updateSize();
                display.draw(&set);
                drawn = true;
            }

            SDL_WaitEvent(&event);

            switch (event.type)
            {
                case SDL_QUIT:
                    quit = true;
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    SDL_GetMouseState(&x, &y);
                    display.getSize(&w, &h);
                    re = (float)(2*x)/(float)w - 1.0;
                    im = (float)(2*y)/(float)h - 1.0;
                    set.setConstant(re, im);
                    std::cout << re << " + " << im << "i\n";
                    drawn = false;
                    break;

                case SDL_WINDOWEVENT:
                    switch (event.window.event) {
                        case SDL_WINDOWEVENT_RESIZED:
                        case SDL_WINDOWEVENT_MAXIMIZED:
                        case SDL_WINDOWEVENT_RESTORED:
                            drawn = false;
                            break;
                    }
            }
        }
    }
};
