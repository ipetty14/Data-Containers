/***********************************************************************
 * Module:
 *    Week 09, Sort Binary
 *    Brother Helfrich, CS 235
 * Author:
 *    Br. Helfrich
 * Summary:
 *    This program will implement the Binary Tree Sort
 ************************************************************************/

#ifndef SORT_BINARY_H
#define SORT_BINARY_H

#include "bst.h"

/*****************************************************
 * PRINT IN ORDER
 * Print the data from the array in sorted order.
 ****************************************************/
template<class T>
void printInOrder(BinaryNode<T> * root)
{
    if(root == NULL)
        return;
    else
    {
        printInOrder(root->pLeft);
        std::cout << root->data;
        printInOrder(root->pRight);
    }
}

/*****************************************************
 * SORT BINARY
 * Perform the binary tree sort
 ****************************************************/
template <class T>
void sortBinary(T array[], int num)
{
    BinaryNode<T> * root;
    root = NULL;
    
    for (int i = 0; i < num; i++)
    {
        T data = array[i];
        //insert(data);
        
    }
    
    printInOrder(root);
}


#endif // SORT_BINARY_H
