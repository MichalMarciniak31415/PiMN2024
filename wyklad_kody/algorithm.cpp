// przykłady jeszcze nie omawiane na wykładzie

#include<iostream>
#include<vector>
#include<algorithm>
#include<random>

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

int add2(int x) { return x + 2; }
int add(int x, int y) { return x + y; };

int main() {
  //ustawienie generatora liczb (pseudo)losowych
  std::random_device rd;                          
	std::mt19937 g(rd());
	std::uniform_int_distribution<> dist(1, 100);   


	std::vector<int>  vec{ 33,1,2,3,5,2,1,15,1,22 };

	std::vector<int>  vec2;

	for (int it = 0; it < 10; it++) {     //wypełnij vec2 liczbami losowymi
		vec2.push_back(dist(g));
	}

	cout << "Poczatkowy vector vec: ";
	print(vec);
	cout << "Poczatkowy vector vec2: ";
	print(vec2);
                  // transform z operacją unitarną (jednoargumentową)
                 //początek zakresu    koniec zakresu   miejsce docelowe   fukcja
	std::transform(      vec.begin(),      vec.end(),       vec.begin(),       add2  );     //zastosuj funkcję add2 do vectora vec
	cout << "vec + 2: ";
	print(vec);

	cout << "vec * vec: ";
                  // transform z operacją binarną (dwuargumentową)
                 //początek zakresu    koniec zakresu   miejsce drugiego zakresu     miejsce docelowe           fukcja
	std::transform(     vec.begin(),        vec.end(),            vec.begin(),           vec.begin(),      std::multiplies<>{});    //
	print(vec);

           //początek zakresu    koniec zakresu    funkcja porównawcza
	std::sort(   vec2.begin(),       vec2.end(),       std::greater<>{} );
	cout << "posortowany od max do min vec2: ";
	print(vec2);

	cout << "przetasowany vec pierwszych 5 elementów: ";
              //początek zakresu     koniec zakresu          generator liczb losowych
	std::shuffle(     vec.begin(),   std::next(vec.begin(), 5),           g             );
	print(vec);

	cout << "przesuniecie vec o 4 w lewo: ";
	std::rotate(vec.begin(), std::next(vec.begin(), 4), vec.end());
	print(vec);

	cout << "przesuniecie vec o 1 w prawo: ";
	std::rotate(vec.rbegin(), std::next(vec.rbegin(), 1), vec.rend());
	print(vec);

	cout << " \'wlasny sort\' vec: ";
            //sort z funkcją lambda
      //       capture clause      lista argumentów   (opcjonalnie) zwracany typ     ciało funkcji
    // lambda :      []               (int a, int b)            -> bool               {return a > b; }
    // capture clause - pozwala na wykorzystanie innych zmiennych z zakresu

	std::sort(vec.begin(), vec.end(), [](int a, int b) {return a > b; });
	print(vec);

	int q = 10;
  //dlaczego korzystamy z capture clause?
  // w poniższym przykładzie chcemy do vec dodać stałą wartość daną przez zmienną q
  // naiwne użycie q jako argumentu: std::transform(vec.begin(), vec.end(), vec.begin(), [](int a, int q) {return a + q; });
  // prowadzi do błędów: std::transform będzie oczekiwać, że funkcja będzie jednoargumentowa

  std::transform(vec.begin(), vec.end(), vec.begin(), [q](int a) {return a + q; });
	cout << " sqrt(vec) + q: ";
	print(vec);
                                                                    //tutaj można użyć funkcji add
	std::transform(vec.begin(), vec.end(), vec2.begin(), vec.begin(), [](int a, int b) {return a + b; });
	cout << " vec+ vec2 = : ";
	print(vec);


	return 0;
}

