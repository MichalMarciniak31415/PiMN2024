#include "pde.h"
//#include <ppl.h>
#include <cmath>
#include <random>
#include <iostream>
#include <vector>

pde::pde(float ti, float tf, float (*f)(float)) {
	x0 = ti;
	xk = tf;
	fptr = f;
	
	
	std::vector<float> temp;
	for (float i = x0; i <= xk; i += h) {
		x.push_back(i);
		temp.push_back(fptr(i) ); 
	}
	u.push_back(temp);
}



void pde::solve() {

	std::vector<float> temp;
	for (int itr = 0; itr < tmax; itr++) {
		temp.resize(0);
		temp.push_back(u[itr][0]);
		for (int i = 1; i < x.size() - 1; i++) {
			
			temp.push_back((1 - 2 * r * a) * u[itr][i] + r * a * u[itr][i+1] + r * a * u[itr][i - 1] );
		}
		
		temp.push_back(u[itr].back());
		
		u.push_back(temp);
	}
	
}


void pde::set_window() {
	
	ImGui::Begin("Heat eq");
	
	ImGui::SliderInt("time step", &cnt, 0, tmax - 1);
	if (ImPlot::BeginPlot("plot", ImVec2(800, 800))) {
		ImPlot::SetNextLineStyle(line_color, line_width);
		ImPlot::PlotLine("sol", x.data(), u.at(cnt).data(), x.size());
		
		ImPlot::EndPlot();
	}

	ImGui::End();
	
	
}
