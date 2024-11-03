#include"window.hpp"

Window::Window(int w, int h) : window(nullptr)
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

Window::~Window() {
    if(window) {
        SDL_DestroyWindow(window);
    }
    SDL_Quit();
}

SDL_Window* 
Window::getWindow() const {
    return window;
}

void 
Window::getWSize(int *w, int *h) {
    if(window) {
        SDL_GetWindowSize(window, w, h);
    }
}
