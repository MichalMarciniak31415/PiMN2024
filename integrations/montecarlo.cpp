#include "montecarlo.h"
//#include <ppl.h>
#include <cmath>
#include <random>
#include <iostream>
#include <vector>
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<float> dist(-1.0, 1.0);


static std::vector<float> linspace(float start, float end, int point_num) {
   
    std::vector<float> x0(point_num);
    float scale = (end - start) / point_num;
    for (int i = 0; i < point_num; i++) {
        x0[i] = start + i * scale;
    }
    return x0;
}




montecarlo::montecarlo(float (*ptr)(float,float)) {
    
    fptr = ptr;
    
    for (int i = 0; i < 360; i++) {
        circlePointsX.push_back(cos(2*3.1415/360*i));
        circlePointsY.push_back(sin(2 * 3.1415 / 360 * i));
    }

    circlePointsX.push_back(cos(2 * 3.1415 / 360 * 0));
    circlePointsY.push_back(sin(2 * 3.1415 / 360 * 0));
    
    
}

bool check(float a,float b) {
    return a * a + b * b <= 1 ? true : false;

}

void montecarlo::nsphere() {
   
    float result{};
    for (int j = 0; j < size; j++) {
        nsphereX.resize(0);
        nsphereY.resize(0);

         for (int i = 0; i < dim; i++) {
            nsphereX.push_back(dist(gen));
         }

        float r{0};
        for (int i = 0; i < nsphereX.size(); i++) {
            r += nsphereX[i] * nsphereX[i];
        }

        if (r < 1)result++;
    
    }
    std::cout << result << std::endl;
    nres= result / size * pow(2,dim);
}



void montecarlo::generate(bool a) {
    float temp, temp1;
    
    for (int i = 0; i<size; i++) {
        temp = dist(gen);
        temp1 = dist(gen);
        if (check(temp, temp1)) {
            cnt++;
            randyC.push_back(temp);
            randxC.push_back(temp1);
        }
        else {
            randy.push_back(temp);
            randx.push_back(temp1);
        
        }
        
    }

    pi.push_back(4. * cnt / (randx.size() + randxC.size()));

}


void montecarlo::serie() {
    
    for (int i = 0; i < series; i++) {
        reset(1);
        generate(0);
        //std::cout << pi[i] << std::endl;
    }

}

float montecarlo::approx() {
    float sum{ 0 };
    for (auto& elem : pi) {
        sum += elem;
    }
    return sum / pi.size();
}
void montecarlo::reset(bool ap=0) {
    if(ap == 0)pi.resize(0);
    randx.resize(0);
    randy.resize(0);
    randxC.resize(0);
    randyC.resize(0);
    cnt = 0;
}
void montecarlo::integrate() {
    float temp, temp1, sum{};
    int cnt1{ 0 };
    reset();
    for (int i = 0; i < size; i++) {
        temp = dist(gen);
        temp1 = dist(gen);
        if (check(temp, temp1)) {
            cnt1++;
            sum += fptr(temp, temp1);
            cnt++;
            randyC.push_back(temp);
            randxC.push_back(temp1);
        }
        else {
            randy.push_back(temp);
            randx.push_back(temp1);

        }
        

    }

    integral = 4. * cnt / (randx.size() + randxC.size())* sum / cnt1;
}

void montecarlo::set_window() {

    ImGui::Begin("Monte Carlo");

    if (ImGui::Button("generate"))generate(0);
    ImGui::SameLine();
    if (ImGui::Button("reset"))reset();
    if (ImGui::Button("integrate")) { integrate(); }
    ImGui::SameLine();
    ImGui::Text(" integration of funcition f over disc gives: %f", integral);
    ImGui::SliderInt("number of shots", &size, 100, 100000);
    //ImGui::SameLine();
    ImGui::SliderInt("number of series", &series, 1, 1000);
    ImGui::SameLine();
    if (ImGui::Button("seria"))serie();
    if (ImGui::Button("nsphere")) nsphere();
    ImGui::SliderInt("dim", &dim, 2, 9);
    ImGui::Text("Volume of %d sphere is %f", dim, nres);
    if (ImPlot::BeginPlot("ImPlot", ImVec2(800, 800))) {

        
        ImPlot::SetupAxes("Position", "Value");
        ImPlot::SetNextLineStyle(ImVec4(0, 0, 1, 1), 6);
        ImPlot::PlotLine("kwadrat", rectPointsX.data() /*x.data() = &x[0]*/, rectPointsY.data(), rectPointsX.size());
        ImPlot::SetNextLineStyle(ImVec4(1, 0, 0, 1),6);
        ImPlot::PlotLine("circle", circlePointsX.data() /*x.data() = &x[0]*/, circlePointsY.data(), circlePointsX.size());

        ImPlot::PlotScatter("miss", randx.data() /*x.data() = &x[0]*/, randy.data(), randx.size());
        ImPlot::PlotScatter("hits", randxC.data() /*x.data() = &x[0]*/, randyC.data(), randxC.size());
        ImPlot::EndPlot();
    }

    ImGui::End();
   


    ImGui::Begin("calculating pi");

  
    ImGui::Text(" pi is : %f", approx());
  
    if (ImPlot::BeginPlot("ImPlot", ImVec2(800, 800))) {


        ImPlot::SetupAxes("# of series", "Value");
        ImPlot::SetNextLineStyle(ImVec4(0, 0, 1, 1), 6);
        ImPlot::PlotLine("pi", pi.data() /*x.data() = &x[0]*/, pi.size());
        ImPlot::EndPlot();
    }

    ImGui::End();
}
