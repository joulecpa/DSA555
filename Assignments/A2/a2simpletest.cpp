#include "table.h"
#include <iostream>
using namespace std;


int main(void){
	/* test a simple table*/
	Table<int>* table=new SimpleTable<int>();
	int value;
	table->update("dog", 5);
	table->update("cat", 4);
	table->update("mouse", 3);
	bool rc=table->find("dog",value);
	//prints 5
	cout << "value for dog: " << value << endl;
	rc=table->find("cat",value);
	//prints 4
	cout << "value for cat: " << value << endl;

	rc=table->find("hamster",value);
	if(rc){
		cout << "bug, hamster should not have been found" << endl;
	}
	else{
		cout << "correct, hamster is not in table" << endl;
	}

	table->remove("cat");
	rc=table->find("cat",value);
	if(rc){
		cout << "bug, cat should not have been found" << endl;
	}
	else{
		cout << "correct, cat is not in table" << endl;
	}

}