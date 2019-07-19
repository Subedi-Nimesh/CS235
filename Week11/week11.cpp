/***********************************************************************
* Program:
*    Week 11, Sorting
*    Brother Ercanbrack, CS 235
* Author:
*    Nimesh Subedi
* Summary: 
*	  Implementing heapSort and mergeSort.
************************************************************************/

#include <iostream>        // for CIN and COUT
#include <cstring>         // for strcmp
#include <fstream>
#include <iomanip>         // for SETW
#include "heap.h"
#include "merge.h"

using namespace std;

/**********************************************************************
 * MAIN
 * Gets the sort type and filename from the command line. If the sort type
 * or filename are not entered on the command line, the user will be
 * prompted for the sort type and/or filename.
 * Call the appropriate sort to sort the data contained in the vector or
 * linked list and display the sorted data to the console.
 ***********************************************************************/
int main(int argc, const char* argv[])
{
   char sortType[10];
   char fileName[50];
   if (argc == 1)
   {
      cout << "Which sort merge or heap? ";
      cin >> sortType;
      cout << "Enter name of file to sort: ";
      cin >> fileName;
   }
   else if (argc == 2)
   {
      strcpy(sortType,argv[1]);
      cout << "Enter name of file to sort: ";
      cin >> fileName;
   }
   else if (argc == 3)
   {
      strcpy(sortType,argv[1]);    
      strcpy(fileName,argv[2]);
   }
   
   if (strcmp(sortType, "heap") == 0)
   {

   	vector<int> data;
	   int size = 0;
	   int temp;
	   ifstream fin(fileName);

	   if (fin.fail())
	      return -1;

	   while(fin >> temp)
	   {
   		data.push_back(temp);
   		size++;
	   }
   	fin.close();

		heapSort(data, size); 
		printVector(data, size);

   }
   else if (strcmp(sortType, "merge") == 0)
   {

		list<int> data;
	   // int size = 0;
	   int temp;
	   ifstream fin(fileName);

	   if (fin.fail())
	      return -1;

	   while(fin >> temp)
	   {
   		data.push_back(temp);
   		// size++;
   	}

   	fin.close();

		mergeSort(data); 
		printList(data);
      
   }
   else
   {
      cout << "\nInvalid sort name - must be 'heap' or 'merge'" << endl;
   }
   
   return 0;
}
