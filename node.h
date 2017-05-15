//
//  node.h
//  linkedList
//
//  Created by Ian Petty on 10/19/16.
//  Copyright © 2016 Ian Petty. All rights reserved.
//

#ifndef node_h
#define node_h

#include <stdio.h>

template <class T>
class Node
{
public:
    T data;
    Node * pNext;
    
    Node() : pNext(NULL) {}
    Node(T data) : data(data), pNext(NULL) {}
};

template <class T>
Node<T> * copy(Node<T>* rhs)
{
    Node<T> * pFirst = new Node<T>;
    Node<T> * pTemp = rhs;
    Node<T> * pCurrent = pFirst;
    
    pFirst->data = rhs->data;
    
    while (pTemp->pNext)
    {
        pCurrent->pNext = new Node<T>;
        pCurrent = pCurrent->pNext;
        pTemp = pTemp->pNext;
        pCurrent->data = pTemp->data;
    }
    
    return pFirst;
}

template <class T>
void insert (T data, Node<T> * & pNode, bool isHead = false)
{
    if (pNode == NULL)
    {
        Node<T> * temp = new Node<T> (data);
        pNode = temp;
    }
    else if (isHead == false)
    {
        Node<T> * pNew = new Node<T> (data);
        pNew->pNext = pNode->pNext;
        pNode->pNext = pNew;
    }
    else
    {
        Node<T> * pNew = new Node<T> (data);
        pNew->pNext = pNode;
        pNode = pNew;
    }
}

template <class T>
Node<T> * find (Node<T> * pHead, const T & data)
{
    Node<T> * pCurrent = pHead;
    
    while(pCurrent)
    {
        if(pCurrent->data == data)
        {
            return pCurrent;
        }
        
        pCurrent = pCurrent->pNext;
    }
    
    pCurrent = NULL;
    
    return pCurrent;
}


template <class T>
std::ostream & operator << (std::ostream & out, const Node<T> * pNode)
{
    for(const Node<T> * p = pNode; p; p = p->pNext)
    {
       if (p->pNext != NULL)
           out << p->data << ", ";
       else
           out << p->data;
    }
    
    return out;
}

template <class T>
void freeData(Node<T>* & pNode)
{
    Node<T> * temp = pNode;
    
    while (pNode != NULL)
    {
        temp = pNode->pNext;
        delete pNode;
        
        pNode = temp;
    }
    
    pNode = NULL;
}

#endif /* node_h */
