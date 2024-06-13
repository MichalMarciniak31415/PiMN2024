#pragma once

#include <vector>
#include "imgui.h"
#include "implot.h"

class montecarlo {
public:
    int size = 1000;
    int series = 1;
    int cnt{ 0 };
    float (*fptr)(float,float) = nullptr;
    std::vector<float> x;
    std::vector<float> y;

    std::vector<float> xbins;
    std::vector<float> ybins;

    std::vector<float> randy;
    std::vector<float> randx;

    std::vector<float> randxC;
    std::vector<float> randyC;
    std::vector<float> pi;

    float integral{ 0 };
    float start{}, end{};
    float rect{ 0 }, trap{ 0 }, simp{ 0 };
    float scale;
    float line_width = 4;
    int dim{ 2 };
    float nres{ 0 };
    std::vector<float> rectPointsX{ -1, 1,1,-1,-1 };
    std::vector<float> rectPointsY{ -1,-1,1,1, -1 };

    std::vector<float> circlePointsX;
    std::vector<float> circlePointsY;

    std::vector<float> nsphereX;
    std::vector<float> nsphereY;


    ImVec4 line_color = { 0.1, .8, .9, 1 };


    montecarlo( float (*ptr)(float,float));

    void serie();
    void reset(bool);
    void generate(bool);
    float approx();
    void nsphere();
    void integrate();
    void set_window();
};

