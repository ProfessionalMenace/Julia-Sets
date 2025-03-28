#include <GLFW/glfw3.h>
#include <algorithm>
#include <cmath>
#include <complex>
#include <execution>
#include <vector>
#include <span>
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
    std::vector<std::complex<double>> point_buffer;

    inline int calculate(std::complex<double> z, std::complex<double> c) {
        int iter = 0;
        while (std::norm(z) < Radius && iter < IterMax) {
            z = z * z + c;
            ++iter;
        }
        return iter;
    }

    inline void color(int iter) {
        float value = static_cast<float>(iter) / IterMax;
        glColor3f(0.0, 0.0, powf(value, 0.2f));
    }

public:
    Display(size_t max_width, size_t max_height) : Radius(), IterMax(), Min(-1.2, -1.2), Max(1.2, 1.2), Constant(), point_buffer(max_width * max_height) {
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

        for (int y = 0; y < height ; ++y) {
            for (int x = 0; x < width; ++x) {
                point_buffer[y * width + x] = Min + std::complex<double>(x * xdelta, y * ydelta);
            }
        }

        Timer timer("Draw");
        glBegin(GL_POINTS);
        // mdspan soon... 
        std::span<std::complex<double>> span_buffer(point_buffer); 
        for (int i = 0; i < height; ++i) {
            auto span_row = span_buffer.subspan(i*width, width);
            std::for_each(std::execution::par_unseq, span_row.begin(), span_row.end(), [this](std::complex<double> &z) {
                color(calculate(z, Constant));
                glVertex2d(z.real(), z.imag());
            });
        }
        glEnd();
    }
};
