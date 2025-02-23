#include <GLFW/glfw3.h>
#include <complex>
#include <cmath>

class Display {
    double Radius;
    int IterMax;
    std::complex<double> Min, Max, Constant;

    int calculate(std::complex<double> z) {
        int iter = 0;
        while(std::norm(z) < Radius && iter < IterMax) {
            z = z * z + Constant;
            ++iter;
        }
        return iter;
    }

    void color(int iter) {
        if (iter == IterMax) {
            glColor3f(1.0, 1.0, 1.0);
        } else {
            float value = static_cast<float>(iter)/IterMax;
            glColor3f(0.0, 0.0, powf(value, 0.2f));
        }
    }

public:
    Display() : Radius(4.0), IterMax(25), Min(-1.2, -1.2), Max(1.2, 1.2), Constant(0.35, 0.35) {
        glMatrixMode(GL_PROJECTION);
    }

    void set_constant(std::complex<double> constant) {
        Constant = constant;
    }

    void set_radius(double radius) {
        Radius = radius;
    }

    void set_iteration(int iter) {
        IterMax = iter;
    }

    void bounds(double xmin, double xmax, double ymin, double ymax) {
        Min = { xmin, ymin };
        Max = { xmax, ymax };
    }

    void draw(int width, int height) {
        glViewport(0, 0, width, height);
        glLoadIdentity();
        glOrtho(Min.real(), Max.real(), Min.imag(), Max.imag(), -1.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        glBegin(GL_POINTS);

        double xdelta = (Max.real() - Min.real()) / static_cast<double>(width);
        double ydelta = (Max.imag() - Min.imag()) / static_cast<double>(height);

        for(int i = 0; i < width; ++i) {
            for(int j = 0; j < height; ++j) {
                auto z = Min + std::complex<double>(i*xdelta, j*ydelta);
                auto iter = calculate(z);
                color(iter);
                glVertex2d(z.real(), z.imag());
            }
        }
        glEnd();
    }
};

