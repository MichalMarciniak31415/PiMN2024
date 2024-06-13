#pragma once

#include <vector>
#include "imgui.h"
#include "implot.h"

class ODE {
public:
    
    std::vector<float> x;
    std::vector<float> x1;
    std::vector<float> x2;
    std::vector<float> t;
    float(*fptr)(float, float);
    float x0{};
    float h = 0.5f;
  

    ODE(float(*  )(float, float), float, float,float,float);
    float diff(float, float);
    void euler();

    void RK2();





    void set_window();




    float line_width = 4;

    ImVec4 line_color = { 0.1f, .8f, .9f, 1.f };

};
