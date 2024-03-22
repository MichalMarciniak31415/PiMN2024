#include<iostream>
#include<vector>
#include<algorithm>


using std::cout, std::cin, std::endl;
//szablony do wypisywania elementów pojemnika
template <typename T>
void print(const T& vec) {
	for (const auto& elem : vec) {
		cout << elem << " ";
	}
	cout << endl;
	cout << endl;
}
template <typename T>
void print2d(const T& vec) {
	for (const auto& row : vec) {
		for (const auto& elem : row)
			cout << elem << " ";
		cout << endl;
	}
	cout << endl;
	cout << endl;
}


void example1() {

	cout << "\n\n example 1\n \n";
	// podstawy - przykłady definiowania vectora
	std::size_t n = 10;
	std::vector<int> vec; //inicjalizacja pustego vectora
	std::vector<int> vec1{ 1, 2, 3, 4, 5, 6, 7, 8, 9 }; //inicjalizacja przez podanie wartości 
	std::vector<int> vec2(n); //inicjalizacja 10-elementowego vectora zer 
	std::vector<int> vec3(n, 5); //inicjalizacja 10-elementowego vectora piątek 
	std::vector<int> vec4 = vec1; //utworzenie vectora przez skopiowanie wartości z vec1

	print(vec);
	print(vec1);
	print(vec2);
	print(vec3);
	print(vec4);


	int element1 = vec1[4];    // nie sparwdza poprawności adresu
	int element2 = vec1.at(4); // sparwdza poprawność adresu

	cout << element1 << " " << element2 << endl;


	//int element3 = vec1[41];    // nie sparwdza poprawności adresu -> jeśli poza zakres to segmentation fault - błąd nie wyjdzie w kompilacji
	//int element4 = vec1.at(41); // sparwdza poprawność adresu
	//cout << element3 << " " << element4 << endl;

	// przykładowy komunikat po metodzie at()
	//terminate called after throwing an instance of 'std::out_of_range'
	//	what() : vector::_M_range_check : __n(which is 41) >= this->size() (which is 9)
	//	Aborted




	int element5 = *(&vec1[0] + 3);    // nie sparwdza poprawności adresu -> jeśli poza zakres to segmentation fault - błąd nie wyjdzie w kompilacji
	int element6 = *(vec1.data() + 3); // sparwdza poprawność adresu
	cout << element5 << " " << element6 << endl;

	int element7 = vec1.front();    // nie sparwdza poprawności adresu -> jeśli poza zakres to segmentation fault - błąd nie wyjdzie w kompilacji
	int element8 = vec1.back(); // sparwdza poprawność adresu
	cout << element7 << " " << element8 << endl;


}


void example2() {

	cout << "\n\n example 2 \n\n";
	//iterowanie po vectorze

	std::vector<int> vec{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	for (std::size_t i = 0; i < vec.size(); i++) {   //ok
		cout << vec.at(i) << " ";
	}
	cout << endl;

	//tutaj auto = std::vector<int>::iterator
	for (auto it = vec.begin(); it != vec.end(); it++) {
		cout << *it << " ";
	}
	cout << endl;

	//tutaj auto = std::vector<int>::reverse_iterator
	// przejście po elementach od tyłu
	for (auto it = vec.rbegin(); it != vec.rend(); it++) {
		cout << *it << " ";
	}
	cout << endl;

	//najlepsza wersja; 
	for (auto& elem : vec) {
		cout << elem << " ";
	}

	cout << endl;
}

void example3() {

	cout << "\n\n example 3 \n\n";
	// vector - metody  

	std::vector<int> vec;   // utwórz pusty vector
	std::vector<int> vec1{ -5,-4,-3,-2,-1 };

	for (int i = 0; i < 10; i++) {
		vec.push_back(i);  //dodaj element
	}

	print(vec);

	vec.pop_back();  //usuń ostatni element
	print(vec);

	vec.resize(20);  // zmień rozmiar elementu; jeśli potrzeba będzie realokacja pamięci
	print(vec);

}


void example4() {

	cout << "\n\n example 4 \n\n";
	// sposób działania vectora - dynamiczne alokowanie pamięci
	// rezerwowanie więcej miejsca w pamięci (capacity) niż rozmiar tablicy (size)
	// kopiowanie tablicy w nowe miejsce w pamięci po wyczerpaniu poprzedniego miejsca

	std::vector<int> vec1;   // utwórz pusty vector

	for (int i = 0; i < 100; i++) {
		vec1.push_back(i);  //dodaj element
		cout << "size is: " << vec1.size() << " allocated memory is " << vec1.capacity();  //porównaj size vs capacity
		cout << "    adres 1-ego elementu: " << &vec1[0] << "\n";    //wyświetl adres pierwszego elementu
		//adres się zmienia wraz z dodawaniem elementów		
	}

}

void example5() {


	cout << "\n\n example 5 \n\n";
	// vector - metody 2 

	std::vector<int> vec{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	std::vector<int> vec1{ -5,-4,-3,-2,-1 };
	print(vec);

	vec.insert(vec.begin() + 5, 42);  //wstaw 42 przed szósty element

	print(vec);

	vec.insert(vec.begin(), vec1.begin(), vec1.end()); //wstaw cały vector vec1 na początek vec

	print(vec);
}

void example6() {
	cout << "\n\n example6 \n\n";
	//elementy vectora mogą być dowolnego typu; w szczególności możemy 
	// mieć vector vectorów - może to być macierz ale niekoniecznie - długość elementów nie musi być identyczna

	std::vector<std::vector<int>> vec1{ {1,2,3},{4,5,6},{7,8,9} }; //inicjalizacja przez podanie wartości 


	int n = 5, m = 7;
	std::vector<std::vector<int>> vec2(n, std::vector<int>(m, 42));  //inicjalizacja n x m macierzy wypełnionej liczbą 42

	print2d(vec2);  //wypisz macierz

}


int main() {


	example1();
	example2();
	example3();
	example4();
	example5();
	example6();

	return 0;
}

