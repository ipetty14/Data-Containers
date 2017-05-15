/***********************************************************************
* Program:
*    Week 11, Sorting
*    Brother Ercanbrack, CS 235
*
* Author:
*   Ian Petty
* Summary: 
*
************************************************************************/

/*************************************************************************
* This function sorts a vector using a heap sort.
* Input:  data -  Array to be sorted.
* Output: data -  Array sorted
**************************************************************************/
template<class T>
void percolateDown(T * array, int i, int n)
{
    int j;
    T temp;
    
    temp = array[i];
    
    j = i * 2;
    
    while(j <= n)
    {
        if (j < n && array[j+1] > array[j])
            j = j + 1;
        if (temp >array[j])
            break;
        else if(temp <= array[j])
        {
            array[j / 2] = array[j];
            j = j * 2;
        }
    }
    
    array[j / 2] = temp;
}

/*************************************************************************
 * Sort the array with the heap algorithm
 **************************************************************************/
template<class T>
void heapSort(T * array, int n)
{
    int i;
    T temp;
    
    for(i = n; i >= 2; i--)
    {
        temp = array[i];
        array[i] = array[1];
        array[1] = temp;
        
        percolateDown(array, 1, i - 1);
    }
}

/*************************************************************************
 * Calls the percolateDown function in a loop. 
 **************************************************************************/
template<class T>
void heapify(T * array, int n)
{
    int i;
    
    for(i = (n / 2); i >= 1; i--)
    {
        percolateDown(array, i, n);
    }
}
