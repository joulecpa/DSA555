/*
DSA555 Assignment 3
The skyline problem: https://github.com/cathyatseneca/dsa555-w15/wiki/Assignment-3
-Find the silhouette of a skyline that is formed by buildings that potentially overlap.
Author: Hong Zhan Huang
A3.h
*/
#include <iostream>
using namespace std;

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

//SilhouetteBinaryTree Implementation

//Inserts Buildings into the tree recursively, adjusts when there is overlapping ranges
//by simply adjusting left/right position values or by splitting an incoming building
//based on the current node. 
void SilhouetteBinaryTree::insertR(Building& riser, Node*& subTR){
	
	if (!subTR){ //Base case
		subTR = new Node(riser);
		count++;
	}
	else{
		
		if (subTR->build.left_ > riser.right_){ //Simple case of being left of subTR, nooverlap
			insertR(riser, subTR->left);
		}
		else if (subTR->build.right_ < riser.left_){ //Simple case of being right of subTR, no overlap
			insertR(riser, subTR->right);
		}
		else{ //In the case where we may need to split a node due to overlapping ranges
			
			if (riser.left_ < subTR->build.left_ && riser.right_ <= subTR->build.right_){ 
				//left side of riser sticks out
				riser.right_ = subTR->build.left_;
				insertR(riser, subTR->left);
			}
			else if(riser.right_ > subTR->build.right_ && riser.left_ >= subTR->build.left_){ 
				//right side of riser sticks out
				riser.left_ = subTR->build.right_;
				insertR(riser, subTR->right);
			}
			else{ //riser's range is contains the current node or is the exact range of the node
				
				//riser contains subTR, split the incoming node into child nodes of the current node
				if ((riser.left_ < subTR->build.left_ && riser.right_ > subTR->build.right_)){
					Building lBuild = Building(riser.left_, subTR->build.left_, riser.height_);
					Building rBuild = Building(subTR->build.right_, riser.right_, riser.height_);
					
					insertR(lBuild, subTR->left);
					insertR(rBuild, subTR->right);
				}
				else if (riser.left_ == subTR->build.left_ && riser.right_ == subTR->build.right_){
					//riser's range is equal to subTR, just update the height if needed
					if (riser.height_ > subTR->build.height_)
						subTR->build.height_ = riser.height_;
				}
			}
		}
		
	}
}

//In-order recursive traversal print function for testing purposes	
void SilhouetteBinaryTree::printR(Node* subTR) const{
	if (subTR){
		printR(subTR->left);
		cout << "B-left: " << subTR->build.left_ << " B-right: " << subTR->build.right_
			<< " B-height: " << subTR->build.height_ << endl;
		printR(subTR->right);
	}
}

//In-order recursive traversal assignment of values from each node to the silhouette array
void SilhouetteBinaryTree::assignR(Node* subTR, int* silhouette){
	
	if (subTR){
		assignR(subTR->left, silhouette);
		
		for (int i = subTR->build.left_; i < subTR->build.right_; i++){
			silhouette[i] = subTR->build.height_;
		}
		
		assignR(subTR->right, silhouette);
	}
}

//Deallocate all the nodes	
void SilhouetteBinaryTree::clear(Node*& subTR){
	if (subTR){
		clear(subTR->left);
		clear(subTR->right);
		delete subTR;
	}
}

//Default constructor
SilhouetteBinaryTree::SilhouetteBinaryTree(){
	count = 0;
	root = nullptr;
}

//Insert function wrapper that calls insertR
bool SilhouetteBinaryTree::insert(Building& build){
	int cur = size();
	insertR(build, root);
	
	if (cur < size())
		return true;
	else
		return false;
}

//Print function wrapper that calls printR
void SilhouetteBinaryTree::print() const{
	printR(root);
}

//Assign function wrapper that calls assignR
void SilhouetteBinaryTree::assign(int* silhouette){
	assignR(root, silhouette);
}

//Returns the number of nodes in the tree
int SilhouetteBinaryTree::size() const{
	return count;
}
	
SilhouetteBinaryTree::~SilhouetteBinaryTree(){
	clear(root);
}

//End SilhouetteBinaryTree

/*
The following are functions that enable a heap sort for the buildings. It sorts them
so the output is by tallest buildings to smallest buildings. 
*/

//Swaps two buildings
void swap(Building* a, Building* b){
	
	Building* c = a;
	a = b;
	b = c;
}

//A percolate up process for the heap 
void shiftHeap(Building*& heap, int i, int heapSize){
	int cur, leftChild, rightChild;
	while (true){
		cur = i;
		leftChild = (2*i) + 1;
		rightChild = leftChild + 1;
		
		if(leftChild < heapSize && heap[leftChild].height_ < heap[cur].height_)
			cur = leftChild;
		if (rightChild < heapSize && heap[rightChild].height_ < heap[cur].height_)
			cur = rightChild;
		if (cur == i) break;
		swap(heap[i], heap[cur]);
		i = cur;
	}
}

//Turn the Building array into a heap
void makeHeap(Building*& src, int src_size){
	
	int i = (src_size/2) - 1;
	while (i >= 0){
		shiftHeap(src, i, src_size);
		i--;
	}
	
}

//The main sorting function that uses the above functions 
void heapSort(Building*& src, int src_size){
	
	makeHeap(src, src_size);
	int last = src_size - 1;
	while (last > 0){
		swap(src[0], src[last]);
		shiftHeap(src, 0, last);
		last--;
	}

}	

//End heapSort

int findSilhouette(Building buildingList[],int numBuildings, int silhouette[]);