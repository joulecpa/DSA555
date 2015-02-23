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
  Node<T>* end;
	int listSize;

	public:

    RecentList();
    
    RecentList(const RecentList&);
    RecentList& operator=(const RecentList&);

    void insert(const T&);
    void remove(const T&, bool (*isSame)(const T&, const T&));
    Node<T>* search(const T& key, bool (*isSame)(const T&, const T&));
    bool copyToArray(T array[],int capacity);

    ~RecentList();
    
};

//No argument constructor, sets the object to a safe state
template <class T>
RecentList<T>::RecentList(){

	front = nullptr;
  end = nullptr;
	listSize = 0;
}

		
//Copy constructor, reuses Assignment operator
template <class T>
RecentList<T>::RecentList(const RecentList& rList){
		 
  *this = rList;

}

//Assignment operator overload
template <class T>
RecentList<T>& RecentList<T>::operator=(const RecentList<T>& source){

  if (this != &source){ 

    //Set listSize as it isn't yet for uninitalized objects
    //ie RecentList<T> list = otherlist
    //list isn't initialized so listSize will be a random number
    listSize = 0;

    //Clean up the current list if it exists
    if (front && listSize > 0){

       this->~RecentList();
    }
    else{
      if (front)
        front = nullptr;
    }

    Node<T> * n = source.end;

    while (n){
      this->insert(n->data);
      n = n->prev;
    }

  }

  return *this;
}

//Inserts a node at the front of the list
template <class T>		
void RecentList<T>::insert(const T& data_){

	//Check if there are any nodes to begin with
	if (front){
		//Create a new Node and make its next pointer point to the current front node
		Node<T>* n = new Node<T>(data_, front);
		

		//Then set the current front's prev pointer point to the new node
		front->prev = n;

		//Now the new node is the front node
		front = n;

	}
	else{
		front = new Node<T>(data_);
    end = front;
  }
		
	listSize++;

}

//Removes the first node where data matches the key if such data exists
template <class T>
void RecentList<T>::remove(const T& key, bool (*isSame)(const T&, const T&)){

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
    while (currentNode && !check);

		  //We find a match
			if (check){
					
			  //Detach the previous node and the next node from the currentNode
			  //and attach them to each other

        //Set up the next and prev nodes relative to the currentNode
        Node<T>* pnode = currentNode->prev;
        Node<T>* nnode = currentNode->next;

        //Check if the node is the first node, if it is just make the next node the front
        if (currentNode != front){

				  //Corner case if the node found is the last node in the list
          if (!nnode && pnode){
            pnode->next = nnode;
          }

          //'Normal' case where the currentNode is between two other nodes
          if (nnode && pnode){
            pnode->next = nnode;
            nnode->prev = pnode;
          }			
        
        }
        else{
          front = nnode;
        }

				//Finally remove the currentNode
				delete currentNode;
				listSize--;
			}

	}

  if (!front)
    end = nullptr;

}

//Searches the list for a node with data that matches the key and puts it in the
//front of the list and returns that node.
template <class T>
Node<T>* RecentList<T>::search(const T& key, bool (*isSame)(const T&, const T&)){

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
		while(currentNode && !check);

		//We find a match
		if (check){
			
			//Detach the previous node and the next node from the currentNode
			//and attach them to each other
			
      //Set up the previous and next nodes relative to the currentNode
      Node<T>* pnode = currentNode->prev;
      Node<T>* nnode = currentNode->next;

      //Only bother doing if the node found isn't already in front
      if (currentNode != front){

        //Corner case if the node found is the last node in the list
        if (!nnode && pnode){
          pnode->next = nnode;
        }

        //'Normal' case where the currentNode is between two other nodes
        if (nnode && pnode){
          pnode->next = nnode;
          nnode->prev = pnode;
        }

        //Insert the Node to the front
        insert(currentNode->data);
      }
      else{
        //cout << "The node we found was already the front node.\n";
      }

			return currentNode;
		}	

	}

	return currentNode;

}
		
//Copies each node's data into the array starting with the front
//If the array is large enough to hold the entire list return true, false otherwise
template <class T>
bool RecentList<T>::copyToArray(T array[], int capacity){

	Node<T>* currentNode = front;
	int count = 0;

	for (int i = 0; i < capacity && currentNode; i++){
			
		array[i] = currentNode->data;
		currentNode = currentNode->next;
		count++;
	}

	if (count == listSize)
		return true;
				
	return false;
}

//Destructor
template <class T>
RecentList<T>::~RecentList(){
			
  //Traverse through the list and deallocate each node
	while(front){
		listSize--;
    Node<T>* cur = front->next;
    delete front;
    front = cur;
  }

}
