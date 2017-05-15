/***********************************************************************
* Header:
*    Vector
* Summary:
*    This class contains the notion of a vector: a bucket to hold
*    data for the user. 
*
*    This will contain the class definition of:
*        Vector         : A class that holds data
*        VectorIterator : An interator through the class Vector
* Author
*    Br. Helfrich
************************************************************************/

#ifndef VECTOR_H
#define VECTOR_H

#include <cassert>

// Pre-declaration of the VectorIterator
template <class T>
class VectorIterator;

template <class T>
class RVectorIterator;

/************************************************
 * Vector
 * A class that holds data of a certain type.
 ***********************************************/
template <class T>
class Vector
{
public:
	//Default Constructor : Empty 
	Vector() : numItems(0), Vcapacity(0), data(NULL) {}

	//Copy constructor
	Vector(const Vector & rhs) throw (const char *);
	
	//Non-default Constructor : Pre-allocate
	Vector(int Vcapacity) throw (const char *);
	
	//Destructor : free everything
	~Vector()        { if (Vcapacity) delete [] data; }
	
	//Overload the '=' operator to copy
	Vector & operator=(const Vector & rhs) throw (const char*);
	
	//Overload the "[]" operator 
	T & operator[](int index) throw (const char*);
	T & operator[](int index) const throw (const char*);

	//Is the vector currently empty?
	bool empty() const  { return numItems == 0;         }

	//Remove all the items from the vector
	void clear()        { numItems = 0;                 }

	//How many items are currently in the vector?
	int size() const    { return numItems;              }
	
	//How many items can the vector hold?
	int capacity() 		 { return Vcapacity;             }

	//Add an item to the vector
	void push_back(const T & t) throw (const char *);
	
	//Return an iterator to the beginning of the list
	VectorIterator <T> begin() { return VectorIterator<T>(data); }
	
	RVectorIterator <T> rbegin() { return RVectorIterator<T>(data + (numItems - 1)); }

	//Return an iterator to the end of the list
	VectorIterator <T> end() { return VectorIterator<T>(data + numItems); }
	
	RVectorIterator <T> reverseEnd() { return RVectorIterator<T>(data - 1); }
	
private:
	T * data;          // Dynamically allocated array of T
	int numItems;      // How many items are currently in the Vector?
	int Vcapacity;     // How many items can I put on the Vector before full?
};

/**************************************************
 * Vector Iterator
 * An iterator through the Vector
 *************************************************/
template <class T>
class VectorIterator
{
public:
	//Default Constructor
  	VectorIterator() : p(NULL) {}

	//Initialize to direct p to an item
  	VectorIterator(T * p) : p(p) {}

	//Copy Constructor
	VectorIterator(const VectorIterator & rhs) { *this = rhs; }

	//Assignment Operator
	VectorIterator & operator = (const VectorIterator & rhs)
	{
		this->p = rhs.p;
		return *this;
	}

	//Not Equals Operator
	bool operator != (const VectorIterator & rhs) const
	{
		return rhs.p != this->p;
	}

	//Dereference Operator
	T & operator * ()
	{
		return *p;
	}

	//Prefix Increment
	VectorIterator <T> & operator ++ ()
	{
		p++;
		return *this;
	}
	
	VectorIterator <T> & operator -- ()
	{
		p--;
		return *this;
	}

	//Postfix Increment
	VectorIterator <T> operator++(int postfix)
	{
		VectorIterator tmp(*this);
		p++;
		return tmp;
	}
	
	VectorIterator <T> operator--(int postfix)
	{
		VectorIterator tmp(*this);
		p--;
		return tmp;
	}
	
private:
	T * p;
};

template <class T>
class RVectorIterator
{
public:
	//Default Constructor
  	RVectorIterator() : p(NULL) {}

	//Initialize to direct p to an item
  	RVectorIterator(T * p) : p(p) {}

	//Copy Constructor
	RVectorIterator(const RVectorIterator & rhs) { *this = rhs; }

	//Assignment Operator
	RVectorIterator & operator = (const RVectorIterator & rhs)
	{
		this->p = rhs.p;
		return *this;
	}

	//Not Equals Operator
	bool operator != (const RVectorIterator & rhs) const
	{
		return rhs.p != this->p;
	}

	//Dereference Operator
	T & operator * ()
	{
		return *p;
	}
	
	RVectorIterator <T> & operator ++ ()
	{
		p--;
		return *this;
	}
	
