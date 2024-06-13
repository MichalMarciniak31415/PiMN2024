#pragma once

#include <vector>
#include<complex>
#include<string>
#include "imgui.h"
#include "implot.h"

class Fourier{
        int N;
        float dx;
        bool is_DFT =false;
        std::vector<float> x;       
        std::vector<float> fx;      
        std::vector<float> freq;
        std::vector<std::complex<float>> Xk; 
        std::vector<float> spectrum; 

        //ImVec4 color_points={1, 0, 0, 1};   //kolor punktów 
        ImVec4 color_line={0, 1, 0, 1};     //kolor krzywej

    public:
        Fourier(std::string);
        void DFT();
        void set_window();
        
};