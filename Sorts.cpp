#include <iostream>
#include <math.h>
#include <chrono>

//Is this less offensive than using the entire std namespace?
using std::cout;
using std::endl;

//These little functions are used by the heap-sort algorithm
#define PARENT(i) ((i - 1) / 2)
#define LEFT(i)   (2 * i + 1)
#define RIGHT(i)  (2 * i + 2)



//First comes bubble-sort, the most brute-force sorting method.
//Bubble-sort is a simple sorting algorithm that repeatedly steps 
//through the list to be sorted, compares each pair of adjacent items 
//and swaps them if they are in the wrong order

void bubble_sort(int list[], int size)
{
	int temp;
	for(int i=0; i<size; i++)
	{
		for(int j=size-1; j>i; j--)
		{
			if(list[j]<list[j-1])
			{
				temp=list[j-1];
				list[j-1]=list[j];
				list[j]=temp;
			}
		}
	}
}


//Insertion sort is another n^2 algorithm, which works by taking each element
//and inserting it into the proper spot.  Can work quickly on arrays that 
//are either small or nearly sorted already.

void insertion_sort(int list[], int size)
{
	for(int j=1;j<size;j++)
	{
		int key=list[j];
		int i = j-1;
		while(i>-1 and list[i]>key)
		{
			list[i+1]=list[i];
			i=i-1;
		}
		list[i+1]=key;

	}
}

//Merge-sort is much faster than insertion-sort in general, and works by
//dividing the array successively into smaller arrays, sorting them, and then
//merging the results.  merge_sort is written as two functions, `merge` which takes two
//pre-sorted lists and merges them to a single sorted list.  This is called on by merge_sort, 
//which also recursively calls itself.

void merge(int list[], int p, int q, int r)
{
//n1 and n2 are the lengths of the pre-sorted sublists, list[p..q] and list[q+1..r]
int n1=q-p+1;
int n2=r-q;
//copy these pre-sorted lists to L and R
int L[n1+1];
int R[n2+1];
for(int i=0;i<n1; i++)
{
	L[i]=list[p+i];
}
for(int j=0;j<n2; j++)
{
	R[j]=list[q+1+j];
}


//Create a sentinal value for L and R that is larger than the largest
//element of list
int largest;
if(L[n1-1]<R[n2-1]) largest=R[n2-1]; else largest=L[n1-1];
L[n1]=largest+1;
R[n2]=largest+1;

//Merge the L and R lists
int i=0;
int j=0;
for(int k=p; k<=r; k++)
{
	if (L[i]<=R[j])
	{
	list[k]=L[i];
	i++;
	} else
	{
	list[k]=R[j];
	j++;
	}
}
}

void merge_sort_aux(int list[], int p, int r)
{
if(p<r)
{
	int q=floor((p+r)/2);
	merge_sort_aux(list,p,q);
	merge_sort_aux(list,q+1,r);
	merge(list,p,q,r);
}

}

void merge_sort(int list[], int size)
{
	merge_sort_aux(list, 0, size - 1);
}

//Heap-sort is a really interesting algorithm, which first arranges the 
//array into a max-heap, before sorting.  In a max-heap, each element is 
//greater than its 'children', LEFT and RIGHT.

class heap
{
	public:
		int *nodes;
		int length;
		int heap_size;
};

//max_heapify places the element list[index] into the subarray list[index+1...], 
//which is assumed to already be in max-heap form

void max_heapify(heap list, int index)
{

		int left,right,largest,exchange_temp;

		left = LEFT(index);
		right = RIGHT(index);

		if(left <list.heap_size && list.nodes[left] > list.nodes[index])
		{
			largest = left;
		} else
		{
			largest = index;
		}

		if(right <list.heap_size && list.nodes[right] > list.nodes[largest])
		{
			largest = right;
		}


		if(largest != index)
		{
			exchange_temp = list.nodes[index];
			list.nodes[index] = list.nodes[largest];
			list.nodes[largest] = exchange_temp;
			max_heapify(list, largest);
		}

}

//build_max_heap turns an array into max-heap form by repeatedly calling
//max_heapify

void build_max_heap(heap list)
{
	list.heap_size = list.length;
	for(int i = floor(list.length/2); i>=0; i--)
	{
		max_heapify(list, i);
	}
}

//Since one property of a max-heap is that the first element is the largest,
//heap_sort swaps this element with the last element, then re-heapifies the 
//rest, recursively until the whole array is sorted

void heap_sort(int list[], int size)
{
	int exchange_temp;
	heap tempheap;
	tempheap.length = size;
	tempheap.nodes = list;
	tempheap.heap_size = size;
	build_max_heap(tempheap);


	for(int i= tempheap.length - 1; i>=1; i--)
	{
		exchange_temp = tempheap.nodes[0];
		tempheap.nodes[0] = tempheap.nodes[i];
		tempheap.nodes[i] = exchange_temp;
		tempheap.heap_size = tempheap.heap_size - 1;

		max_heapify(tempheap,0);
	}

}

//Quicksort works by dividing the array based upon a 'pivot' element, everything
//to the right of it are greater than or equal to the pivot, everything 
//smaller than the pivot are moved to the left.  Then the left and right
//arrays are sorted in the same way.  Works great on a random array, but
//data that is nearly already sorted are very slow by this method.

