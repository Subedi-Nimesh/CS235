/***********************************************************************
 * Module:
 *    Week 12, GENEALOGY
 * Author:
 *    Nimesh Subedi
 * Summary:
 *    This program will display the child, his parents and his grandparents.
 ************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void readFile (string filename){

   ifstream fin(filename);
   if ( fin.is_open() )
   {


	}
	else
   {
      cout << "Error reading file \"" << filename << "\"\n";   
   }   


      	fin.close();
}

int main()
{
	string fileLocation = "";
	readFile(fileLocation);
	return 0;
}
