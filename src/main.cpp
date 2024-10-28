#include<SDL2/SDL.h>
#include<complex>

constexpr int scale = 1;
constexpr int winHX = 500;
constexpr int winHY = 500;
constexpr int winX = 2*winHX;
constexpr int winY = 2*winHY;

template<typename T>
inline std::complex<T>
juliaFn(std::complex<T> z, std::complex<T> c) {
    return z * z + c;
}

template<typename T>
int juliaIter(
        std::complex<T> z,
        std::complex<T> c,
        unsigned int iterMax
) {
    unsigned int iter = 0;
    while(std::norm(z) < 4.0 && iter < iterMax) {
        z = juliaFn<T>(z, c);
        ++iter;
    }
    return iter;
}

template<typename T>
void juliaSet(
        SDL_Renderer *renderer,
        const T minX,
        const T maxX,
        const T minY,
        const T maxY,
        const int winHX,
        const int winHY,
        const int iterMax
) {
    std::complex<T> c(0.35, 0.35);
    int iter = 0;
    for(T x = minX ; x < maxX; x+=0.001) {
        for(T y = minY; y < maxY;  y+=0.001) {
            std::complex<T> z(x,y);
            iter = juliaIter<T>(z, c, iterMax);
            if(iter != iterMax) {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); 
                SDL_RenderDrawPointF(renderer, winHX + x*2*winHX, winHY + y*2*winHY);
            }
        }
    }
}

int main(void) {
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(winX * scale, winY * scale, 0, &window, &renderer);
    if(!window || !renderer){ return 1; }

    SDL_RenderSetScale(renderer, scale, scale);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    
    juliaSet<double>(renderer, -2.0, 2.0, -2.0, 2.0, winHX, winHY, 64);

    SDL_RenderPresent(renderer);
    
    bool isRunning = true;
    while(isRunning) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                isRunning = false;
            }
        }
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    return 0;
}
