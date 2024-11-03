#include<SDL2/SDL.h>

class Window {
private:
    SDL_Window *window;
public:
    Window(int w, int h); 
    ~Window();
    SDL_Window* getWindow();
    void getWSize(int *w, int *h);
};
