
#include <iostream>

#include <cmath>


class Complex {

private:
    float re{}, im{};


public:

    Complex() :re{}, im{} {}


    Complex(float a, float b) : re{ a }, im{ b } {

    }

    void set_re(float x) {
        re = x;
    }


    void set_im(float x) {
        im = x;
    }


    void print()const {
        std::cout << re << " + " << im << "i" << std::endl;
    }

    float get_re() const {
        return re;
    }


    float get_im()const {
        return im;
    }


    float abs()const {
        return sqrtf(re * re + im * im);
    }


    Complex conjugate() {
        Complex z(re, -im);
        return z;
    }


    Complex& conjugate_me() {
        this->set_im(-im);
        return *this;
    }


    Complex operator+(Complex const& a) {
        Complex z(re + a.re, im + a.im);
        return z;
    }


    Complex operator-(Complex const& a) {
        Complex z(re - a.re, im - a.im);
        return z;
    }


    Complex operator*(Complex const& a) {
        Complex z(re * a.re - im * a.im, re * a.im + a.re * im);
        return z;
    }


    Complex operator/(Complex const& a) {
        Complex z((re * a.re + im * a.im) / (re * re + im * im), (re * a.im - a.re * im) / (re * re + im * im));
        return z;
    }


    bool operator<(Complex const& a)const {
        return abs() < a.abs();
    }


    bool operator>(Complex const& a)const {
        return abs() > a.abs();
    }


    friend std::ostream& operator<<(std::ostream& str, Complex const& complex) {
        str << complex.re << " + " << complex.im << "i";
        return str;
    }

};


int main() {
    Complex z(2, 4);
    Complex z1(-2, 3);

    z.print();
    z.conjugate_me();
    z.print();
    auto z2 = z + z1;
    z2.print();

    std::cout << z1.abs() << std::endl;

    if (z2 < z)std::cout << "done" << std::endl;

    std::cout << z1 << std::endl;

   

}
