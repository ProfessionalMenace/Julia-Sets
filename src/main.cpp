#include<cstdio>
#include"application.hpp"

int main(int argc, char* argv[]) {
    float re = 0, im = 0, radius = 4.0;
    int iter = 25;
    switch(argc) {
        case 5:
            radius = std::atof(argv[4]);
        case 4:
            iter = std::atoi(argv[3]);
        case 3:
            im = std::atof(argv[2]);
        case 2:
            re = std::atof(argv[1]);
    }
    Application app;
    app.run(re, im, iter, radius);
    return 0;
}
