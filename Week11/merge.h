/***********************************************************************
* Program:
*    Week 11, Sorting
*    Brother Ercanbrack, CS 235
*
* Author:
*   Nimesh Subedi
* Summary: 
*	 Merge Sort
************************************************************************/
#include <list>
#include <iomanip>
   
using namespace std;

template<class T>
void printList(list<T> &data);

template<class T>
void merge(list<T> &data, list<T> &sub1, list<T> &sub2);

template<class T>
void split(list<T> &data, list<T> &sub1, list<T> &sub2);

/*************************************************************************
* This function sorts a linked list using a Natural Merge Sort.
* Input:  data -  linked list of data to be sorted.
* Output: data -  sorted linked list
**************************************************************************/
template<class T>
void mergeSort(list<T> &data)
{

	list<T> sub1;
	list<T> sub2;

	do
	{
		split(data, sub1, sub2);
		
		if (sub1.empty() && !sub2.empty() || !sub1.empty() && sub2.empty()){
			if (!sub1.empty()) {
				data = sub1;
			} else {
				data = sub2;
			}
			break;
		}

		merge(data, sub1, sub2);

	} while (true);
}

/*************************************************************************
* This function splits the list into two different lists and 
* sorts while doing it.
**************************************************************************/
template<class T>
void split(list<T> &data, list<T> &sub1, list<T> &sub2) {

	sub1.clear();
	sub2.clear();

	T temp;
	bool pushed1 = true;

	if (sub1.empty() && sub2.empty())
	{
		sub1.push_back(data.front());
		temp = data.front();
		data.pop_front();
		pushed1 = true;
	}

	while (!data.empty()) {
		if (pushed1 == true)
		{
			if(data.front() >= temp){
				sub1.push_back(data.front());
				temp = data.front();
				data.pop_front();
				pushed1 = true;
			} else {
				sub2.push_back(data.front());
				temp = data.front();
				data.pop_front();
				pushed1 = false;
			}
		} else {

			if(data.front() >= temp){
				sub2.push_back(data.front());
				temp = data.front();
				data.pop_front();
				pushed1 = false;
			} else {
				sub1.push_back(data.front());
				temp = data.front();
				data.pop_front();
				pushed1 = true;
			}
		}
	}
}


/*************************************************************************
* This function merges the two list into one list and 
* sorts while doing it.
**************************************************************************/
template<class T>
void merge(list<T> &data, list<T> &sub1, list<T> &sub2) 
{ 

	if (sub1.front() < sub2.front()) {
		data.push_back(sub1.front());
		sub1.pop_front();
	} else {
		data.push_back(sub2.front());
		sub2.pop_front();
	}

	while(!sub1.empty() || !sub2.empty()) {
		
		if (sub1.front() < sub2.front()) {
			data.push_back(sub1.front());
			sub1.pop_front();
		} else {
			data.push_back(sub2.front());
			sub2.pop_front();
		}		
	}
} 


/*************************************************************************
* This function displays the sorted list.
**************************************************************************/
template<class T>
void printList(list<T> &data)
{
	int count = 0;
	list<int>::iterator it;
   for (it = data.begin(); it != data.end(); ++it){
    	if(count % 10 == 0 && count != 0)
    		cout << endl;
      cout << setw(3) << *it;
      count++;
   }

    cout << "\n"; 
}