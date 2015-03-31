/*
	Author: Hong Zhan Huang
	DSA555 Assignment 2
	This file contains implementation for  three types of tables.
	1. Simple Table 2. Hash Table 3. Tree Table
*/

#include "llist.h"
#include <cstring>
#include <functional>
#include <iostream>

using namespace std;

template <class TYPE>
class Table{
public:
	Table(){}
	Table(const Table& other){}
	virtual bool update(const char* key, const TYPE& value)=0;
	virtual bool remove(const char* key)=0;
	virtual bool find(const char* key, TYPE& value)=0;
	virtual int size() const=0;
	virtual bool isFull() const = 0;
	virtual bool isEmpty() const = 0;
	virtual const Table& operator=(const Table<TYPE>& other){return *this;}
	virtual ~Table(){}

};

//Generic record struct
template <class TYPE>
struct Entry{

  char* key;
  TYPE value;

  Entry<TYPE>(const char* key_ = nullptr, const TYPE& value_ = 0){
		
		key = new char[30];
		if (key_)
			strcpy(key, key_);
    value = value_;
  }
};

//**********************************************************Start SimpleTable

template <class TYPE>
class SimpleTable:public Table<TYPE>{

int max;
int count;
Entry<TYPE>* sTable;

int binarySearch(const char* key);

public:

  SimpleTable(int maxExpected = 30);
	SimpleTable(const SimpleTable& other);
	virtual const SimpleTable& operator=(const SimpleTable& other);
	virtual bool update(const char* key, const TYPE& value);
	virtual bool remove(const char* key);
	virtual bool find(const char* key, TYPE& value);
	virtual int size() const;
	virtual bool isFull() const ;
	virtual bool isEmpty() const;
	virtual ~SimpleTable();

};

//One arg constructor that sets the max size of the SimpleTable
template <class TYPE>
SimpleTable<TYPE>::SimpleTable(int maxExpected) : Table<TYPE>(){

  max = maxExpected;
  count = 0;
  sTable = new Entry<TYPE>[max];
}

//Copy constructor
template <class TYPE>
SimpleTable<TYPE>::SimpleTable(const SimpleTable<TYPE>& other){
	//sTable = nullptr; //temp fix
  *this = other;
}

//Assignment operator
template <class TYPE>
const SimpleTable<TYPE>& SimpleTable<TYPE>::operator=(const SimpleTable<TYPE>& other){

  if (this != &other){

    if (sTable != nullptr){
			for (int i = 0; i << count; i++){
				delete [] sTable[i].key;
			}
			sTable = nullptr;
		}
    max = other.max;
    count = other.count;
    sTable = new Entry<TYPE>[max];
    
    for (int i = 0; i < count; i++){
      if (other.sTable[i].key != nullptr)
				sTable[i] = Entry<TYPE>(other.sTable[i].key, other.sTable[i].value);
    }

  }

  return *this;
}

//Helper function that performs the binary search on an Entry array
template <class TYPE>
int SimpleTable<TYPE>::binarySearch(const char* key){
	
	int ret = -1;
    
  if (count != 0){

    int low = 0;
    int high = count;
    int mid;

    while (low <= high && ret == -1){

      mid = (low + high)/2;
      if (strcmp(sTable[mid].key, key) > 0)
        high = mid - 1;
      else if (strcmp(sTable[mid].key, key) < 0)
        low = mid + 1;
      else{
        ret = mid;
      }

    }

  }
	return ret;
}

