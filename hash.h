//
//  hash.h
//  spellChecker
//
//  Created by Ian Petty on 12/2/16.
//  Copyright © 2016 Ian Petty. All rights reserved.
//

#ifndef hash_h
#define hash_h

#include <vector>
#include <list>

using namespace std;

/****************************************
 * HASH
 * Class designed to implement a hash.
 * Contains a vector of lists.
 ****************************************/
template <class T>
class Hash
{
public:
    Hash () : numItems(0), hCapacity(0) {}
    
    Hash(int capacity)
    {
        hashTable.resize(capacity);
        this->hCapacity = capacity;
        this->numItems = 0;
    }
    
    ~Hash() {};
    
    Hash(const Hash & rhs);
    
    Hash & operator = (const Hash & rhs);
    
    bool empty()
    {
        return (numItems == 0);
    }
    
    int size() const { return numItems; }
    int capacity() const { return hCapacity; }
    void clear();
    bool find(T value);
    void insert(T value);
    virtual int hash(const T & value) const = 0;

private:
    int numItems;
    int hCapacity;
    vector<list<T> > hashTable;
};

/****************************************
 * HASH : COPY CONSTRUCTOR
 * Copy Constructor for the hash table
 ****************************************/
template <class T>
Hash<T>::Hash(const Hash<T> & rhs)
{
    this->numItems = rhs.numItems;
    this->hCapacity = rhs.hCapacity;
    this->hashTable = rhs.hashTable;
}

/****************************************
 * HASH : ASSIGNMENT OPERATOR
 * Copy the hash table using the 
 * overloaded '='
 ****************************************/
template <class T>
Hash<T> & Hash<T>::operator=(const Hash<T> & rhs)
{
    this->numItems = rhs.numItems;
    this->hCapacity = rhs.hCapacity;
    this->hashTable = rhs.hashTable;
    return *this;
}

/****************************************
 * HASH : CLEAR
 * Clear the hash table using the vector
 * clear function
 ****************************************/
template <class T>
void Hash<T>::clear()
{
    hashTable.clear();
    numItems = 0;
    hCapacity = 0;
}

/****************************************
 * HASH : FIND
 * Find the value based on the the index
 * in the hash table. Iterates through 
 * the list at that index in the vector
 * and returns true or false
 ****************************************/
template <class T>
bool Hash<T>::find (T value)
{
    int index = hash(value);
    
    for (typename list<T>::iterator it = hashTable[index].begin(); it != hashTable[index].end(); it++)
    {
       if (*it == value)
           return true;
    }
    
    return false;
}

/****************************************
 * HASH : INSERT
 * Insert a value at a specific index in
 * the hash table.
 ****************************************/
template <class T>
void Hash<T>::insert(T value)
{
    int index = hash(value);
    
    hashTable[index].push_back(value);
    
    numItems++;
    
}

/****************************************
 * S HASH
 * A simple hash of strings
 ****************************************/
class SHash : public Hash <string>
{
public:
    SHash(int numBuckets)    throw (const char *) : Hash <string> (numBuckets) {}
    SHash(const SHash & rhs) throw (const char *) : Hash <string> (rhs)        {}
    
    // hash function for integers is simply to take the modulous
    int hash(const string & text) const
    {
        int value = 0;
        
        for (int i = 0; i < text.length(); i++)
        {
            value += text[i];
        }
        
        return value % capacity();
    }
};

#endif /* hash_h */
