#include <iostream>
using namespace std;

template <class T>
struct Node{
	T data;
	Node<T>* next;
	Node<T>* prev;

	Node<T>(const T& data_, Node<T>* next_ = nullptr, Node<T>* prev_ = nullptr){
		data = data_;
		next = next_;
		prev = prev_;
	}	
};

template <class T>
class RecentList{

	//The front node
	Node<T>* front;
	int listSize;

	public:

		//No argument constructor, sets the object to a safe state
		RecentList(){

			front = nullptr;
			listSize = 0;
		}

		
		//Copy constructor
		RecentList(const RecentList& rList){
			
			*this = rList;
		}

		//Assignment operator overload
		RecentList& operator=(const RecentList& source){
	
			
			if (this != &source){
				//Delete the current RecentList and deallocate with Destructor
				~RecentList();		
			
				//Make a node to traverse through the source list
				Node<T>* copyNode = source->front;

				while (copyNode){
			
					insert(copyNode->data);
					copyNode = copyNode->next;	
				}
			}

			return *this;
		}

		//Inserts a node at the front of the list
		void insert(const T& data_){

			//Check if there are any nodes to begin with
			if (front){
				//Create a new Node and make its next pointer point to the current front node
				Node<T>* n = new Node<T>(data_, front);
		

				//Then set the current front's prev pointer point to the new node
				front->prev = n;

				//Now the new node is the front node
				front = n;

			}
			else
				front = new Node<T>(data_);
			
			listSize++;
		}

		//Removes the first node where data matches the key if such data exists
		void remove(const T& key, bool (*isSame)(const T&, const T&)){

			//Check if there is a list at all first otherwise do nothing
			if (front != nullptr){
			
				//Create a temporary node to traverse through the linked list
				Node<T>* currentNode = front;
				bool check = false; //flag for isSame

				//Look for the node that where the key matches the node's data
				//keep traversing through the list until end of list
				do {

      		if (isSame(key, currentNode->data)){
						check = true;
					}
					else
						currentNode = currentNode->next;

				}
				while (currentNode->next && !check);

				//We find a match
				if (check){
					
					//Detach the previous node and the next node from the currentNode
					//and attach them to each other
					currentNode->prev->next = currentNode->next;
					currentNode->next->prov = currentNode->prev;
					
					//Finally remove the currentNode
					delete currentNode;
					listSize--;
				}

			}

			

		}

		//Searches the list for a node with data that matches the key and puts it in the
		//front of the list
		Node<T>* search(const T& key, bool (*isSame)(const T&, const T&)){

			Node<T>* currentNode;

			//Check if there is a list at all to begin with
			if (front != nullptr){
				
				//Create a temporary node to traverse through the linked list
				currentNode = front;
			 	bool check = false; //flag for isSame

				//Look for the node where the key matches the node's data until end
				do {

					if (isSame(key, currentNode->data)){
						check = true;
					}
					else
						currentNode = currentNode->next;

				}
				while(currentNode->next && !check);

				//We find a match
				if (check){
			
					//Detach the previous node and the next node from the currentNode
					//and attach them to each other
					currentNode->prev->next = currentNode->next;
					currentNode->next->prev = currentNode->prev;

					//Insert the Node to the front then delete
					insert(currentNode->data);
					
					return currentNode;
				}	

			}

			return currentNode;

		}
		
		//Copies each node's data into the array starting with the front
		//If the array is large enough to hold the entire list return true, false otherwise
		bool copyToArray(T array[], int capacity){

			Node<T>* currentNode = front;
			int count = 0;

			for (int i = 0; i < capacity && i < listSize ; i++){
				
				array[i] = currentNode->data;
			 	currentNode = currentNode->next;
				count++;
			}

			if (count == listSize)
				return true;
				
			return false;
		}

		//Destructor
		~RecentList(){
			
			//Delete all the nodes in the list
			while(front){
				Node<T>* del = front;
				front = front->next;
				delete del;
			}
			
			//Reset listSize
			listSize = 0;
		}
};