//Updates existing entries of the table their key matches the one pass in otherwise
//inserts a new entry into the table. Table grows when it is fully filled to allow new entries.
template <class TYPE>
bool SimpleTable<TYPE>::update(const char* key, const TYPE& value){

  //When there's still room for more entries
  if (count != max && key){
   
    int flag = binarySearch(key);

		if (flag != -1){ //Update entry
			sTable[flag].value = value;
		}
		else{ //Insert new entry
			if (count == 0 || strcmp(sTable[count-1].key, key) < 0){
				strcpy(sTable[count].key, key);
				sTable[count].value = value;
			}
      else{

        int shiftpt = 0;
        for (int i = 0; i < count; i++){
          if (strcmp(key, sTable[i].key) < 0){
            shiftpt = i;
            break;
          }
        }

        for (int i = max; i > shiftpt; i--){
          if (strlen(sTable[i-1].key) > 0){
						//strcpy(sTable[i].key, sTable[i-1].key);
						sTable[i].key = sTable[i-1].key;
						sTable[i].value = sTable[i-1].value;
          }

        }

				sTable[shiftpt].key = new char[strlen(key)+1];
        strcpy(sTable[shiftpt].key, key);
				sTable[shiftpt].value = value;
      } 
      
			count++;
    }

	}
	else{ //Invalid Key
    return false;
  }	
    
  if (count == max){//Grow the table
    max += max;
    Entry<TYPE>* temp = new Entry<TYPE>[max];

    for (int i = 0; i < count; i ++){
			temp[i] = Entry<TYPE>(sTable[i].key, sTable[i].value);
    }

    delete [] sTable;
    sTable = temp;
  }
	
  return true;
}

//Remove an entry from the table that matches the passed in key if it is present.
template <class TYPE>
bool SimpleTable<TYPE>::remove(const char* key){

  if (count > 0){

		int flag = binarySearch(key);
		if (flag != -1){

      for (int i = flag; i < max; i++){

        if (i + 1 != max && strlen(sTable[i+1].key) > 0){
          //strcpy(sTable[i].key, sTable[i+1].key);
          sTable[i].key = sTable[i+1].key;
					sTable[i].value = sTable[i+1].value;
        }
      }

      count--;
      return true;
		}

  }

  return false;
}

//Finds an entry that matches the passed in key and returns the value of that Entry
//to the value parameter if it exists in the table.
template <class TYPE>
bool SimpleTable<TYPE>::find(const char* key, TYPE& value){

  if (count > 0){
    int flag = binarySearch(key);
		if (flag != -1){
			value = sTable[flag].value;
			return true;
		}
  }
  else
    cout << key << " was not found\n";
   
  return false;
}

//Returns the current number of entries in the table
template <class TYPE>
int SimpleTable<TYPE>::size() const{
	
	/*
	for (int i = 0; i < count; i++)
		cout << "Key " << sTable[i].key << " Value " << sTable[i].value << endl;
	*/
	
  return count;
}

//Returns whether the table is full or not.
template <class TYPE>
bool SimpleTable<TYPE>::isFull() const{
	return (count == max);
}

//Returns whether the table is empty or not
template <class TYPE>
bool SimpleTable<TYPE>::isEmpty() const{
	return (count == 0);
}

//Destructor
template <class TYPE>
SimpleTable<TYPE>::~SimpleTable(){
  max = 0;
  count = 0;
  if (sTable)
    delete [] sTable;
}

//**************************************************End SimpleTable

//**************************************************Start HashTable

template <class TYPE>
class HashTable:public Table<TYPE>{

int max;
int count;
HashList<TYPE>* hTable;

int hasher(const char* key, const int input);
void clear();

public:

  HashTable(int maxExpected = 30);
	HashTable(const HashTable& other);
	virtual const HashTable& operator=(const HashTable& other);
	virtual bool update(const char* key, const TYPE& value);
	virtual bool remove(const char* key);
	virtual bool find(const char* key, TYPE& value);
	virtual int size() const;
	virtual bool isFull() const ;
	virtual bool isEmpty() const;
	virtual ~HashTable();

};

//Helper function, hashes the key for the index
template <class TYPE>
int HashTable<TYPE>::hasher(const char* key, const int input){
  hash<string> h1;
	int h = h1(key);
	int ret = (h > 0 ? h : -h) % input;
  return ret;
}

