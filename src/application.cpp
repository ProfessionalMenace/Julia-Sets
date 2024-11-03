#include"application.hpp"
Application::Application(int w, int h, float radius, int it) : display(w, h), set(radius, it) {}
Application::Application(int w, int h) : display(w, h), set(4.0, 25) {}

void 
Application::run(JuliaSet set) {
    bool quit = false;
    bool drawn = false;
    bool pressed = false;
    SDL_Event event;
    // rendering
    display.newBounds(-1.2, -1.2, 1.2, 1.2);
    
    int mouseX, mouseY;
    int w, h;
    float re, im;
    while (!quit) {
        if(!drawn) {
            display.clear();
            display.updateSize();
            display.draw(&set);
            drawn = true;
        }

        while(SDL_PollEvent(&event)) {
            

            switch (event.type)
            {
                case SDL_QUIT:
                    quit = true;
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    pressed = true;
                    drawn = false;
                    break;

                case SDL_MOUSEBUTTONUP:
                    pressed = false;
                    set.print();
                    break;

                case SDL_MOUSEMOTION:
                    if(pressed) {
                        SDL_GetMouseState(&mouseX, &mouseY);
                        display.getSize(&w, &h);
                        re = static_cast<float>(2*mouseX)/w - 1.0;
                        im = static_cast<float>(2*mouseY)/h - 1.0;
                        set.setConstant(re, im);
                        drawn = false;
                    }
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
}
