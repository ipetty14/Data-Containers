//
//  list.h
//  doublyLinkedList
//
//  Created by Ian Petty on 10/24/16.
//  Copyright © 2016 Ian Petty. All rights reserved.
//

#ifndef list_h
#define list_h

#include <stdio.h>
#include <new>
#include "node.h"

using namespace std;

template <class T>
class ListIterator;

template <class T>
class List
{
private:
    Node<T> * pHead;
    Node<T> * pTail;
    int numItems;
    
public:
    //Default Constructor
    List () : pHead(NULL), pTail(NULL), numItems(0) {}
    
    //Copy Constructor
    List (const List & rhs);
    
    //Destructor
    ~List() { clear(); }
    
    //Overloaded Assignment Operator
    List & operator =(const List & rhs) throw (const char *);
    
    bool empty() { return (pHead == NULL && pTail == NULL); }
    void clear();
    int size () { return numItems; }
    void push_back(T data) throw (const char *);
    void push_front(T data) throw (const char *);
    void insert(ListIterator<T> & it, T data) throw (const char *);
    void allocate(T data) throw (const char *);
    void remove(ListIterator<T> it) throw (const char *);
    T & front() throw (const char *);
    T & back() throw (const char *);
    
    ListIterator<T> begin() const { return ListIterator<T>(pHead); }
    ListIterator<T> end() const { return ListIterator<T>(NULL); }
    ListIterator<T> rbegin() const { return ListIterator<T>(pTail); }
    ListIterator<T> rend() const { return ListIterator<T>(NULL); }
};

template <class T>
class ListIterator
{
public:
    //Default Constructor
    ListIterator() : p(NULL) {}
    
    //Initialize to direct p to an item
    ListIterator(Node<T> * p) : p(p) {}
    
    //Copy Constructor
    ListIterator(const ListIterator & rhs) { *this = rhs; }
    
    //Assignment Operator
    ListIterator & operator = (const ListIterator & rhs)
    {
        this->p = rhs.p;
        return *this;
    }
    
    //Not Equals Operator
    bool operator != (const ListIterator & rhs) const
    {
        return rhs.p != this->p;
    }
    
    bool operator = (const ListIterator & rhs) const
    {
        return rhs.p = this->p;
    }
    
    bool operator == (const ListIterator & rhs) const
    {
        return rhs.p == this->p;
    }
    
    //Dereference Operator
    T & operator * ()
    {
        return p->data;
    }
    
    //Prefix Increment
    ListIterator <T> & operator ++ ()
    {
        p = p->pNext;
        return *this;
    }
    
    ListIterator <T> & operator -- ()
    {
        p = p->pPrev;
        return *this;
    }
    
    //Postfix Increment
    ListIterator <T> operator++(int postfix)
    {
        ListIterator tmp(*this);
        p++;
        return tmp;
    }
    
    ListIterator <T> operator--(int postfix)
    {
        ListIterator tmp(*this);
        p--;
        return tmp;
    }
    
    Node<T> * p;
};

/*******************************************
 * Linked List :: Copy Constructor
 *******************************************/
template<class T>
List<T>::List(const List & rhs)
{
    this->numItems = rhs.numItems;
    
    Node<T> * pFirst = new Node<T>;
    Node<T> * pTemp = rhs.pHead;
    Node<T> * pCurrent = pFirst;
    
    pFirst->data = rhs.pHead->data;
    
    while (pTemp->pNext)
    {
        pCurrent->pNext = new Node<T>;
        pCurrent->pNext->pPrev = pCurrent;
        pCurrent = pCurrent->pNext;
        pTemp = pTemp->pNext;
        pCurrent->data = pTemp->data;
    }
    
    this->pHead = pFirst;
    this->pTail = pCurrent;
}

/*******************************************
 * Linked List :: Assignment Operator
 *******************************************/
template<class T>
List<T> & List<T>::operator =(const List & rhs) throw (const char *)
{
    try
    {
        freeData(pHead);
        //head = rhs.head;
        pTail = rhs.pTail;
        
        pHead = copy(rhs.pHead);
    }
    catch (std::bad_alloc)
    {
        throw "ERROR: unable to allocate a new node for a list";
    }
    
    this->numItems = rhs.numItems;
    
    return *this;
}

/*******************************************
 * Linked List :: Clear
 * Resets numItems and uses freeData from
 * node.h to clear the list. Accounts for
 * the tail pointer as well.
 *******************************************/
template <class T>
void List<T>::clear()
{
    numItems = 0;
    freeData(pHead);
    pTail = NULL;
}

