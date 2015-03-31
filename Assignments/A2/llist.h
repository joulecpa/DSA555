/*
	Author: Hong Zhan Huang
	Linked list data structure for use with HashTable part of Assignment 2
*/

#include <cstring>
#include <iostream>
using namespace std;

//Nodes for HashTable
template <class TYPE>
struct Node{

	char* key;
	int value;
	Node<TYPE> *next;

	Node(const char* key_, TYPE value) {
		key = new char[30];
		if (key_)
			strcpy(this->key, key_);
		this->value = value;
		this->next = nullptr;
	}
};

//Singly linked list structure
template <class TYPE>
class HashList{
	
	Node<TYPE>* front;
	Node<TYPE>* current;
	Node<TYPE>* last;
	
	public:
		HashList();
		void insert(const char* key, TYPE value);
		void remove();
		void goStart();
		int goNext();
		Node<TYPE>* getFront();
		Node<TYPE>* getCurr();
		Node<TYPE>* getNext();
		char* getKey();
		TYPE getVal();
		void setVal(TYPE value);
		void print();
		void clear();
		~HashList();
};

//Constructor
template <class TYPE>
HashList<TYPE>::HashList(){
	front = nullptr;
	last = nullptr;
	current = nullptr;
}

//Inserts into the back of the linked list
template <class TYPE>
void HashList<TYPE>::insert(const char* key, TYPE value){
	
	if (front){
		Node<TYPE>* n = new Node<TYPE>(key, value);
		last->next = n;
		last = n;
	}
	else{
		Node<TYPE>* n = new Node<TYPE>(key, value);
		front = n;
		current = front;
		last = front;
	}
}

//Removes the current node and resets current to front
template <class TYPE>
void HashList<TYPE>::remove(){
	
	if (current == front){
		front = front->next;
		delete current;
		current = front;
	}
	else{
	
		Node<TYPE>* n = front;
		while (n->next != current){
			n = n->next;
		}
	
		if (current == last){
			last->next = n;
			last = n;
			delete current;
		}
		else{
			n->next = current->next;
			delete current;
		}
		
	}
	
	current = front;
}

//Sets current node to the front node
template <class TYPE>
void HashList<TYPE>::goStart(){
	current = front;
}

//Moves the current node to the next node if it exists
template <class TYPE>
int HashList<TYPE>::goNext(){
	
	if (current != last){
		current = current->next;
		return 1;
	}
	else{
		current = nullptr;
		return 0;
	}
		
}

//Returns the front node
template <class TYPE>
Node<TYPE>* HashList<TYPE>::getFront(){
	return front;
}

//Returns the current node
template <class TYPE>
Node<TYPE>* HashList<TYPE>::getCurr(){
	return current;
}

//Returns the next node
template <class TYPE>
Node<TYPE>* HashList<TYPE>::getNext(){
	if (current != last)
		return current->next;
	else
		return nullptr;
}

//Returns the key of the current node
template <class TYPE>
char* HashList<TYPE>::getKey(){
	return current->key;
}

//Returns the value of the current node
template <class TYPE>
TYPE HashList<TYPE>::getVal(){
	return current->value;
}

//Sets the value of the current node
template <class TYPE>
void HashList<TYPE>::setVal(TYPE value){
	current->value = value;
}

//Prints the entire link list, used for checking results
template <class TYPE>
void HashList<TYPE>::print(){
	
	while(current){
		cout << "Key: " << current->key << " Value: " << current->value << endl;
		current = current->next;
		if (current == last){
			cout << "Key: " << current->key << " Value: " << current->value << endl;
			break;
		}
	}
	
	current = front;
}

//Deallocates the list
template <class TYPE>
void HashList<TYPE>::clear(){
	goStart();
	while(current){
		Node<TYPE>* node = current->next;
		delete current;
		current = node;
	}
}

//Destructor
template <class TYPE>
HashList<TYPE>::~HashList(){
	clear();
}