#include "box.h"

Box::Box(float _a, float _b, float _c) {
    a = _a;
    b = _b;
    c = _c;
};

float Box::area() {
    return 2 * a * b + 2 * a * c + 2 * b * c;
}

float Box::volume() {
    return a * b * c;
}
