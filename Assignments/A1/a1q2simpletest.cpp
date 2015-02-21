#include "recentlist.h"
#include <cstring>
#include <iostream>
using namespace std;
struct Record{
	char word_[100];
	int count_;

};
ostream& operator<<(ostream& os, const Record rec){
	os << rec.word_;
	return os;
}
bool compare(const Record& a,const Record& b){
	bool rc=false;
	if(strcmp(a.word_,b.word_)==0)
		rc=true;
	return rc;
}
int main(void){
	Record data[5]={
		{"dog",5},
		{"cat",4},
		{"mouse",3},
		{"hamster",2},
		{"rat",1}
	};
	Record check[5];
	RecentList<Record> list;
	for(int i=0;i<5;i++){
		list.insert(data[i]);
	}

	list.copyToArray(check,5);
	//list should hold (in this order): rat,hamster, mouse,cat, dog
	for(int i=0;i<5;i++){
		cout << check[i] << " ";
	}
	cout << endl;


	Record key;
	strcpy(key.word_,"hamster");
	list.search(key,compare);
	list.copyToArray(check,5);
	//list should hold (in this order): hasmter, rat, mouse,cat, dog
	for(int i=0;i<5;i++){
		cout << check[i] << " ";
	}
	cout << endl;

	strcpy(key.word_,"cat");
	list.search(key,compare);
	list.copyToArray(check,5);
	//list should hold (in this order): cat, hamster,rat, mouse,dog
	for(int i=0;i<5;i++){
		cout << check[i] << " ";
	}
	cout << endl;

}