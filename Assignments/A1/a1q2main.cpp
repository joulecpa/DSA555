/****************************************/
/*                                      */
/*   This is the official tester for    */
/*   assignment 1 question 2 of         */
/*   DSA555-w15                         */
/*                                      */
/*   Your code must all pass all tests  */
/*   on matrix as I will use that for   */
/*   testing                            */
/*                                      */
/*   To compile:                        */
/*   g++ a1q2main.cpp                   */
/*                                      */
/*   version 1.1: bug fix to moving     */
/*   copytoarray out of if statement    */
/****************************************/
#include "recentlist.h"
#include <cstring>
#include <iostream>
#include <cstdlib>
using namespace std;
const int cap = 500;
const int numSearches=500;

struct Record{
	char word_[30];
	int count_;

};
ostream& operator<<(ostream& os, const Record rec){
	os << rec.word_;
	return os;
}
bool compareWords(const Record& a,const Record& b){
	bool rc=false;
	if(strcmp(a.word_,b.word_)==0 && a.count_==b.count_){
		rc=true;
	}
	return rc;
}
bool compareNumbers(const int& a, const int& b){
	bool rc=false;
	if(a == b){
		rc=true;
	}
	return rc;
}
template <class T>
void adjust(int idx,T arr[]);
template <class T>
void removeItem(T arr[],int idx,int sz);
template <class T>
bool cmpArrays(T arr1[],T arr2[],int sz, bool (*cmp)(const T&, const T&) );
template <class T>
void printArray(T array[],int sz);
int main(void){
	Record data[20]={
		{"the",1},
		{"quick",2},
		{"brown ",3},
		{"fox",4},
		{"jumped",5},
		{"over",6},
		{"lazy",7},
		{"dog",8},
		{"Calvin",9},
		{"and",10},
		{"Hobbes",11},
		{"night",12},
		{"watch",13},
		{"captain",14},
		{"carrot",15},
		{"lilac",16},
		{"lavender",17},
		{"lily",18},
		{"coffee",19},
		{"tea",20}
	};
	//this array will mirror what happens to LL
	Record mirror[20];
	//this array is used to hold contents of LL
	Record check[20];

	int intData[cap];
	int intCheck[cap];
	int intMirror[cap];
	RecentList<Record> list;
	RecentList<int> intList;
	bool passtest=true;
  int numPassed=0;
    for(int i=0;i<20;i++){
      list.insert(data[19-i]);
      mirror[i]=data[i];
    }
    for(int i=0;i<cap;i++){
       intList.insert(i);
       intData[cap-1-i]=i;
       intMirror[cap-1-i]=i;
    }
    cout << "test 1: create list, insert some records." << endl;
    if(list.copyToArray(check,20) && !cmpArrays(data,check,20,compareWords)){
      passtest=false;
      cout << "Error 1a: Bug in either constructor, insert() or copyToArray()"<< endl;
    }
    if(intList.copyToArray(intCheck,cap) && !cmpArrays(intData,intCheck,cap,compareNumbers)){
       passtest=false;
       cout << "Error 1b: Bug in either constructor, insert() or copyToArray()"<< endl;
    }
    RecentList<Record> copy=list;
    RecentList<int> intCopy=intList;
    if(passtest){
      numPassed++;
    	cout << "test 2: create a duplicate of the lists, ensure they match" << endl;
    	if(copy.copyToArray(check,20) && !cmpArrays(data,check,20,compareWords)){
    		passtest=false;
    		cout << "Error 2a: Bug in copy constructor"  << endl;  		
    	}
    	if(intCopy.copyToArray(intCheck,cap) && !cmpArrays(intData,intCheck,cap,compareNumbers)){
    		passtest=false;
    		cout << "Error 2b: Bug in copy constructor" << endl;
    	}
    }
    if(passtest){
      numPassed++;
    	cout << "test 3: perform some searches, ensure adjustment is handled" << endl;
   		for(int i=0;i<numSearches;i++){
   			int pick=rand()%20;
   			if(list.search(mirror[pick],compareWords)){
     			adjust(pick,mirror);
          list.copyToArray(check,20);
     			if(!cmpArrays(mirror,check,20,compareWords)){
   	  			passtest=false;
            cout << "Error 3a: Bug in search." << endl;
   			  }
        }
        else{
          passtest=false;
        }
   		}
   		for(int i=0;i<numSearches;i++){
   			int pick=rand()%cap;
   			if(intList.search(intMirror[pick],compareNumbers)){
     			adjust(pick,intMirror);
          intList.copyToArray(intCheck,cap);
     			if(!cmpArrays(intMirror,intCheck,cap,compareNumbers)){
   	  			passtest=false;
   		 		  cout << "Error 3b: Bug in search."<< endl;
   			  }
   		  }
        else{
          passtest=false;
        }
      }
    }
    if(passtest){
      numPassed++;
    	cout << "test 4: ensure that copied list were not altered (proper deep copy was made) " << endl;
      copy.copyToArray(check,20);
    	if(!cmpArrays(data,check,20,compareWords)){
    		passtest=false;
    		cout << "Error 4a: Bug in copy constructor, deep copy not made?"  << endl;  		
    	}
      intCopy.copyToArray(intCheck,cap);
    	if(!cmpArrays(intData,intCheck,cap,compareNumbers)){
    		passtest=false;
    		cout << "Error 4b: Bug in copy constructor, deep copy not made?" << endl;
    	}
    }
    if(passtest){
      numPassed++;
    	cout << "test 5: test assignment operator"  << endl;
    	copy = list;
    	intCopy = intList;
      copy.copyToArray(check,20);
    	if(!cmpArrays(mirror,check,20,compareWords)){
    		passtest=false;
    		cout << "Error 5a: Bug in = operator"  << endl;  		
    	}
      intCopy.copyToArray(intCheck,cap);
    	if(!cmpArrays(intMirror,intCheck,cap,compareNumbers)){
    		passtest=false;
    		cout << "Error 5b: Bug in = operator"  << endl;  		
    	}
      for(int i=0;i<20;i++){
        data[i]=mirror[i];
      }
      for(int i=0;i<cap;i++){
        intData[i]=intMirror[i];
      }
    }
    if(passtest){
      numPassed++;
    	cout << "test 6: test remove function"  << endl;
    	list.remove(mirror[19],compareWords);
    	removeItem(mirror,19,20);
      list.copyToArray(check,20);
   		if(!cmpArrays(mirror,check,19,compareWords)){
   			passtest=false;
   			cout << "Error 6a: Bug in remove." << endl;
   		}
   		list.remove(mirror[0],compareWords);
   		removeItem(mirror,0,19);
      list.copyToArray(check,20);
   		if(!cmpArrays(mirror,check,18,compareWords)){
   			passtest=false;
   			cout << "Error 6b: Bug in remove." << endl;
   		}
   		for(int i=0;i<3;i++){
   			int pick=rand()%(18-i);
   			list.remove(mirror[pick],compareWords);
   			removeItem(mirror,pick,18-i);
   			if(list.copyToArray(check,20) && !cmpArrays(mirror,check,18-i-1,compareWords)){
	   			passtest=false;
   				cout << "Error 6c:  Bug in remove." << endl;

   			}
   		}
    	intList.remove(intMirror[0],compareNumbers);
    	removeItem(intMirror,0,cap);
      intList.copyToArray(intCheck,cap);
   		if(!cmpArrays(intMirror,intCheck,cap-1,compareNumbers)){
   			passtest=false;
   			cout << "Error 6d: Bug in remove." << endl;
   		}
      intList.remove(intMirror[0],compareNumbers);
      removeItem(intMirror,0,cap-1);
      intList.copyToArray(intCheck,cap);
      if(!cmpArrays(intMirror,intCheck,cap-2,compareNumbers)){
        passtest=false;
        cout << "Error 6e: Bug in remove." << endl;
      }
      intList.remove(intMirror[cap-3],compareNumbers);
      removeItem(intMirror,cap-3,cap-2);
      intList.copyToArray(intCheck,cap);
      if(!cmpArrays(intMirror,intCheck,cap-3,compareNumbers)){
        passtest=false;
        cout << "Error 6f: Bug in remove." << endl;
      }
      intList.remove(intMirror[cap-4],compareNumbers);
      removeItem(intMirror,cap-4,cap-3);
      intList.copyToArray(intCheck,cap);
      if(!cmpArrays(intMirror,intCheck,cap-4,compareNumbers)){
        passtest=false;
        cout << "Error 6g: Bug in remove." << endl;
      }
   		for(int i=0;i<100;i++){
   			int pick=rand()%(cap-4);
   			intList.remove(intMirror[pick],compareNumbers);
   			removeItem(intMirror,pick,cap-4-i);
        intList.copyToArray(intCheck,cap);
   			if(!cmpArrays(intMirror,intCheck,cap-i-5,compareNumbers)){
	   			passtest=false;
   				cout << "Error 6h:  Bug in remove." << endl;
   			}
   		}
    }
    if(passtest){
      numPassed++;
      cout << "test 7: test assignment operator (deep copy)"  << endl;
      copy.copyToArray(check,20);
      if(!cmpArrays(data,check,20,compareWords)){
        passtest=false;
        cout << "Error 7a: Bug in = operator, no deepcopy?"  << endl;
      }
      intCopy.copyToArray(intCheck,cap);
      if(!cmpArrays(intData,intCheck,cap,compareNumbers)){
        passtest=false;
        cout << "Error 7b: Bug in = operator,no deep copy?"  << endl;     
      }
    }
    if(passtest){
      numPassed++;
      cout << "test 8: search for removed items" << endl;
      int pick[2]={0,19};
      for(int i=0;i<2;i++){
        if(!list.search(data[pick[i]],compareWords)){
          list.copyToArray(check,20);
          if(!cmpArrays(mirror,check,15,compareWords)){
            passtest=false;
            cout << "Error 8a: Bug in search." << endl;
          }
        }
        else{
          cout << "Error 8a: Bug in search" << endl;
          passtest=false;
        }
      }

    }
    if(passtest){
      int pick[4]={0,1,cap-1,cap-2};
      for(int i=0;i<4;i++){
        if(!intList.search(intData[pick[i]],compareNumbers)){
          intList.copyToArray(intCheck,cap);
          if(!cmpArrays(intMirror,intCheck,cap-104,compareNumbers)){
            passtest=false;
            cout << "Error 8b: Bug in search."<< endl;
          }
        }
        else{
          passtest=false;
          cout << "Error 8b: Bug in search."<< endl;
        }
      }

    }
    if(passtest){
      numPassed++;
    }
    if(numPassed == 8){
      cout << "Testing for Assignment 1 completed successfully" << endl;
    }
    else{
      cout << numPassed << " / 8 tests passed.  Looks like you still" << endl;
      cout << "have some work to do" << endl;
    }
}
template <class T>
void adjust(int idx,T arr[]){
  T temp=arr[idx];
  for (int i=idx;i>0 ;i--){
    arr[i]=arr[i-1];
  }/*for*/
  arr[0]=temp;
}
template <class T>
void removeItem(T arr[],int idx,int sz){
  for(int i=idx;i<sz-1;i++){
    arr[i]=arr[i+1];
  }
}
template <class T>
bool cmpArrays(T arr1[],T arr2[],int sz, bool (*cmp)(const T&, const T&) ){
	bool rc=true;
	for(int i=0;i<sz && rc;i++){
		if(!cmp(arr1[i],arr2[i]))
	      rc=false;
  }
  return rc;
}
template <class T>
void printArray(T array[],int sz){
  for(int i=0;i<sz;i++){
    cout << array[i] << endl;
  }
}





