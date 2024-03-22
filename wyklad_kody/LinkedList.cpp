#include<iostream>
#include <algorithm>


using std::cout, std::cin, std::endl;


class Node {

public:
	int value;
	Node* forward = nullptr;
	Node* backward = nullptr;

	Node() :value{0} {}
	Node(int val) :value{ val } {}



};

class ListIterator {
	
public:
	using iterator_category = std::bidirectional_iterator_tag;
	using value_type = int;
	using difference_type = std::ptrdiff_t;
	using pointer = Node*;
	using reference = int&; 

	ListIterator(pointer ptr) :myPtr{ ptr } {}

	ListIterator& operator++() {

		myPtr = myPtr->forward;
		return *this;
	}

	ListIterator& operator--() {

		myPtr = myPtr->backward;
		return *this;
	}

	reference operator*() {
		return myPtr->value;
	}

	bool operator!=(ListIterator it) {
		return myPtr != it.myPtr;
	}

	bool operator==(ListIterator it) {
		return myPtr == it.myPtr;
	}

	private:
		pointer myPtr;
};

class LinkedList {
	Node* head = nullptr;
	Node* tail = nullptr;
	using Iterator = ListIterator;
public:
	LinkedList(){}

	~LinkedList() {
		while (head->forward != nullptr) {
			Node* ptr = head;
			head = head->forward;
			delete ptr;
		}
		delete head;
	}

	void push_back(int val) {
		Node* newNode = new Node(val);

		if (head == nullptr) {
			head = newNode;
			tail = newNode;
			return;
		}

		newNode->backward = tail;

		tail->forward = newNode;

		tail = tail->forward;

	}
	
	void push_front(int val) {
		Node* newNode = new Node(val);

		if (head == nullptr) {
			head = newNode;
			tail = newNode;
			return;
		}

		newNode->forward = head;

		head->backward = newNode;

		head = head->backward;

	}

	void print() {

		Node* ptr = head;
		while (ptr != nullptr) {
			cout << ptr->value << endl;
			ptr = ptr->forward;
		}
	}

	Iterator begin() {
		return Iterator(head);
	}


	Iterator end() {
		return ++Iterator(tail);
	}

};




int main() {


	LinkedList lst;
	lst.push_back(5);
	lst.push_back(4);
	lst.push_front(-5);
	lst.push_front(-4);
	lst.print();

	cout << "print 1" << endl;
	for (auto& elem : lst) {
		cout << elem << " ";
	}
	cout << endl;

	auto ptr = std::find(lst.begin(), lst.end(), -5);

	cout << *ptr << endl;

	*ptr = 15;

	cout << "print 2" << endl;
	for (auto& elem : lst) {
		cout << elem << " ";
	}
	cout << endl;
	return 0;
}
