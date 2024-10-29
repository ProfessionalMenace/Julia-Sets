#include <SDL2/SDL.h>
#include <iostream>
#include<complex>

inline std::complex<float>
juliaFn(std::complex<float> z, std::complex<float> c) {
    return z * z + c;
}

bool juliaIter(
        std::complex<float> z,
        std::complex<float> c,
        float radius,
        unsigned int iterMax
) {
    unsigned int iter = 0;
    while(std::norm(z) < radius && iter < iterMax) {
        z = juliaFn(z, c);
        ++iter;
    }
    return iter == iterMax;
}

class Window {
private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    std::pair<int, int> winSize;
    int scale;
public:
    Window(int w, int h)
        :winSize(w,h),
        window(nullptr),
        renderer(nullptr)
    {
        SDL_Init(SDL_INIT_VIDEO);
        SDL_CreateWindowAndRenderer(w, h, 0, &window, &renderer);
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

    void forEachF() {
        float xMin = -2.0;
        float yMin = -2.0;
        float xMax = 2.0;
        float yMax = 2.0;
        float xDelta = (abs(xMax - xMin))/static_cast<float>(winSize.first);
        float yDelta = (abs(yMax - yMin))/static_cast<float>(winSize.second);
        std::complex<float> z;
        std::complex<float> c(0.35, 0.35);
        std::cout << xDelta << " " << yDelta << "\n";

        float x, y;
        int i,j;
        for(i = 0, x = xMin; i < winSize.first; ++i, x+=xDelta) {
            std:: cout << x << ' ' << y << '\n';
            for(j = 0, y = yMin; j < winSize.second; ++j, y+=yDelta) {
                z = std::complex<float>(x, y);
                if(juliaIter(z, c, 4.0, 25)) {
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                    SDL_RenderDrawPoint(renderer, i, j); 
                }
            }
        }
        SDL_RenderPresent(renderer);
        std::cout << "Drawn\n";
    }

    void run() {
        bool quit = false;
        bool drawn = false;
        SDL_Event event;

        while (!quit) {
            if(!drawn) {
                clear();
                forEachF();
                drawn = true;
            }

            SDL_WaitEvent(&event);

            switch (event.type)
            {
                case SDL_QUIT:
                    quit = true;
                    break;
            }
        }
    }
};
