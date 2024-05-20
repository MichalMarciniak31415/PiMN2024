#pragma once

#include <vector>
#include "imgui.h"
#include "implot.h"


////////////////////////////
/////Przykładowe zastosowanie w funkcji main
///////////////////////////

//Interpolation inter(5, -5.f, 5.f, 10000);
//while (!glfwWindowShouldClose(context.window))
//{
//    context.new_frame();
//    inter.set_window();
//    context.render_frame();
//    }


class Interpolation {

    int size = 0;       //liczba punktów na osi x
    int psize{};        //liczba punktów do interpolacji

    std::vector<float> x;   //oś x
    std::vector<float> y;   //oś y


    std::vector<float> x_points;  //współrzędne x punktów użytych do interpolacji  
    std::vector<float> y_points;  //współrzędne y punktów użytych do interpolacji


    float start{}, end{};   //początek i koniec przedziału

    float line_width = 3;   //grubość lini
    ImVec4 line_color = { 0, 1, 0, 1 };     // kolor lini
public:
    //konstruktor
    Interpolation(int , float , float , int );
    //metoda do generowania punktów do interpolacji
    void generate();
    //metoda interpolacji Lagrange'a
    void lagrange();
    //metoda interpolacji Neville'a
    void neville();
    //wyświetlanie
    void set_window();
};
