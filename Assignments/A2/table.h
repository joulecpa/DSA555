
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

template <class TYPE>
class SimpleTable:public Table<TYPE>{

public:
	SimpleTable();
	SimpleTable(const SimpleTable& other);
	virtual bool update(const char* key, const TYPE& value);
	virtual bool remove(const char* key);
	virtual bool find(const char* key, TYPE& value);
	virtual int size() const;
	virtual bool isFull() const ;
	virtual bool isEmpty() const;
	virtual const SimpleTable& operator=(const SimpleTable& other);
	virtual ~SimpleTable();
};
/* none of the code in the function definitions below are correct.  You can replace what you need
*/
template <class TYPE>
SimpleTable<TYPE>::SimpleTable(): Table<TYPE>(){

}

template <class TYPE>
SimpleTable<TYPE>::SimpleTable(const SimpleTable<TYPE>& other){

}

template <class TYPE>
bool SimpleTable<TYPE>::update(const char* key, const TYPE& value){
	return true;
}

template <class TYPE>
bool SimpleTable<TYPE>::remove(const char* key){
	return true;
}

template <class TYPE>
bool SimpleTable<TYPE>::find(const char* key, TYPE& value){
	return true;
}

template <class TYPE>
int SimpleTable<TYPE>::size() const{
	return true;

}
template <class TYPE>
bool SimpleTable<TYPE>::isFull() const{
	return true;

}
template <class TYPE>
bool SimpleTable<TYPE>::isEmpty() const{
	return true;

}
template <class TYPE>
const SimpleTable<TYPE>& SimpleTable<TYPE>::operator=(const SimpleTable<TYPE>& other){
	return *this;

}
template <class TYPE>
SimpleTable<TYPE>::~SimpleTable(){

}
