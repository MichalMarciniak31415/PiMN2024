#include "interpolation.h"
//#include <ppl.h>
#include <cmath>
#include <random>
#include <iostream>
#include <vector>


static std::vector<float> linspace(float start, float end, int point_num) {

    //funkcja do rozpinania punktów na osi x

    std::vector<float> x0(point_num);
    float scale = (end - start) / point_num;
    
    for (int i = 0; i < point_num; i++) {
        x0[i] = start + i * scale;
    }
    
    return x0;
}


void Interpolation::generate() {
    //funkcja do generowania psize losowych punktów 

    //ustawienie generatora liczb losowych
    std::random_device rd;
    std::mt19937 gen(rd());
    //jednorodny rozk³ad z zakresu [start, end]
    std::uniform_real_distribution<float> dist(start, end);
    
    //psize bêdzie zmieniany przez suwak
    //wiêc dostosowujemy rozmiar vectorów do liczby punktów
    x_points.resize(psize);
    y_points.resize(psize);


    //losowanie psize punktów
    // losujemy wspó³rzêdne punktów
    for (int i = 0; i < psize; i++) {    
        x_points[i]= dist(gen) ;
        y_points[i]= dist(gen) ;
    }

 
}

Interpolation::Interpolation(int _psize,float x_start, float x_end, int _size) {
    size = _size;
    psize = _psize;
    start = x_start;
    end = x_end;

    // wylosuj punkty
    generate(); 
    
    //rozepnij przestrzeñ na osi x
    x = linspace(start, end, size);
    //dostosuj rozmiar vectora dla wartoœci funkcji do
    // rozmiaru vectora trzymaj¹cego argumenty funkcji 
    y.resize(size);
   
}



void Interpolation::neville() {
    //utwórz tablicê o rozmiarach psize x psize
    std::vector<std::vector<float>> nevilleP(psize, std::vector<float>(psize));


    //wype³nij diagonalê macierzy nevilleP
    for (int i = 0; i < psize; i++) {
        nevilleP[i][i] = y_points[i];
    }
    
    for (int k = 0; k < x.size(); k++) {  //iteracja po punktach z vectora x

        // odpowiednio napisana pêtla:
        // przechodzimy macierz po przek¹tnych
        // zaczynaj¹c od przek¹tnej ponad diagonal¹
        for(int j =1; j<x_points.size();j++){
            for (int i = 0; i < x_points.size()-j; i++) {
                // obliczamy p_i_{i+j}
                nevilleP[i][i+j] = ((x[k] - x_points[i]) * nevilleP[i + 1][i+j] - (x[k] - x_points[j+i]) * nevilleP[i][j - 1+i]) / (x_points[j+i] - x_points[i]);
               
            }
            
        }
        //wartoœæ funkcji w punkcie x[k] jest dana przez 
        // p_{0}{psize}
        y[k] = nevilleP[0][x_points.size() - 1];

    }
    
}


void Interpolation::lagrange() {
    float temp{ 1 }, lag{ 0 };
    //pêtla po wszystkich punktach w vectorze x
    for (int i = 0; i < x.size(); i++) { 
        lag = 0;
        //suma y_j * l_j
        for (int j = 0; j < x_points.size(); j++) {
            temp = 1;

            // iloczyn l_j
            for (int m = 0; m < x_points.size(); m++) {
                if (m != j) temp *= (x[i] - x_points[m]) / (x_points[j] - x_points[m]);
            }
            //dodaj y_j * l_j
            lag += temp * y_points[j];
    
        }
        // L(x[i])
        y[i] = lag;
       
    }


}



void Interpolation::set_window() {


    ImGui::Begin("Lagrage interpolation");
    //przycisk do wywo³ania metody lagrange()
    if (ImGui::Button("Lagrange!") && x_points.size() == psize)lagrange();
    //przycisk do wywo³ania metody neville()
    if (ImGui::Button("Neville!")&&x_points.size() ==psize)neville();
    //przycisk do wyczyszczenia vectora y
    if (ImGui::Button("clear!")) {
        y.resize(0);
        y.resize(size);
    }
    //wygeneruj nowe punkty do interpolacji
    if (ImGui::Button("reGenerate points")){

        generate();
    }
    //suwak do zmiany psize - liczby punktów do interpolacji
    ImGui::SliderInt("number of points", &psize, 2, 20);

    if (ImPlot::BeginPlot("ImPlot test", ImVec2(1600, 800))) {
        //ustaw nazwy osi
        ImPlot::SetupAxes("x", "y");
        //ustaw styl lini - kolor dany przez line_color, gruboœæ lini przez line_width
        ImPlot::SetNextLineStyle(line_color, line_width);
        //wyœwietl interpolowan¹ funkcjê f(x) = y
        ImPlot::PlotLine("interpolacja", x.data() /*x.data() = &x[0]*/, y.data(), x.size());
        //wyœwietl wylosowane punkty do interpolacji
        ImPlot::PlotScatter("points", x_points.data(), y_points.data(), x_points.size());
        ImPlot::EndPlot();
    }

   ImGui::End();

   
}