//Help function, deallocate the whole table
template <class TYPE>
void HashTable<TYPE>::clear(){
	
	max = 0;
  count = 0;
	for (int i = 0; i < max; i++){
		hTable[i].clear();
	}
  hTable = nullptr;
}

//One argument constructor which sets the max entries of the table
template <class TYPE>
HashTable<TYPE>::HashTable(int maxExpected){
  max = maxExpected;
  count = 0;
	hTable = new HashList<TYPE>[max];
}

//Copy constructor
template <class TYPE>
HashTable<TYPE>::HashTable(const HashTable& other){
	//hTable = nullptr; //temp fix
  *this = other;
}

//Assignment Operator
template <class TYPE>
const HashTable<TYPE>& HashTable<TYPE>::operator=(const HashTable<TYPE>& source){
	
  if (this != &source){
		
		if (hTable != nullptr)
			clear();
	
		max = source.max;
		count = source.count;
		hTable = new HashList<TYPE>[max];
		
		
		for (int i = 0; i < max; i++){
			source.hTable[i].goStart();
			hTable[i].goStart();
			while(source.hTable[i].getCurr()){
				hTable[i].insert(source.hTable[i].getKey(), source.hTable[i].getVal());
				source.hTable[i].goNext();
			}
			
		}
  }

  return *this;
}

/*
	Note: The update, remove and find functions rely on the current node of
	each linked list to traverse through the list so the respective functionality
	can be completed. Thus the current node is reset to the front node of that 
	particular list at the beginning of each of  these three functions.
*/

//Updates existing entries of the table or inserts new ones if it does not
//currently exist in the table. Does not grow.
template <class TYPE>
bool HashTable<TYPE>::update(const char* key, const TYPE& value){
	
	int index = hasher(key, max);
	hTable[index].goStart();
	if (!hTable[index].getFront()){ //Empty list then insert for sure
		hTable[index].insert(key, value);
		count++;
		return true;
	}
	else{
		while(hTable[index].getNext() != nullptr && strcmp(hTable[index].getKey(), key) != 0)
			hTable[index].goNext();
		if (strcmp(hTable[index].getKey(), key) == 0){ //update
			hTable[index].setVal(value);
			return true;
		}
		else{ //insert in next spot in linked list
			hTable[index].insert(key, value);
			count++;
			return true;
		}
			
	}
		
  return false;
}

//Removes a entry that matches the given key if found
template <class TYPE>
bool HashTable<TYPE>::remove(const char* key){

	int index = hasher(key, max);
	hTable[index].goStart();
	if (!hTable[index].getFront()){ //Empty list, nothing to remove
		return false;
	}
	else{
		while(hTable[index].getNext() != nullptr && strcmp(hTable[index].getKey(), key) != 0)
			hTable[index].goNext();
		if (strcmp(hTable[index].getKey(), key) == 0){ //found it
			hTable[index].remove();
			count--;
			return true;
		}
		else{ //end of list, not found
			return false;
		}
			
	}
	
	
  return false;
}

//Finds a matching entry if it exists and returns value through parameter value
template <class TYPE>
bool HashTable<TYPE>::find(const char* key, TYPE& value){

	int index = hasher(key, max);
	hTable[index].goStart();
	if (!hTable[index].getFront()){ //Empty list, doesn't exist for sure
		return false;
	}
	else{
		while(hTable[index].getNext() != nullptr && strcmp(hTable[index].getKey(), key) != 0)
			hTable[index].goNext();
		if (strcmp(hTable[index].getKey(), key) == 0){ //found it
			value = hTable[index].getVal();
			return true;
		}
		else{ //end of list, not found
			return false;
		}
			
	}
}

template <class TYPE>
HashTable<TYPE>::~HashTable(){
  clear();
}

//Returns number of entries in the table
template <class TYPE>
int HashTable<TYPE>::size() const{
  return count;
}

//Returns whether the table is full or not.
template <class TYPE>
bool HashTable<TYPE>::isFull() const{
	return (count == max);
}

