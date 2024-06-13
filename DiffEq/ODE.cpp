#include "ODE.h"
//#include <ppl.h>
#include <cmath>

#include <iostream>
#include <vector>

// ODE solver
//exact solution is for the equation: x'[t] =x + std::exp(t) + t * x

ODE::ODE(float(*f)(float, float), float t0, float tk, float y0, float h0) {
	fptr = f;
	
	x.push_back(y0);
	x1.push_back(y0);
	x2.push_back(y0);
	h = h0;
	for (float i = t0; i <= tk; i+=h) {
		t.push_back(i);
	}

}

void ODE::euler() {
	x.resize(1);
	x2.resize(1);
	for (int i = 0; i < t.size()-1; i++) {
		
		x.push_back( x[i] + fptr(x[i],t[i]) * h);
		
		//exact solution to the equation: x'[t] =x + std::exp(t) + t * x;
		x2.push_back(0.5f*std::expf(-3./2.+t[i]+ t[i]* t[i]/2) * ( 4-std::expf(3./2.)*sqrtf(2.f*3.14159f)*std::erff(sqrtf(2)/2.f)+ std::expf(3.f / 2.f) * sqrtf(2.f * 3.14159f) * std::erff(t[i]*sqrtf(2) / 2))); //exact
	}

	
}
void ODE::RK2() {
	
	x1.resize(1);
	for (int i = 0; i < t.size() - 1; i++) {

		x1.push_back(x1[i] + (fptr(x1[i]+ h * fptr(x1[i], t[i]), t[i+1]) + fptr(x1[i], t[i])) * h / 2);
	}

}

float ODE::diff(float x0, float t0) {

	return (fptr(x0, t0 + h) - fptr(x0, t0)) / h;
}

void ODE::set_window() {
	
	ImGui::Begin("solver");
	
	if (ImPlot::BeginPlot("plot", ImVec2(800, 800))) {
		
		ImPlot::SetupAxisScale(ImAxis_Y1, ImPlotScale_Log10);
		
		
		ImPlot::SetNextLineStyle(ImVec4(1, 0, 0, 1), 4);
		ImPlot::PlotLine("euler", t.data(), x.data(), x.size());
		
		ImPlot::SetNextLineStyle(ImVec4(0, 1, 0, 1), 4);
		ImPlot::PlotLine("RK2", t.data(), x1.data(), x1.size());
		
		ImPlot::SetNextLineStyle(ImVec4(0, 0, 1, 1), 4);
		ImPlot::PlotLine("exact", t.data(), x2.data(), x2.size());
		
		ImPlot::EndPlot();
	}

	ImGui::End();


	euler();
	RK2();
}
