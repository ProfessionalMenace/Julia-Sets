#include<SDL2/SDL.h>
#include"window.hpp"

int main(void) {
    Window window(1024, 1024);
    window.run();
    
    return 0;
}
