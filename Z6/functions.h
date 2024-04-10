#pragma once

#include <vector>
#include "imgui.h"
#include "implot.h"

const float _PI_ = 3.141592653;
const float _SCALE_ = 1 / (2 * _PI_);

class parabole {
public:
    int size = 0;
    std::vector<float> x;
    std::vector<float> y;
    float star{}, end{};
    float a{1}, b{1}, c{1};
    float line_width = 4;

   

    ImVec4 line_color = { 0.1, .8, .9, 1 };


    parabole(float x_start, float x_end, int _size);
    void update();
    void set_window();
};
