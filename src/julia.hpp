#include<complex>

class JuliaSet {
private:
    std::complex<float> constant;
    float radius;
    unsigned int iterMax;
public:
    JuliaSet(float re, float im)
        : constant(re,im) {}
    JuliaSet(float re, float im, float radius)
        : constant(re,im), radius{radius} {}
    JuliaSet(float re, float im, float radius, unsigned int max)
        : constant(re,im), radius{radius}, iterMax{max} {}

    inline std::complex<float>
    function(std::complex<float> z) {
        return z * z + constant;
    }

    void setConstant(std::complex<float> c) {
        constant = c;
    }

    int iterate(std::complex<float> z) {
        int iter = 0;
        while(std::norm(z) < radius && iter < iterMax) {
            z = function(z);
            ++iter;
        }
        return iter;
    }

    bool isMember(std::complex<float> z) {
        int iter = iterate(z);
        return iter == iterMax;
    }
};
