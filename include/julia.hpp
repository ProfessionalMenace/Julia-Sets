#include<complex>
#include<iostream>

class JuliaSet {
private:
    std::complex<float> constant;
    float radius;
    int iterMax;
public:
    JuliaSet(float radius, int max)
        : constant(0.0, 0.0), radius{radius}, iterMax{max} {}

    inline std::complex<float>
    function(std::complex<float> z) {
        return z * z + constant;
    }

    void setConstant(std::complex<float> c) {
        constant = c;
    }

    void setConstant(float re, float im) {
        constant = std::complex<float>(re, im);
    }

    int iterate(std::complex<float> z) {
        int iter = 0;
        while(std::norm(z) < radius && iter < iterMax) {
            z = function(z);
            ++iter;
        }
        return iter;
    }

    void print() {
        std::cout << constant << "\n";
    }

    bool isMember(std::complex<float> z) {
        int iter = iterate(z);
        return iter == iterMax;
    }
};
