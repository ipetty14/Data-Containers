/***********************************************************************
* Program:
*    Week 11, Sorting
*    Brother Ercanbrack, CS 235
*
* Author:
*   <Your Name>   
* Summary: 
*
************************************************************************/
#include <iostream>
#include <cstdlib>
#include <cstdio>

using namespace std;

/*************************************************************************
 * Definition of simple node to be used in linked list.
 **************************************************************************/
struct Node
{
    int data;
    struct Node * pNext;
};

void split(Node * root, Node ** front, Node ** back);
struct Node * SortedAndMerged(Node * one, Node * two);

/*************************************************************************
* This function sorts a linked list using a Natural Merge Sort.
* Input:  data -  linked list of data to be sorted.
* Output: data -  sorted linked list
**************************************************************************/
void mergeSort(struct Node ** front)
{
    Node * head = *front;
    Node * temp;
    Node * temp2;
    
    if (head == NULL || head->pNext == NULL)
        return;
    
    split(head, &temp, &temp2);
    mergeSort(&temp);
    mergeSort(&temp2);
    
    *front = SortedAndMerged(temp, temp2);
}

/*************************************************************************
 * Split function for the two lists.
 **************************************************************************/
void split(Node * root, Node ** front, Node ** back)
{
    Node * quickIterator;
    Node * slowIterator;
    
    if (root == NULL || root->pNext == NULL)
    {
        *front = root;
        *back = NULL;
    }
    else
    {
        slowIterator = root;
        quickIterator = root->pNext;
        
        while (quickIterator != NULL)
        {
            quickIterator = quickIterator->pNext;
            
            if (quickIterator != NULL)
            {
                slowIterator = slowIterator->pNext;
                quickIterator = quickIterator->pNext;
            }
        }
        
        *front = root;
        *back = slowIterator->pNext;
        slowIterator->pNext = NULL;
    }
}

/*************************************************************************
 * Returns a node and sorts the data based on merge algorithm.
 **************************************************************************/
Node * SortedAndMerged(struct Node * a, struct Node * b)
{
    Node * result = NULL;
    
    if(a == NULL)
        return b;
    else if (b == NULL)
        return a;
    
    if(a->data <= b->data)
    {
        result = a;
        result->pNext = SortedAndMerged(a->pNext, b);
    }
    else
    {
        result = b;
        result->pNext = SortedAndMerged(a, b->pNext);
    }
    
    return result;
}

/*************************************************************************
 * Definition of simple node push function. Pushes to the front.
 **************************************************************************/
void push(Node ** head, int data)
{
    Node * new_node = new Node;
    new_node->data = data;
    new_node->pNext = (*head);
    (*head) = new_node;
}
