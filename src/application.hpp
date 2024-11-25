#include<SDL2/SDL.h>
#include<iostream>
#include"display.hpp"

class Application {
private:
    SDL_Window *window;
    SDL_Renderer *renderer;

    void window_init(int w, int h)
    {
        std::cout << "Initailizing window...\n";
        if(SDL_Init(SDL_INIT_VIDEO) == -1) {
            std::cerr << "Window initialization failed\n" << SDL_GetError();
            exit(EXIT_FAILURE);
        }

        window = SDL_CreateWindow("Fractal",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            w,
            h,
            SDL_WINDOW_RESIZABLE
            );

        if(!window) {
            std::cerr << "Failed to create window\n";
            exit(EXIT_FAILURE);
        }

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

        if(!renderer) {
            std::cerr << "Failed to create renderer\n";
            exit(EXIT_FAILURE);
        }

    }

    void window_deinit() {
        std::cout << "Destroying window...\n";
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    void get_window_size(int *w, int *h) {
        SDL_GetWindowSize(window, w, h);
    }

    void main_loop() {
        std::cout << "Starting main loop...\n";
        bool is_running = true;
        bool is_drawn = false;
        bool is_pressed = false;
        bool is_resized = true;
        bool mouse_input = false;
        SDL_Event event;
        int width, height;
        int mouse_x, mouse_y;

        Display display(4.0, 25);
        display.set_bounds(-1.2, -1.2, 1.2, 1.2);

        while (is_running) {
            if(is_resized) {
                SDL_GetWindowSize(window, &width, &height);
                display.update_size(width, height);
                is_resized = false;
            }

            if(mouse_input) {
                SDL_GetMouseState(&mouse_x, &mouse_y);
                display.set_constant(
                    static_cast<float>(2 * mouse_x) / width - 1.0, 
                    static_cast<float>(2 * mouse_y) / height - 1.0
                );
                mouse_input = false;
            }

            if(!is_drawn) {
                display.redraw(renderer, width, height);
                is_drawn = true;
            }

            while(SDL_PollEvent(&event)) {
                switch (event.type) {
                    case SDL_QUIT:
                    is_running = false;
                    break;

                    case SDL_MOUSEBUTTONDOWN:
                    is_pressed = true;
                    mouse_input = true;
                    break;

                    case SDL_MOUSEBUTTONUP:
                    is_pressed = false;
                    std::cout << mouse_x << " " << mouse_y << std::endl;
                    break;

                    case SDL_MOUSEMOTION:
                    if(is_pressed) {
                        is_drawn = false;
                        mouse_input = true;
                    }
                    break;

                    case SDL_WINDOWEVENT:
                    switch (event.window.event) {
                        case SDL_WINDOWEVENT_RESIZED:
                        case SDL_WINDOWEVENT_MAXIMIZED:
                        case SDL_WINDOWEVENT_RESTORED:
                            is_resized = true;
                            is_drawn = false;
                            break;
                    }
                }
            }
        }
    }

public:
    void run() {
        window_init(600, 600);
        main_loop();
        window_deinit();
    }
};
