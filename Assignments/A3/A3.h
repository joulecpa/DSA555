/*
DSA555 Assignment 3
The skyline problem: https://github.com/cathyatseneca/dsa555-w15/wiki/Assignment-3
-Find the silhouette of a skyline that is formed by buildings that potentially overlap.
Author: Hong Zhan Huang
A3.h
*/
#include <iostream>
using namespace std;

#ifndef A3_H
#define A3_H

//The Building struct that we start out with. Added a constructor for ease of use.
struct Building{
   int left_;          //x position of left side of building
   int right_;         //x position of right side of building
   int height_;        //height of the building
	 Building(int l = 0, int r = 0, int h = 0){
		 left_ = l;
		 right_ = r;
		 height_ = h;
	 }
};

int findSilhouette(Building buildingList[],int numBuildings, int silhouette[]);

/*put your unique header file code here if you need to*/

//The Node struct for the SilhouetteBinaryTree. Holds building objects primarily.
struct Node{
	
	Building build;
	Node* left;
	Node* right;
	Node(Building b, Node* l = nullptr, Node* r = nullptr){
		build = b;
		left = l;
		right = r;
	}
	~Node(){ //clear function in BinarySilhouetteTree fulfills the deallocation of all the notes
		//delete left;
		//delete right;	
	}
};

/*
A binary tree structure that is used to sort all the buildings into Nodes that
encompass the ranges that make up the skyline. The Nodes are organized as follows:
left children are to the left of the parent node positionally eg. parent's building has a range
of 3-5, its left child would be positioned left of that range so something like 1-3 or 1-2 would be
valid. The same principle holds for the right children but to the other direction.

In regards to the range 1-3 would affect array positions 1,2. The right side of the range of a Node
is non-inclusive when assigning a value to the array.

This tree works best when buildings are inserted from tallest in height to shortest. In order to 
allow for this, data is sorted by a heap sort for height before it is inserted into the tree.
*/
class SilhouetteBinaryTree{

	int count;
	Node* root;

	void insertR(Building& riser, Node*& subTR);
	void printR(Node* subTR) const;
	void assignR(Node* subTR, int* silhouette);
	void clear(Node*& subTR);
	
public:

  SilhouetteBinaryTree();
	bool insert(Building& build);
	void print() const;
	void assign(int* silhouette);
	int size() const;
	~SilhouetteBinaryTree();

};

#endif