#include<iostream>
#include<algorithm>
#include<map>

using std::cout, std::cin, std::endl;

int main(){
	std::map<std::string, unsigned> miasta;

	miasta["Wroclaw"] = 670'000;
	miasta["Warszawa"] = 1'800'000;
	miasta["Poznan"] = 540'000;
	miasta["Krakow"] = 800'000;
	miasta["Lodz"] = 650'000;
	miasta["Gdansk"] = 480'000;

	cout << "Populacja Warszawy to " << miasta["Warszawa"] << "\n";
	cout << "Populacja Wroclawia to " << miasta["Wroclaw"] << "\n";
	cout << "Populacja Poznania to " << miasta["Poznan"] << "\n";
	cout << "Populacja Kowar to " << miasta["Kowary"] << "\n";

	cout << endl;
	for (auto it = miasta.begin(); it != miasta.end(); it++) {
		cout << it->first << " ";
		cout << it->second << "\n";
	}
	cout << endl;
  
  for (auto it = miasta.begin(); it != miasta.end(); it++) {
  	cout << (*it).first << " ";           // to co wyżej ale najpierw bierzemy obiekt (a nie wskaźnik), a potem wywołujemy metodę/zmienną
  	cout << (*it).second << "\n";
  }
cout << endl;
	for (auto& elem : miasta) {
		cout << elem.first << " ";
		cout << elem.second << "\n";
	}

	cout << endl;
	//best way - structure bindings C++17
	for (auto& [key, value] : miasta) {
		cout << key << " ";
		cout << value << "\n";
	}
	//miasta.at("Ankara") = 5600000;
	cout << endl;
	miasta.insert({ {"Londyn", 8800000} ,{"Berlin", 3700000} });
	for (auto& [key, value] : miasta) {
		cout << key << " ";
		cout << value << "\n";
	}
	std::map<std::string, unsigned> inne_miasta{ {"Madryt",3200000},{"Lizbona",500000} };
	miasta.insert(inne_miasta.begin(), inne_miasta.end());
	cout << endl;
	for (auto& [key, value] : miasta) {
		cout << key << " ";
		cout << value << "\n";
	}
	if (miasta.count("Szczecin") == 0)
		miasta["Szczecin"] = 390000;
	else {
		cout << miasta["Szczecin"] << endl;
	}
	if (miasta.count("Szczecin") == 0)
		miasta["Szczecin"] = 390000;
	else {
		cout << miasta["Szczecin"] << endl;
	}

}
