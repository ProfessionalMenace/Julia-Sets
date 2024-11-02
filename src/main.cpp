#include<cstdio>
#include"application.hpp"

int main(int argc, char* argv[]) {
    int w = 500, h = 500;
    float re = 0.35, im = 0.35;
    JuliaSet set(4.0, 50);

    switch(argc) {
        case 5:
            w = std::stoi(argv[3]);
            h = std::stoi(argv[4]);
        case 3:
            re = std::stof(argv[1]);
            im = std::stof(argv[2]);
            set.setConstant(re, im);
            break;
        default:
            std::cerr << "Invalid number of nyarguments\n";
        }

    if(w < 1 || h < 1) {
        std::cerr << "Invalid arguments\n";
        return 1;
    }
    Application app(w, h);
    app.run(set);
    return 0;
}
