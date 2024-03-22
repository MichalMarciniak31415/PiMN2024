#include<iostream>
#include<list>
#include <vector>
using std::cout, std::cin,std::endl;

template <typename T>
void print(const T& vec) {
	for (const auto& elem : vec) {
		cout << elem << " ";
	}
	cout << endl;
}


int main() {

	std::size_t size = 10;

	int count = 5, value = 3;
	{
	std::vector<int> vec{ 3,1,4,15,9 };

	std::list<int> lista{ 1,2,3,4,5,6,7 };

	std::list<int> lista1;
	std::list<int> lista2(size);
	std::list<int> lista3(size, value);

	print(lista);
	print(lista1);
	print(lista2);
	print(lista3);

	cout << endl;

	lista.assign(count, value);
	lista1.assign(vec.begin(), vec.end());
	lista2.assign({ 4,5,6,7,7,8 });

	print(lista);
	print(lista1);
	print(lista2);
}
	{
	std::list<int> lista;
	for (int i = 0; i < 10; i++) {
		if (i % 2 == 0)lista.push_back(i);
		else lista.push_front(i);
	}

	print(lista);

	lista.pop_back();
	lista.pop_front();
	print(lista);
	}
	{
		std::list<int> lista1{ 3, 1, 5, -9, 2, 7 };
		std::list<int> lista2{ 1, 2, 2, 2, 3, 4, 5, 6 };
		cout << " lista1: ";
		print(lista1);
		cout << " lista2: ";
		print(lista2);
		lista1.sort();       // posortuj pierwszą listę
		//sort z algorithm nie działa - brak losowego dostępu do elementów
		// i brak swap()
		cout << " posortowana lista1: ";
		print(lista1);

		lista2.reverse();	//odwraca listę
		cout << " odwrocona lista2: "; print(lista2);

		auto itr = lista1.begin();    //iterator itr wskazuje na pierwszy element
		std::advance(itr, 3);		  //przesuń itr o trzy elementy

		lista2.splice(lista2.begin(), lista1, itr);   //do lista2 dodaj na początku
		//element  czwarty element z lista1
		cout << " przepisany element z lista1 do lista2: ";

		print(lista2);
		cout << " lista1 jest o element mniejsza: ";
		print(lista1);

		lista2.sort();						// posortuj lista2
		lista1.merge(lista2);				// połacz obie listy;
		//UWAGA! DZIAŁA TYLKO NA POSORTOWANYCH LISTACH
		cout << " zlaczone listy z powtorzeniami: ";

		print(lista1);
		lista1.unique();			//usuń powtarzające się elementy

		cout << " zlaczone listy bez powtorzeniami: ";

		print(lista1);
	}
}
