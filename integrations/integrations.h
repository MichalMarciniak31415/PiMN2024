#pragma once

#include <vector>
#include "imgui.h"
#include "implot.h"

class integrations{
public:
    int size = 0;
    int nbins = 10;
    float (*fptr)(float) = nullptr;
    std::vector<float> x;
    std::vector<float> y;

    std::vector<float> xbins;
    std::vector<float> ybins;
    
   
    
    float start{}, end{};
    float rect{ 0 }, trap{ 0 }, simp{ 0 };
    float scale;
    float line_width = 4;


  

    
    ImVec4 line_color = { 0.1, .8, .9, 1 };


    integrations(float x_start, float x_end, int _size,float (*ptr)(float));
    float rectangle();
    float simpson();
    float trapez();
    void update();
   
    void set_window();
};