//Returns whether the table is empty or not
template <class TYPE>
bool HashTable<TYPE>::isEmpty() const{
	return (count == 0);
}

//**************************************************End HashTable

//**************************************************Start TreeTable

template <class TYPE>
struct tNode{
	
	char* key;
	TYPE value;
	tNode<TYPE>* left;
	tNode<TYPE>* right;
	tNode(const char* k, TYPE v, tNode<TYPE>* l = nullptr, tNode<TYPE>* r = nullptr){
		key = new char[30];
		if (k)
			strcpy(key, k);
		value = v;
		left = l;
		right = r;
	}
};

template <class TYPE>
class TreeTable:public Table<TYPE>{

	int count;
	tNode<TYPE>* root;

	void insert(const char* key, TYPE value, tNode<TYPE>*& subtreeroot);
	tNode<TYPE>* search(const char* key, tNode<TYPE>* subtreeroot);
	void remove(const char* key, tNode<TYPE>*& subtreeroot);
	void print(tNode<TYPE>* subtreeroot) const;
	void clear(tNode<TYPE>* subtreeroot);
	void copyTree(tNode<TYPE>*& thisRoot, const tNode<TYPE>* srcRoot);
	
public:

  TreeTable();
	TreeTable(const TreeTable& src);
	virtual const TreeTable& operator=(const TreeTable& src);
	virtual bool update(const char* key, const TYPE& value);
	virtual bool remove(const char* key);
	virtual bool find(const char* key, TYPE& value);
	virtual int size() const;
	virtual bool isFull() const;
	virtual bool isEmpty() const;
	virtual ~TreeTable();

};

//Helps to recursively insert into tree
template <class TYPE>
void TreeTable<TYPE>::insert(const char* key, TYPE value, tNode<TYPE>*& subtreeroot){
	
	if (!subtreeroot){
		subtreeroot = new tNode<TYPE>(key, value);
	}
	else{
		if (strcmp(subtreeroot->key, key) > 0){
			insert(key, value, subtreeroot->left);
		}
		else if (strcmp(subtreeroot->key, key) < 0){
			insert(key, value, subtreeroot->right);
		}
	}
}

//Helps to recursively search through the tree for a node with the specified key
template <class TYPE>
tNode<TYPE>* TreeTable<TYPE>::search(const char* key, tNode<TYPE>* subtreeroot){
	
	tNode<TYPE>* rc = nullptr;
	if (subtreeroot){
		if (strcmp(subtreeroot->key, key) == 0)
			rc = subtreeroot;
		else if(strcmp(subtreeroot->key, key) > 0)
			rc = search(key, subtreeroot->left);
		else
			rc = search(key, subtreeroot->right);
	}
	return rc;
}

//Helps to remove a node from a tree
template <class TYPE>
void TreeTable<TYPE>::remove(const char* key, tNode<TYPE>*& subtreeroot){
	
	if (subtreeroot){
		if (strcmp(subtreeroot->key, key) == 0){
			//remove it, unlink, deallocate
			if (subtreeroot->left && subtreeroot->right){
				//two kids
				tNode<TYPE>* parentofIS = nullptr;
				tNode<TYPE>* inorderSuccessor = subtreeroot->right;
				tNode<TYPE>* rm = subtreeroot;
				while (inorderSuccessor->left){
					parentofIS=inorderSuccessor;
					inorderSuccessor=inorderSuccessor->left;
				}
				if (parentofIS){
					parentofIS->left = inorderSuccessor->right;
					inorderSuccessor->left = subtreeroot->left;
					inorderSuccessor->right = subtreeroot->right;
					subtreeroot=inorderSuccessor;
				}
				else{
					//only occurs if inorder successor is immediate right child of node to be removed
					inorderSuccessor->left = subtreeroot->left;
					subtreeroot=inorderSuccessor;
				}
				
				delete rm;
			}
			else if (!subtreeroot->left &&  !subtreeroot->right){
				//no kids
				delete subtreeroot;
				subtreeroot = nullptr;
			}
			else{
				//one kid
				tNode<TYPE>* rm = subtreeroot;
				subtreeroot = (subtreeroot->left) ?
					(subtreeroot->left) : (subtreeroot->right);
				delete rm;
			}
		}
		else{ //haven't gotten to the node to remove yet
			if (strcmp(subtreeroot->key, key) > 0)
				remove(key, subtreeroot->left);
			else
				remove(key, subtreeroot->right);
		}
	}
}

