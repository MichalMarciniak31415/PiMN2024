#include "functions.h"
//#include <ppl.h>
#include <cmath>
#include <random>
#include <iostream>
#include <vector>
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<float> dist(0.0, 1.0);




std::vector<float> linspace(float start, float end, int point_num) {
   
    
    std::vector<float> x(point_num);
    float scale = 1.0 / point_num;
    for (int i = 0; i < point_num; i++) {
        float temp = i * scale;
        x[i] = (temp - 1) * start + temp * end;
    }
    return x;
}


void parabole::update(){
    for (int i = 0; i < size; i++) {
        y[i] = a * x[i] * x[i] + b * x[i] + c;
    }
 }


parabole::parabole(float x_start, float x_end, int _size) {
        size = _size;

        x = linspace(x_start, x_end, size);
        y.resize(size);
        update();
       

    }

void parabole::set_window() {

        
        ImGui::Begin("Parabole");

        ImGui::PushItemWidth(ImGui::GetWindowWidth() * 0.25f);
        ImGui::SliderFloat("##a", &a, -10.f, 10.f, "a coeff: %.2f");
        ImGui::PushItemWidth(ImGui::GetWindowWidth() * 0.25f);
        ImGui::SliderFloat("##b", &b, -10.f, 10.f, "b coeff: %.2f");
        ImGui::PushItemWidth(ImGui::GetWindowWidth() * 0.25f);
        ImGui::SliderFloat("##c", &c, -10.f, 10.f, "c coeff: %.2f");


        if (ImPlot::BeginPlot("ImPlot test", ImVec2(1600, 800) ) ) {
        
            ImPlot::SetupAxes("Position", "Amplitide");
            ImPlot::SetNextLineStyle(line_color, line_width);
            ImPlot::PlotLine("parabole", x.data(), y.data(), size);
      
            ImPlot::EndPlot();
        }

        ImGui::ColorEdit4("Color", &(line_color.x));
        ImGui::SameLine();
        ImGui::PushItemWidth(ImGui::GetWindowWidth() * 0.1f);
        ImGui::SliderFloat("Linewidth", &line_width, 0, 60);
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();
        update();
    }
