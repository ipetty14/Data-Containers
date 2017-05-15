//
// deque.h
// Created by Ian Petty on 10/7/16.

#ifndef _Deque_h_
#define _Deque_h_

#include <cassert>     // for ASSERT

template<class T>
class Deque {
public:
	//Default Constructor : Empty 
	Deque() : deque_front(0), deque_back(0), deque_capacity(0), numItems(0), data(NULL) {}
	
	//Copy constructor
	Deque(const Deque & rhs) throw (const char *);
	
	//Non-default Constructor : Pre-allocate
	Deque(int deque_capacity) throw (const char *)
	{
		data = new T[deque_capacity];
		deque_front = 0;
		deque_back = -1;
		this->deque_capacity = deque_capacity;
		numItems = 0;
	}
	
	//Destructor : free everything
	~Deque() 
	{ 
		if (data == NULL) 
			delete [] data; 
		data = NULL;
	}
	
	//Overload the '=' operator to copy
	Deque & operator = (Deque & rhs) throw (const char*);
	
	bool empty() const { return numItems == 0; }
	int size() const { return numItems; }
	int capacity() { return deque_capacity; }
	void clear()
	{
		numItems = 0;
		deque_front = deque_back = 0;
	}
	void push_back(T & t) throw (const char *);
	void push_front(T & t) throw (const char *);
	void pop_front() throw (const char *);
	void pop_back() throw (const char *);
 	T & front() throw (const char *);
	T & back() throw (const char *);
	
private:
	T * data;
	int deque_capacity;
	int deque_front;
	int deque_back;
	int numItems;
};

/*******************************************
 * Deque :: Copy Constructor
 *******************************************/
template <class T>
Deque <T> :: Deque(const Deque & rhs) throw (const char *)
{		
	this->deque_capacity = rhs.deque_capacity;
	this->data = new T[rhs.deque_capacity];
	
	int j = rhs.deque_front;
	
	for(int i = 0; i < rhs.numItems; i ++, j = (j + 1) % deque_capacity)
	{
		data[i] = rhs.data[j];
	}	
	
	this->numItems = rhs.numItems;
	this->deque_front = 0;
	this->deque_back = (this->numItems - 1);
}

/*******************************************
 * Deque :: Assignment Operator Overloading 
 *******************************************/
template<class T>
Deque<T> & Deque<T>::operator =(Deque & rhs) throw (const char*)
{
	if (this->deque_capacity <= rhs.numItems)
	{
		if( data != NULL)
		{
			delete[] this->data;
			data = NULL;
		}
		
		try
		{
			data = new T[rhs.deque_capacity];
		}
		catch (std::bad_alloc)
		{
			throw "ERROR: Unable to allocate a new buffer for deque";
		}
		
		this->deque_capacity = rhs.deque_capacity;
	}
	
	int j = rhs.deque_front;
	
	for(int i = 0; i < rhs.numItems; i ++, j = (j + 1) % deque_capacity)
	{
		data[i] = rhs.data[j];
	}	
	
	this->numItems = rhs.numItems;
	this->deque_front = 0;
	this->deque_back = (this->numItems - 1);
			
	return *this;
}

/*******************************************
 * Deque :: Push_back
 * Push items of any type into the deque 
 * from the back.
 *******************************************/
template<class T>
void Deque<T>::push_back(T & t) throw (const char *)
{	
	if(numItems >= deque_capacity || deque_capacity == 0)
	{
		if(deque_capacity == 0)
			deque_capacity = 1;
		
		try 
		{
			T * new_data = new T[deque_capacity * 2];

				
			int j = deque_front;
			
			for(int i = 0; i < numItems; i ++, j = (j + 1) % deque_capacity)
			{
				new_data[i] = data[j];
			}
		
			delete [] data;
			data = new_data;
		}
		catch(std::bad_alloc)
		{
			throw "ERROR: Unable to allocate a new buffer for deque";
		}

		deque_front = 0;
		deque_back = (numItems - 1);
		deque_capacity *= 2;
	}
	
	deque_back = (deque_back + 1) % deque_capacity;
	data[deque_back] = t;
	numItems++;
}

/*******************************************
 * Deque :: Push_front
 * Push items of any type into the deque 
 * from the front.
 *******************************************/
template <class T>
void Deque<T>::push_front(T & t) throw (const char *)
{
	if(numItems >= deque_capacity || deque_capacity == 0)
	{
		if(deque_capacity == 0)
			deque_capacity = 1;
		
		try 
		{
			T * new_data = new T[deque_capacity * 2];

				
			int j = deque_front;
			
			for(int i = 0; i < numItems; i ++, j = (j + 1) % deque_capacity)
			{
				new_data[i] = data[j];
			}
		
			delete [] data;
			data = new_data;
		}
		catch(std::bad_alloc)
		{
			throw "ERROR: Unable to allocate a new buffer for deque";
		}

		deque_front = 0;
		deque_back = (numItems - 1);
		deque_capacity *= 2;
	}
	
	
	deque_front = deque_front - 1;
	
	if (deque_front < 0)
		deque_front = deque_capacity - 1;
		
	data[deque_front] = t;
	numItems++;
}

/*******************************************
 * Queue :: Pop_front
 * Pop (or remove) items of any type from 
 * the front of the deque by changing where 
 * the pointer is assigned.
 *******************************************/
template<class T>
void Deque<T>::pop_front() throw (const char *)
{
	if(numItems > 0) 
	{
		deque_front = (deque_front + 1) % deque_capacity;
		numItems--;
	}
	else 
	{
		throw "ERROR: unable to pop from the front of empty deque";
	}
}

/*******************************************
 * Queue :: Pop_back
 * Pop (or remove) items of any type from 
 * the back of the deque by changing where 
 * the pointer is assigned.
 *******************************************/
template<class T>
void Deque<T>::pop_back() throw (const char *)
{
	if(numItems > 0) 
	{
		deque_back = deque_back - 1;
		
		if (deque_back < 0)
			deque_back = deque_capacity - 1;
		
		numItems--;
	}
	else 
	{
		throw "ERROR: unable to pop from the back of empty deque";
	}
}

/*******************************************
 * Deque :: Front
 * Display the first item put in the deque.
 *******************************************/
template<class T>
T & Deque<T>::front() throw (const char*)
{	
	if(numItems != 0)
		return data[deque_front];
	else 
		throw "ERROR: unable to access data from an empty deque";
}

/*******************************************
 * Deque :: Back
 * Display the most recent item put 
 * in the deque.
 *******************************************/
template<class T>
T & Deque<T>::back() throw (const char*)
{
	if(numItems != 0)
		return data[deque_back];	
	else 
		throw "ERROR: unable to access data from an empty deque";
}

#endif