//Recursively prints the tree through depth first preordered traversals
template <class TYPE>
void TreeTable<TYPE>::print(tNode<TYPE>* subtreeroot) const{
	
	if (subtreeroot){
		cout << "Key " << subtreeroot->key << " Value " << subtreeroot->value << endl;
		print(subtreeroot->left);
		print(subtreeroot->right);
	}
}

//Recursively deallocates all nodes in the tree through depth first postorder traversals
template <class TYPE>
void TreeTable<TYPE>::clear(tNode<TYPE>* subtreeroot){
	
	if (subtreeroot){
		clear(subtreeroot->left);
		clear(subtreeroot->right);
		delete subtreeroot;
	}
}

//Recursive helper function for assignment operator/copy constructor to help copy trees
template <class TYPE>
void TreeTable<TYPE>::copyTree(tNode<TYPE>*& thisRoot, const tNode<TYPE>* srcRoot){
	
	if (srcRoot == nullptr)
		thisRoot = nullptr;
	else{
		thisRoot = new tNode<TYPE>(srcRoot->key, srcRoot->value);
		copyTree(thisRoot->left, srcRoot->left);
		copyTree(thisRoot->right, srcRoot->right);
	}
}

//Default constructor
template <class TYPE>
TreeTable<TYPE>::TreeTable(){
	count = 0;
	root = nullptr;
}

//Copy constructor
template <class TYPE>
TreeTable<TYPE>::TreeTable(const TreeTable<TYPE>& src){
	//root = nullptr;
	*this = src;
}

//Assignment operator
template <class TYPE>
const TreeTable<TYPE>& TreeTable<TYPE>::operator=(const TreeTable<TYPE>& src){
	
	if (this != &src){
		
		count = src.count;
		
		if (root){
			root = nullptr;
		}
		if (src.root != nullptr){
			copyTree(root, src.root);
		}
		
	}
	
	return *this;
}

//Inserts a node into the table or updates an existing one
template <class TYPE>
bool TreeTable<TYPE>::update(const char* key, const TYPE& value){
	
	tNode<TYPE>* upAttempt = search(key, root);
	if (upAttempt){ //update
		upAttempt->value = value;
	}
	else{
		insert(key, value, root);
		count++;
	}
	return true;
}

//Removes a node if it is found in the table
template <class TYPE>
bool TreeTable<TYPE>::remove(const char* key){
	
	tNode<TYPE>* rAttempt = search(key, root);
	if(rAttempt){
		remove(key, root);
		count--;
		return true;
	}
	
	return false;
}

//Finds a node in the table if it exists and returns value through parameter
template <class TYPE>
bool TreeTable<TYPE>::find(const char* key, TYPE& value){
	tNode<TYPE>* sAttempt = search(key, root);
	if (sAttempt){
		value = sAttempt->value;
		return true;
	}
	return false;
}

//Returns the size of the table
template <class TYPE>
int TreeTable<TYPE>::size() const{
	//print(root);
	return count;
}

//Returns whether the table is full or not, always false for Treetable
template <class TYPE>
bool TreeTable<TYPE>::isFull() const{
	return false;
}

//Returns  whether the table is empty or not
template <class TYPE>
bool TreeTable<TYPE>::isEmpty() const{
	return (root == nullptr) ? true : false;
}

//Destructor
template <class TYPE>
TreeTable<TYPE>::~TreeTable(){
	clear(root);
}

//**************************************************End TreeTable
