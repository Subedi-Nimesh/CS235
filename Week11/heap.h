/***********************************************************************
* Program:
*    Week 11, Sorting
*    Brother Ercanbrack, CS 235
*
* Author:
*   Nimesh Subedi
* Summary: 
*   Heap Sort
************************************************************************/
#include <vector>
#include <iomanip>

using namespace std;

template<class T>
void heapify(vector<T> &data, int n, int i); 

template<class T>
void printVector(vector<T> &data, int size); 

/*************************************************************************
* This function sorts a vector using a heap sort.
* Input:  data -  Vector to be sorted.
* Output: data -  Vector sorted
**************************************************************************/
template<class T>
void heapSort(vector<T> &data, int size)
{
  int loop = size / 2 - 1;
	for (int i = loop; i >= 0; i--) 
        heapify(data, size, i); 
  
    for (int i = size - 1; i >= 0; i--) 
    {
      swap(data[0], data[i]); 
      
      heapify(data, i, 0); 
    } 
}

/*************************************************************************
* This function sorts the vector.
**************************************************************************/
template<class T>
void heapify(vector<T> &data, int size, int i) 
{ 
	int largest = i;
	int first = 2 * i + 1;
	int second = 2 * i + 2;

	if (first < size && data[first] > data[largest]) 
		  largest = first; 
	
		if (second < size && data[second] > data[largest]) 
		  largest = second; 
	
		if (largest != i)
		{ 
		  swap(data[i], data[largest]); 

     heapify(data, size, largest); 
    } 
}


/*************************************************************************
* This function displays the sorted list.
**************************************************************************/
template<class T>
void printVector(vector<T> &data, int size) 
{ 
    for (int i=0; i<size; ++i){
    	if(i % 10 == 0 && i != 0)
    		cout << endl;
      cout << setw(3) << data[i]; 
    }
    cout << endl; 
} 