int partition(int list[], int p, int r)
{
	int pivot, index, exchange_temp;
	pivot = list[r];
	index = p - 1;
	for(int i = p; i < r; i++)
	{
		if(list[i] <= pivot)
		{
			index++;
			exchange_temp = list[i];
			list[i] = list[index];
			list[index] = exchange_temp;
		}
	}
	exchange_temp = list[r];
	list[r] = list[index+1];
	list[index+1] = exchange_temp;
	return index+1;
}

void quicksort_aux(int list[], int p, int r)
{
	int q;
	if(p<r)
	{
		q = partition(list, p, r);
		quicksort_aux(list, p, q-1);
		quicksort_aux(list, q+1, r);
	}
}

void quick_sort(int list[], int size)
{
	quicksort_aux(list,0, size-1);
}



int main()
{
	//Now what I want to do is compare the timing of the various sorting routines.  

	std::chrono::high_resolution_clock::time_point t1,t2;
	srand(time(0));

	int npointsmax = 100000, nave = 100, npoints = 46;
	double  bubble_timelist[npoints], insertion_timelist[npoints],merge_timelist[npoints], quick_timelist[npoints], heap_timelist[npoints];

	int *rlist1= new int[npointsmax];
	int *rlist2= new int[npointsmax];
	int *rlist3= new int[npointsmax];
	int *rlist4= new int[npointsmax];
	int *rlist5= new int[npointsmax];

	//I will sort random arrays with number of elements taken from the list
	//{1,2,3..10,20,30..100,200.....100000} .  For each array size I average
	//the time over 100 instances.

	double nplist[npoints];
	nplist[0] = 1;
	for(int n=0;n<5;n++)
	{
		for(int j=2;j<11;j++)
		{
			nplist[9*n + j - 1] = j * pow(10,n);
		}
	}

	int icounter = 0;

	cout<<"Number of random points being sorted:\n";

	for (int npointsi : nplist)
{   
		//bbtime, instime, are the time for an individual run for bubble
		//and insertion sort, respectively. this is added to bb_temp_timer
		//over the 100 instances, then the average is found by dividing this
		//number by 100 and adding it to the list bubble_timelist
		double bbtime,instime,hptime,mgtime,qktime;
		double bb_temp_timer = 0.0;
		double ins_temp_timer = 0.0;
		double hp_temp_timer = 0.0;
		double mg_temp_timer = 0.0;
		double qk_temp_timer = 0.0;
		cout<<npointsi<<endl;
		for(int j = 0; j< nave; j++)
		{

			//generate 5 copies of the exact same random array
			for(int ii=0;ii<npointsi;ii++)
			{
				rlist1[ii]=rlist2[ii]=rlist3[ii]=rlist4[ii]=rlist5[ii]=rand() % 1000;
			}

			//The following section of the code seems repetative, how could I simplify it?

			t1 = std::chrono::high_resolution_clock::now();
			merge_sort(rlist1,npointsi);
			t2 = std::chrono::high_resolution_clock::now();
			mgtime = std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count();
			mg_temp_timer += mgtime ;

			t1 = std::chrono::high_resolution_clock::now();
			heap_sort(rlist2,npointsi);
			t2 = std::chrono::high_resolution_clock::now();
			hptime = std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count();
			hp_temp_timer += hptime ;

			t1 = std::chrono::high_resolution_clock::now();
			quick_sort(rlist3,npointsi);
			t2 = std::chrono::high_resolution_clock::now();
			qktime = std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count();
			qk_temp_timer += qktime ;

			//I know that bubble and insertion grow as O(n^2) in the average
			//case, so I won't bother with them once the array grows too large.
			if(npointsi<=500)
			{
				t1 = std::chrono::high_resolution_clock::now();
				bubble_sort(rlist4,npointsi);
				t2 = std::chrono::high_resolution_clock::now();
				bbtime = std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count();
				bb_temp_timer += bbtime ;

				t1 = std::chrono::high_resolution_clock::now();
				insertion_sort(rlist5,npointsi);
				t2 = std::chrono::high_resolution_clock::now();
				instime = std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count();
				ins_temp_timer += instime   ;
			} else
			{
				bb_temp_timer = 0.0;
				ins_temp_timer = 0.0;
			}

		}


		merge_timelist[icounter] = mg_temp_timer/nave;
		heap_timelist[icounter] = hp_temp_timer/nave;
		quick_timelist[icounter] = qk_temp_timer/nave;
		insertion_timelist[icounter] = ins_temp_timer/nave;
		bubble_timelist[icounter] = bb_temp_timer/nave;
		icounter++;

	}

	//Is there a better way to generate this data table?  A more C++ way?

	FILE * resultsfile;
	resultsfile=fopen("results-comparison_sort-noBS.dat","w");
	for(int j=0;j< npoints;j++) fprintf(resultsfile, "%5e \t %10.2f \t %10.2f \t %10.2f \t %10.2f \t %10.2f \n",nplist[j], bubble_timelist[j], insertion_timelist[j], merge_timelist[j], heap_timelist[j], quick_timelist[j]);
	fclose(resultsfile);


}