	RVectorIterator <T> operator++(int postfix)
	{
		RVectorIterator tmp(*this);
		p--;
		return tmp;
	}
	
private:
	T * p;
};

/*******************************************
 * Vector :: Copy Constructor
 *******************************************/
template <class T>
Vector <T> :: Vector(const Vector <T> & rhs) throw (const char *)
{
	assert(rhs.Vcapacity >= 0);
		
	// do nothing if there is nothing to do
	if (rhs.Vcapacity == 0)
	{
		Vcapacity = numItems = 0;
		data = NULL;
		return;
	}

	// attempt to allocate
	try
	{
		data = new T[rhs.Vcapacity];
	}
	catch (std::bad_alloc)
	{
		throw "ERROR: Unable to allocate buffer";
	}
	
	// copy over the capacity and size
	assert(rhs.numItems >= 0 && rhs.numItems <= rhs.Vcapacity);
	Vcapacity = rhs.Vcapacity;
	numItems = rhs.numItems;

	// copy the items over one at a time using the assignment operator
	for (int i = 0; i < numItems; i++)
		data[i] = rhs.data[i];

	// the rest needs to be filled with the default value for T
	for (int i = numItems; i < Vcapacity; i++)
		data[i] = T();
}

/**********************************************
 * Vector : Non-Default Constructor
 * Preallocate the vector to its "capacity"
 **********************************************/
template <class T>
Vector <T> :: Vector(int Vcapacity) throw (const char *)
{
	assert(Vcapacity >= 0);
	
	// do nothing if there is nothing to do
	if (Vcapacity == 0)
	{
		this->Vcapacity = this->numItems = 0;
		this->data = NULL;
		return;
	}

	// attempt to allocate
	try
	{
		data = new T[Vcapacity];
	}
	catch (std::bad_alloc)
	{
		throw "ERROR: Unable to allocate buffer";
	}

	// copy over the data
	this->Vcapacity = Vcapacity;
	this->numItems = 0;

	// initialize the vector by calling the default constructor
	for (int i = 0; i < Vcapacity; i++)
		data[i] = T();
}

/***************************************************
 * Vector :: Assignment Operator
 * Overload the assignment operator.
 **************************************************/
template<class T>
Vector<T> & Vector<T>::operator =(const Vector<T> & rhs) throw (const char*)
{
	this->Vcapacity = rhs.Vcapacity;
	this->numItems = rhs.numItems;
	
	if(Vcapacity > 0)
		delete [] data;
	
	try
	{
		data = new T[Vcapacity];
	}
	catch(std::bad_alloc)
	{
		throw "ERROR: Unable to allocate a new buffer for Vector";
	}
	
	for(int i = 0; i < Vcapacity; i++)
	{
		this->data[i] = rhs.data[i];
	}
	
	return *this;
}

/***************************************************
 * Vector :: Bracket Operator
 * Overload the bracket operator.
 **************************************************/
template<class T>
T & Vector<T>::operator[](int index) throw (const char*)
{
	if(index > numItems || index < 0)
		throw "ERROR: Invalid index";
	
	return data[index];	
}

/***************************************************
 * Vector :: Bracket Operator
 * Overload the bracket operator.
 * This method is constant and the above is not.
 **************************************************/
template<class T>
T & Vector<T>::operator[](int index) const throw (const char*)
{
	if(index > numItems || index < 0)
		throw "ERROR: Invalid index";
	
	return data[index];
}

/***************************************************
 * Vector :: Push_Back
 * Add an item of the data type to the end of the
 * current vector.
 **************************************************/
template<class T>
void Vector<T>::push_back(const T & t) throw (const char*)
{
	if(Vcapacity == 0)
	{
		try 
		{
			Vcapacity += 1;
			data = new T[Vcapacity];
		}
		catch(std::bad_alloc)
		{
			throw "ERROR: Insufficent space";
		}
	}	
	
	if(Vcapacity == numItems)
	{
		T * new_data;
		try
		{
			Vcapacity *= 2;
			new_data = new T[Vcapacity];
			
			for(int i = 0; i < numItems; i++)
			{
				new_data[i] = data[i];
			}
			
			delete [] data;
			
			data = new_data;
		}
		catch(std::bad_alloc)
		{
			throw "ERROR: Insufficent space";
		}
	}		
	
	data[numItems++] = t;
}

#endif // VECTOR_H

