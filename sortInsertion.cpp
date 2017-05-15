void sortInsertion(T array[], int num)
{
    Node<T> * myNode = new Node<T> (array[0]);
    for(int i = 0; i < num; i++)
    {
        if(myNode->data > array[i])
        {
            insert(array[i], myNode, true);
        }
        else
        {
            Node<T> * iNode;
            iNode = findIndex(myNode, array[i]);
            insert(array[i], myNode);
        }
    }

    for (int i = 0; i < num && myNode != NULL; i++)
    {
        array[i] = myNode->data;
        myNode = myNode->pNext;
    }
}