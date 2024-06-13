  
#include <iostream>
#include<vector>
#include<cmath>
#include<fstream>
#include<sstream>
#include <iomanip>
#include<string>
#include "fourier.h"
#include<complex>
//using std::cout,std::endl,std::cin,std::vector,std::fstream,std::istringstream,std::string, std::complex;
const std::complex<float> I(0,1);
const float PI = 3.14159265359;

Fourier::Fourier(std::string dir){
    std::fstream file;
 
    std::string line;
    file.open(dir);
    if(!file.is_open()){
        std::cout<<"file could not open";
        return;
    }
    float _a{},_b{};
    while(getline(file, line)){
        std::istringstream row { line};
        row>>_a>>_b;
        x.push_back(_a);
        fx.push_back(_b);
    }
    file.close();
    N = x.size();
    dx = x.at(1)-x.at(0);
}
void Fourier::DFT(){
    
    std::complex<float> arg(0,0),val(0,0);
    Xk.resize(0);

    for(int k=0;k<N/2;k++){
        for(int i=0;i<N;i++){
           arg = std::complex<float>(0, 2* PI * k * i / N);
           val+= std::complex<float>(fx.at(i), 0) * exp(arg);
        }
        val;///=sqrt(N);
        Xk.push_back(val);

        freq.push_back(k*2*PI/N/dx);
        spectrum.push_back(norm(val));

        val=(0,0);
    }
 
   is_DFT =true;

}
void Fourier::set_window(){
        ImGui::Begin( "fourier solver" );
        if(ImGui::Button("DFT"))DFT();

        if (ImPlot::BeginPlot("solution", ImVec2(1200, 800) ) ) {
            
            ImPlot::SetupAxes("x", "f(x)");

            ImPlot::SetNextLineStyle(color_line);
            ImPlot::PlotLine("function", &(x.at(0)) , &(fx.at(0)), x.size());
            
            ImPlot::EndPlot();
        }
   
        ImGui::ColorEdit4("Color line", &(color_line.x) );

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();

        if(is_DFT){
            ImGui::Begin( "spectrum" );
            if (ImPlot::BeginPlot("spectrum of f(x)", ImVec2(1200, 800) ) ) {
                
                ImPlot::SetupAxes("freq", "spectrum");
                ImPlot::SetupAxisScale(ImAxis_Y1, ImPlotScale_Log10);
                ImPlot::SetNextLineStyle(color_line);
                ImPlot::PlotLine("function", &(freq.at(0)) , &(spectrum.at(0)), freq.size());
                
                ImPlot::EndPlot();
            }
    
            ImGui::ColorEdit4("Color line", &(color_line.x) );

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }
}