/*******************************************
 * Linked List :: Push_Back
 * Adds an element to the end of the list
 * and links it to the other nodes.
 *******************************************/
template<class T>
void List<T>::push_back(T data) throw (const char *)
{
    try
    {
        Node<T> * temp = new Node<T>(data);
        
        if (numItems == 0)
        {
            pHead = temp;
            pTail = temp;
            numItems++;
        }
        else
        {
            pTail->pNext = temp;
            temp->pPrev = pTail;
            pTail = temp;
            numItems++;
        }
    }
    catch (std::bad_alloc)
    {
        throw "ERROR: unable to allocate a new node for a list";
    }

}

/*******************************************
 * Linked List :: Push_Front
 * Adds an element to the beginning of the
 * list and links it to the other nodes.
 *******************************************/
template<class T>
void List<T>::push_front(T data) throw(const char *)
{
    if(empty())
    {
        allocate(data);
    }
    else
    {
        try
        {
            Node<T> * pNew = new Node<T>(data);
            pNew->pNext = pHead;
            pHead->pPrev = pNew;
            pHead = pNew;
        }
        catch (std::bad_alloc)
        {
            throw "ERROR: unable to allocate a new node for a list";
        }
        
        numItems++;
    }
}

/*******************************************
 * Linked List :: Insert
 * Adds an element to the middle of the list
 * and links it to the other nodes using the
 * ListIterator to find the proper location.
 *******************************************/
template<class T>
void List<T>::insert(ListIterator<T> & it, T data) throw(const char *)
{
    Node<T> * temp = new Node<T> (data);
    if (empty())
    {
        pHead = temp;
        pTail = temp;
        temp->pPrev = NULL;
        temp->pNext = NULL;
        numItems++;
    }
    
    else if (it.p == pHead)
    {
        temp->pNext = pHead;
        temp->pPrev = NULL;
        pHead->pPrev = temp;
        pHead = temp;
        numItems++;
    }
    
    else if (it == end())
    {
        pTail->pNext = temp;
        temp->pPrev = pTail;
        pTail = temp;
        numItems++;
    }
    
    else
    {
        temp->pNext = it.p;
        temp->pPrev = it.p->pPrev;
        it.p->pPrev = temp;
        temp->pPrev->pNext = temp;
        numItems++;
    }
}

/*******************************************
 * Linked List :: Front
 * Returns the data in the first node of
 * the list.
 *******************************************/
template<class T>
T & List<T>::front() throw(const char *)
{
    if(empty())
        throw "ERROR: unable to access data from an empty list";
    else
        return pHead->data;
}

/*******************************************
 * Linked List :: Back
 * Returns the data in the last node of
 * the list.
 *******************************************/
template<class T>
T & List<T>::back() throw(const char *)
{
    if(empty())
        throw "ERROR: unable to access data from an empty list";
    else
        return pTail->data;
}

/*******************************************
 * Linked List :: Allocate
 * Creates a node and sets it to NULL. Used
 * when the list is empty and is created.
 *******************************************/
template<class T>
void List<T>::allocate(T data) throw (const char *)
{
    try
    {
        Node<T> * pNew = new Node<T>(data);
        pHead = pNew;
        pTail = pNew;
        pNew->pPrev = NULL;
        pNew->pNext = NULL;
    }
    catch (std::bad_alloc)
    {
        throw "ERROR: unable to allocate a new node for a list";
    }
    
    numItems++;
}

/*******************************************
 * Linked List :: Remove
 * Removes a node from the list. It handles
 * three cases: removing from the front,
 * middle and back of the list.
 *******************************************/
template<class T>
void List<T>::remove(ListIterator<T> it) throw (const char *)
{
    Node<T> * pTemp = new Node<T>;
    
    if (it != end())
    {
        if(it.p->pNext == NULL)
        {
            pTemp = pTail;
            pTail = pTemp->pPrev;
            pTail->pNext = NULL;
            delete pTemp;
        }
        else if (it.p->pPrev == NULL)
        {
            pTemp = pHead;
            pHead = pTemp->pNext;
            pHead->pPrev = NULL;
            delete pTemp;
        }
        else
        {
            it.p->pNext->pPrev = it.p->pPrev;
            it.p->pPrev->pNext = it.p->pNext;
            delete it.p;
        }
        
        numItems--;
        it.p = NULL;
    }
    else
    {
        throw "ERROR: unable to remove from an invalid location in a list";
    }
}

#endif /* list_h */

