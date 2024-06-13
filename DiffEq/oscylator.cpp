#include "oscylator.h"
//#include <ppl.h>
#include <cmath>
#include <random>
#include <iostream>
#include <vector>

Oscillator::Oscillator(float ti, float tf) {
	t0 = ti;
	tk = tf;
	t.push_back(t0);
	v.push_back(0);
	x.push_back(1);

	for (float i = t0; i <= tk; i += h) {
		t.push_back(i);
	}
	
}

float Oscillator::velocity(float x0, float v0, float t0) {

	return -a * v0 - b * x0;
}

float Oscillator::pos(float x0, float v0, float t0) {

	return v0;
}

void Oscillator::RK4() {
	x.resize(1);
	v.resize(1);
	
	float k1,k2,k3,k4,l1,l2,l3,l4;
//	int iter{ 0 };

	for (int iter = 0; iter < t.size()-1;iter++) {
		k1 = velocity(x[iter]           , v[iter]           , t[iter]);
		l1 =      pos(x[iter]           , v[iter]           , t[iter]);

		k2 = velocity(x[iter] + h/2 * l1, v[iter] + h/2 * k1, t[iter] + h/2);
		l2 =      pos(x[iter] + h/2 * l1, v[iter] + h/2 * k1, t[iter] + h/2);
		
		k3 = velocity(x[iter] + h/2 * l2, v[iter] + h/2 * k2, t[iter] + h/2);
		l3 =      pos(x[iter] + h/2 * l2, v[iter] + h/2 * k2, t[iter] + h/2);
		
		k4 = velocity(x[iter] + h   * l3, v[iter] + h   * k3, t[iter] + h);
		l4 =      pos(x[iter] + h   * l3, v[iter] + h   * k3 ,t[iter] + h);

		
		v.push_back(v[iter] + h / 6 * (k1 + 2 * k2 + 2 * k3 + k4));
		x.push_back(x[iter] + h / 6 * (l1 + 2 * l2 + 2 * l3 + l4));
		
		//std::cout << iter << std::endl;
	}
	
}

void Oscillator::set_window() {
	
	ImGui::Begin("Oscillator");
	ImGui::SliderFloat("a",&a,-5.f,10.f);
	ImGui::SliderFloat("b", &b, -5.f, 10.f);
	ImGui::SliderFloat("t0", &t0, -5.f, 5.f);
	ImGui::SliderFloat("tk", &tk, t0, 100.f);
	ImGui::SliderFloat("x0", &x[0], -5.f, 5.f);
	ImGui::SliderFloat("v0", &v[0], -5.f, 5.f);
	

	if (ImPlot::BeginPlot("plot", ImVec2(800, 800))) {
		ImPlot::SetNextLineStyle(line_color, line_width);
		ImPlot::PlotLine("RK4", t.data(), x.data(), x.size());
		
		ImPlot::EndPlot();
	}

	ImGui::End();
	
	RK4();
	t.resize(0);
	for (float i = t0; i <= tk+h; i += h) {
		t.push_back(i);
	}
}
