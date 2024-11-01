#include<cstdio>
#include"application.hpp"

int main(int argc, char* argv[]) {
    float re, im;
    Application app(1000, 1000);
    switch(argc) {
        case 1:
            app.run(0.35, 0.35);
            break;
        case 2:
            re = std::stof(argv[1]);
            app.run(re, re);
            break;
        case 3:
            re = std::stof(argv[1]);
            im = std::stof(argv[2]);
            app.run(re, im);
            break;
    }
    return 0;
}
