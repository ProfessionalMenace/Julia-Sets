#include<SDL2/SDL.h>

class Window {
private:
    SDL_Window *window;
public:
    Window(int w, int h) : window(nullptr)
    {
        SDL_Init(SDL_INIT_VIDEO);
        window = SDL_CreateWindow("Julia Sets",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            w,
            h,
            SDL_WINDOW_RESIZABLE
            );
    }
    
    ~Window() {
        if(window) {
            SDL_DestroyWindow(window);
        }
        SDL_Quit();
    }

    SDL_Window* getWindow() const {
        return window;
    }

    void getWSize(int *w, int *h) {
        if(window) {
            SDL_GetWindowSize(window, w, h);
        }
    }
};
