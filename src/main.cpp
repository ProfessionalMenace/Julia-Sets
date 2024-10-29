#include<SDL2/SDL.h>
#include<cstdio>
#include"window.hpp"

int main(int argc, char* argv[]) {
    if(argc != 3) {
        return 1;
    }
    float re = std::atof(argv[1]);
    float im = std::atof(argv[2]);
    Window window(1024, 1024);
    window.run(re, im);
    
    return 0;
}
