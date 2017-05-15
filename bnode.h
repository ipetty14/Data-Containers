#ifndef BNODE_H
#define BNODE_H

#include <iostream> 
#include <cassert>

/*****************************************************************
 * BINARY NODE
 * A single node in a binary tree.  Note that the node does not know
 * anything about the properties of the tree so no validation can be done.
 *****************************************************************/
template <class T>
class BinaryNode
{
public:
    //Default Constructor
    BinaryNode() : data(0), pParent(NULL), pLeft(NULL), pRight(NULL) {}
    
    //Non-Default Constructor
    BinaryNode(T data)
    {
        this->data = data;
        pParent = NULL;
        pLeft = NULL;
        pRight = NULL;
    }

    // return size (i.e. number of nodes in tree)
    int size() const
    {
        return 1 +
            (pLeft== NULL? 0 : pLeft->size()) +
            (pRight == NULL ? 0 : pRight->size());
    }
   
    // add a node the left/right
    BinaryNode <T> * addLeft (BinaryNode <T> * pNode);
    BinaryNode <T> * addRight(BinaryNode <T> * pNode);

    // create a node and add it to the left/right
    BinaryNode <T> * addLeft (const T & data) throw (const char *);
    BinaryNode <T> * addRight(const T & data) throw (const char *);
   
    // since no validation is done, everything is public
    BinaryNode <T> * pLeft;
    BinaryNode <T> * pRight;
    BinaryNode <T> * pParent;

    // the data of unknown type: cannot validate so is public
    T data;
};

/*******************************************
 * Linked List :: Push_Front
 * Adds an element to the beginning of the
 * list and links it to the other nodes.
 *******************************************/
template <class T>
BinaryNode <T> * BinaryNode<T>::addLeft(const T & data) throw (const char *)
{
    BinaryNode<T> * pNew;
    
    try
    {
        pNew = new BinaryNode<T>(data);
    }
    catch (std::bad_alloc)
    {
        throw "ERROR: Unable to allocate a node";
    }
    
    return addLeft(pNew);
}

/*******************************************
 * Linked List :: Push_Front
 * Adds an element to the beginning of the
 * list and links it to the other nodes.
 *******************************************/
template <class T>
BinaryNode <T> * BinaryNode<T>::addLeft(BinaryNode<T> * bNode)
{
    this->pLeft = bNode;
    
    if(bNode != NULL)
        bNode->pParent = this;
    
    return this;
}

/*******************************************
 * Linked List :: Push_Front
 * Adds an element to the beginning of the
 * list and links it to the other nodes.
 *******************************************/
template <class T>
BinaryNode <T> * BinaryNode<T>::addRight(const T & data) throw (const char *)
{
    BinaryNode<T> * pNew;
    
    try
    {
       pNew = new BinaryNode<T>(data);
    }
    catch (std::bad_alloc)
    {
        throw "ERROR: Unable to allocate a node";
    }
    
    return addRight(pNew);
}

/*******************************************
 * Linked List :: Push_Front
 * Adds an element to the beginning of the
 * list and links it to the other nodes.
 *******************************************/
template <class T>
BinaryNode <T> * BinaryNode<T>::addRight(BinaryNode<T> * bNode)
{
    this->pRight = bNode;
    
    if(bNode != NULL)
        bNode->pParent = this;
    
    return this;
}

/*******************************************
 * Linked List :: Push_Front
 * Adds an element to the beginning of the
 * list and links it to the other nodes.
 *******************************************/
template<class T>
void deleteBinaryTree(BinaryNode<T> * bNode)
{
    if (bNode != NULL)
    {
        deleteBinaryTree(bNode->pLeft);
        deleteBinaryTree(bNode->pRight);
        delete bNode;
    }
}

/*******************************************
 * Linked List :: Push_Front
 * Adds an element to the beginning of the
 * list and links it to the other nodes.
 *******************************************/
template<class T>
std::ostream & operator << (std::ostream & out, BinaryNode<T> * rhs)
{
    if(rhs != NULL)
    {
        out << rhs->pLeft;
        out << rhs->data << " ";
        out << rhs->pRight;
    }
    
    return out;
}


#endif // BNODE_H
