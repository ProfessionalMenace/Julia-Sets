#include <GLFW/glfw3.h>
#include <algorithm>
#include <cmath>
#include <complex>
#include <execution>
#include <vector>
#include <chrono>
#include <print>
#include <string_view> 

struct Timer {
    std::string_view message_;
    std::chrono::time_point<std::chrono::system_clock> start_;
    Timer(std::string_view message) 
        : message_(message), start_(std::chrono::high_resolution_clock::now()) {} 
    ~Timer() {
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start_);
        println("Duration of {}: {}", message_, duration);
        start_ = end;
    }
};

class Display {
    double Radius;
    int IterMax;
    std::complex<double> Min, Max, Constant;

    inline int calculate(std::complex<double> z) {
        int iter = 0;
        while (std::norm(z) < Radius && iter < IterMax) {
            z = z * z + Constant;
            ++iter;
        }
        return iter;
    }

    inline void color(int iter) {
        float value = static_cast<float>(iter) / IterMax;
        glColor3f(0.0, 0.0, powf(value, 0.2f));
    }

public:
    Display() : Radius(4.0), IterMax(25), Min(-1.2, -1.2), Max(1.2, 1.2), Constant(0.0, 0.0) {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(Min.real(), Max.real(), Min.imag(), Max.imag(), -1.0, 1.0);
    }

    void set_constant(std::complex<double> constant) { Constant = constant; }

    void set_radius(double radius) { Radius = radius; }

    void set_iteration(int iter) { IterMax = iter; }

    void bounds(double xmin, double xmax, double ymin, double ymax) {
        Min = {xmin, ymin};
        Max = {xmax, ymax};
        glLoadIdentity();
        glOrtho(Min.real(), Max.real(), Min.imag(), Max.imag(), -1.0, 1.0);
    }

    void draw(int width, int height) {
        glViewport(0, 0, width, height);

        double xdelta = (Max.real() - Min.real()) / static_cast<double>(width);
        double ydelta = (Max.imag() - Min.imag()) / static_cast<double>(height);

        std::vector<std::complex<double>> vec(width * height);
        for (int i = 0; i < width; ++i) {
            for (int j = 0; j < height; ++j) {
                vec[i * height + j] = Min + std::complex<double>(i * xdelta, j * ydelta);
            }
        }

        Timer timer("Draw");
        glBegin(GL_POINTS);
        std::for_each(std::execution::par_unseq, vec.begin(), vec.end(), [this](std::complex<double> &z) {
            color(calculate(z));
            glVertex2d(z.real(), z.imag());
        });
        glEnd();
    }
};
