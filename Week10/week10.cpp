#include <iostream>
#include <iomanip>
#include <cctype>
#include <fstream>
#include <string> 
#include "map.h"
#include <map>

using namespace std;

 typedef map<string, int> mapWords;
 mapWords wd;

int readFile();

/**********************************************************************
 * MAIN
 * displays the map in a sorted order.
 ***********************************************************************/
int main()
{
   int wordsProcessed = readFile();
   cout << "Number of words processed: " << wordsProcessed << endl;
   cout << "100 most common words found and their frequencies:" << endl;
   int i = 0;
   int maxInt = 10000;

   while(i < 100) {
         // string tempString = "";
         int tempInt = 0;
         mapWords::iterator itTwo;
      for(mapWords::iterator it = wd.begin(); it != wd.end(); it++){
         if (it->second > tempInt) {
            tempInt = it->second;
            // tempString = it->first;
            itTwo = it;
         }

   	// 	if(it != wd.end()){
				// cout << setw(23) << it->first << " - " << it->second << endl;
   	// 	}
		}

      cout << setw(23) << itTwo->first << " - " << itTwo->second << endl;
      // maxInt = tempInt;
      wd.erase(itTwo);
      
      i++;
	}

   return 0;
}

/*******************************************
 * READ FILE
 * Reads a file and stores it in a map.
 ******************************************/
int readFile()
{
   char fileName[256];
   string words;
   int count = 0;

   cout << "Enter filename: ";
   cin >> fileName;
   cout << endl;

   ifstream fin(fileName);

   if (fin.fail())
      return -1;

   while(fin >> words) 
   {
   	// for(int i = 0; i < words.length(); i++){
   	// 	if(isalpha(words[i])||words[i]=='-')
 		 //  		words[i] = tolower(words[i]);
 		 //  	else if (words[i]=='('){
 		 //  		words[i] = ' ';
 		 //  	} else {
 		 //  		words[i] = ' ';
 		 //  	}
   	// }

		string temp = "";
   
   	for (int i = 0; i < words.length(); i++){
   		if(isalpha(words[i]) || words[i] == '-'){
   			temp.push_back(tolower(words[i]));		
   		}

		}


  		wd[temp]++;


   	++count;
   } 
      
   fin.close();
   return count;
}