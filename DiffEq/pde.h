#pragma once

#include <vector>
#include "imgui.h"
#include "implot.h"

class pde {

    
    std::vector<float> x;
    std::vector<std::vector<float>> u;
    std::vector<float> t;
    
    float xk{}, x0{}, y0{ 1 }, a{ 1 }, b{ 0 }, v0{};
    float h = 0.1f;
    float k = 0.01f;
    int cnt{ 0 }, tmax{ 10000 };
    float r = k / h;
    int size = 10000;
    float line_width = 4;
    float (*fptr)(float) = nullptr;
    ImVec4 line_color = { 0.1, .8, .9, 1 };

public:
    
    pde(float ,float,float (*f)(float));

    void set_window();
    void solve();


    
};

