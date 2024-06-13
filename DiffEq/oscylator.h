#pragma once

#include <vector>
#include "imgui.h"
#include "implot.h"

class Oscillator {

    
    std::vector<float> x;
    std::vector<float> v;
    std::vector<float> t;
    
    float tk{}, t0{}, y0{ 1.f }, a{ 1.f }, b{ 1.f }, v0{};
    float h = 0.1f;
    int size = 10000;
    float line_width = 4.f;

    ImVec4 line_color = { 0.1f, .8f, .9f, 1.f };

public:
    
    Oscillator(float ,float);


    float velocity(float, float, float);
    float pos(float, float, float);
    void set_window();
    void RK4();



    
};

