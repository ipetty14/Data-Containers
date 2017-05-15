//
// stack.h
// Created by Ian Petty on 9/21/16.

#ifndef _Stack_h_
#define _Stack_h_

#include <cassert>     // for ASSERT

template<class T>
class Stack {
public:
	//Default Constructor : Empty 
	Stack() : stack_top(0), stack_capacity(0), data(NULL), numItems(0) {}
	
	//Copy constructor
	Stack(const Stack & rhs) throw (const char *);
	
	//Non-default Constructor : Pre-allocate
	Stack(int stack_capacity) throw (const char *)
	{
		data = new T[stack_capacity];
		this->stack_top = 0;
		this->stack_capacity = stack_capacity;
		this->numItems = 0;
	}
	
	//Destructor : free everything
	~Stack() 
	{ 
		if (data == NULL) 
			delete [] data; 
		data = NULL;
	}
	
	//Overload the '=' operator to copy
	Stack & operator = (Stack & rhs) throw (const char*);
	
	bool empty() const { return stack_top == 0; }
	int size() const { return stack_top; }
	int capacity() { return stack_capacity; }
	void push(T t) throw (const char *);
	void pop() throw (const char *);
	T & top() const throw (const char*);
	
private:
	T * data;
	int stack_capacity;
	int stack_top;
	int numItems;
};

/*******************************************
 * Stack :: Copy Constructor
 *******************************************/
template <class T>
Stack <T> :: Stack(const Stack & rhs) throw (const char *)
{		
	try
	{
		data = new T[rhs.stack_capacity];
	}
	catch (std::bad_alloc)
	{
		throw "ERROR: Unable to allocate buffer";
	}
	
	// copy over the capacity and size
	assert(rhs.numItems >= 0 && rhs.numItems <= rhs.stack_capacity);
	
	this->stack_capacity = rhs.stack_capacity;
	this->stack_top = rhs.stack_top;
	this->numItems = rhs.numItems;

	//copy the items over one at a time using the assignment operator
	for (int i = 0; i < stack_top; i++)
		this->data[i] = rhs.data[i];

	// the rest needs to be filled with the default value for T
	for (int i = stack_top; i < stack_capacity; i++)
		this->data[i] = T();
}

/*******************************************
 * Stack :: Assignment Overloading 
 *******************************************/
template<class T>
Stack<T> & Stack<T>::operator =(Stack & rhs) throw (const char*)
{
	if (rhs.stack_capacity != 0 && rhs.stack_capacity >= this->stack_capacity)
	{
		delete[] this->data;
		data = NULL;
		try
		{
			data = new T[rhs.stack_capacity];
		}
		catch (std::bad_alloc)
		{
			throw "ERROR: Unable to allocate buffer";
		}
	}
	
	// copy over the capacity and size
	assert(rhs.stack_top >= 0 && rhs.stack_top <= rhs.stack_capacity);
	this->stack_capacity = rhs.stack_capacity;
	this->stack_top = rhs.stack_top;
	this->numItems = rhs.numItems;

	//copy the items over one at a time using the assignment operator
	for (int i = 0; i < stack_top; i++)
		data[i] = rhs.data[i];

	// the rest needs to be filled with the default value for T
	for (int i = stack_top; i < stack_capacity; i++)
		data[i] = T();
		
	return *this;
}

/*******************************************
 * Stack :: Push
 * Push items of any type onto the top of 
 * the stack.
 *******************************************/
template<class T>
void Stack<T>::push(T t) throw (const char *)
{
	if(numItems == stack_capacity || numItems + 1 == stack_capacity)
	{
		if(this->stack_capacity == 0)
			this->stack_capacity = 1;
		else
			this->stack_capacity *= 2;
	
		T * new_data = new T[stack_capacity];
			
		for(int i = 0; i < numItems; i++)
			new_data[i] = data[i];
		
		if(this->stack_capacity != 0)
		{	
			delete [] data;
			data = NULL;
		}
		
		data = new_data;
	}		
	
	stack_top++;
	data[numItems++] = t;
}

/*******************************************
 * Stack :: Pop
 * Pop (or remove) items of any type from 
 * the top of the stack by changing where 
 * the pointer is assigned.
 *******************************************/
template<class T>
void Stack<T>::pop() throw (const char *)
{
	if(numItems > 0) 
	{
		stack_top--;
		numItems--;
	}
	else 
	{
		throw "ERROR: Unable to pop from an empty Stack";
	}
}

/*******************************************
 * Stack :: Top
 * Display the top item in the stack.
 *******************************************/
template<class T>
T & Stack<T>::top() const throw (const char*)
{	
	if(numItems <= 0)
		throw "ERROR: Unable to reference the element from an empty Stack";
	
	return data[stack_top - 1];
}

#endif