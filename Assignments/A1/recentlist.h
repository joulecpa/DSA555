template <class T>
struct Node{
	T data;
	Node<T>* next;
	Node<T>* prev;

	Node(const T& data_, Node<T>* next_ = nullptr, Node<T>* prev_ = nullptr){
		data = data_;
		next = next_;
		prev = prev_;
	}	
};

template <class T>
class RecentList{

	//The front node
	Node<T>* front;

	public:

		//No argument constructor, sets the object to a safe state
		RecentList(){

			front = nullptr;
		}

		//Copy constructor
		RecentList(const RecentList&){

		}

		//Assignment operator overload
		RecentList& operator=(const RecentList&){

		}

		void insert(const T& data_);
		void remove(const T& key, bool (*isSame)(const T&, const T&));
		Node<T>* search(const T& key, bool (*isSame)(const T&, const T&));
		bool copyToArray(T array[], int capacity);

		~RecentList();
};
