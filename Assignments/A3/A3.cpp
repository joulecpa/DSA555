/*
DSA555 Assignment 3
The skyline problem: https://github.com/cathyatseneca/dsa555-w15/wiki/Assignment-3
-Find the silhouette of a skyline that is formed by buildings that potentially overlap.
Author: Hong Zhan Huang
A3.cpp
*/
#include "A3.h"
#include <iostream>
using namespace std;

//Finds the silhouette of the skyline formed by the buildings and stores that data in the
//silhouette array as heights of each index
int findSilhouette(Building buildingList[],int numBuildings, int silhouette[]){
	
	heapSort(buildingList, numBuildings);
	
	SilhouetteBinaryTree sbt;
	
	for (int i = 0; i < numBuildings; i++){
		sbt.insert(buildingList[i]);
	}
	
	sbt.assign(silhouette);
	
	return 0;
}

int main(void){
	
	Building* build = new Building[4];
	
	build[0] = Building(1, 4, 4);
	build[1] = Building(7, 12, 6);
	build[2] = Building(6, 8, 10);
	build[3] = Building(5, 14, 3);
	
	/*
	build[0] = Building(1, 5, 11);
	build[1] = Building(2, 7, 6);
	build[2] = Building(3, 9, 13);
	build[3] = Building(12, 16, 7);
	build[4] = Building(14, 25, 3);
	build[5] = Building(19, 22, 18);
	build[6] = Building(23, 29, 13);
	build[7] = Building(24, 28, 4);
	*/
	int silArray[14];
	for (int i = 0; i < 14; i++)
		silArray[i] = 0;
	
	findSilhouette(build, 4, silArray);
	
	for (int i = 0; i < 14; i++){
		cout << silArray[i] << " ";
	}
	
	cout << "\n**********************\n";
	cout << "Exit\n";
	return 0;
}