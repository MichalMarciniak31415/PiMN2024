#include "integrations.h"
//#include <ppl.h>
#include <cmath>
#include <random>
#include <iostream>
#include <vector>
static std::random_device rd;
static std::mt19937 gen(rd());
static std::uniform_real_distribution<float> dist(-1.0, 1.0);


static std::vector<float> linspace(float start, float end, int point_num) {
   
    std::vector<float> x0(point_num);
    float scale = (end - start) / point_num;
    for (int i = 0; i < point_num; i++) {
        x0[i] = start + i * scale;
    }
    return x0;
}




integrations::integrations(float x_start, float x_end, int _size,float (*ptr)(float)) {
    size = _size;
    start = x_start;
    end = x_end;
    fptr = ptr;
    x = linspace(start, end, size);
    
    y.resize(size);
    ybins.resize(nbins);
    xbins.resize(nbins);
   
    for (int i = 0; i < size;i++) {
        y[i] = fptr(x[i]);
    }

    scale = (end - start) / nbins;
    xbins[0] = start +  scale/2;
    ybins[0] = fptr(xbins[0]);
    for (int i = 1; i < nbins; i++) {
        xbins[i] = xbins[i-1] +  scale;
        ybins[i] = fptr(xbins[i]);
    }
}

float integrations::rectangle() {
    rect = 0;
    for (const auto& elem : ybins) {
        rect += elem;
    }
    rect *= scale;
    return rect;
}

float integrations::trapez() {
    trap = 0;
    for (const auto& pos : xbins) {
        trap += scale / 2 * (fptr(pos - scale) + fptr(pos + scale));

    }


    //trap *= scale;
    return trap;
}


float integrations::simpson() {
    simp = 0;
    for (const auto& pos : xbins) {
        simp+= scale/6*(fptr(pos-scale)+4*fptr(pos) + fptr(pos + scale));
       
    }

    return simp;
}

void integrations::update() {
    ybins.resize(nbins);
    xbins.resize(nbins);

    scale = (end - start) / nbins;
    xbins[0] = start + scale / 2;
    ybins[0] = fptr(xbins[0]);
    for (int i = 1; i < nbins; i++) {
        xbins[i] = xbins[i - 1] + scale;
        ybins[i] = fptr(xbins[i]);
    }
}

void integrations::set_window() {
    
    ImGui::Begin("Calkowanie");
   
    
    ImGui::SliderInt("##Bins", &nbins, 1, 100);
    ImGui::Text("Area from rectangle rule: %.5f", rectangle());
    ImGui::SameLine();
    ImGui::Text("Area from trapez rule: %.5f", trapez());
    ImGui::SameLine();
    ImGui::Text("Area from simpson rule: %.5f", simpson());
   

    if (ImPlot::BeginPlot("ImPlot", ImVec2(1600, 800))) {

        ImPlot::SetupAxes("Position", "Value");
        ImPlot::SetNextLineStyle(ImVec4(1,1,1,1));
        ImPlot::PlotBars("rectangles", xbins.data(), ybins.data(), nbins, (end - start) / nbins);
        ImPlot::SetNextLineStyle(line_color, line_width);
        ImPlot::PlotLine("funkcja", x.data() /*x.data() = &x[0]*/, y.data(), x.size());

        ImPlot::EndPlot();
    }

   ImGui::End();
   
   update();

}

