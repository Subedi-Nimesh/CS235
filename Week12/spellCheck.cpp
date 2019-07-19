/***********************************************************************
 * Module:
 *    Week 12, Spell Check
 *    Brother Helfrich, CS 235
 * Author:
 *    Nimesh Subedi
 * Summary:
 *    This program will implement the spellCheck() function
 ************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include "spellCheck.h"
#include "hash.h"
using namespace std;

void readFile (string filename, SHash dictionary);
void readDictionary (SHash &dictionary);

/*****************************************
 * TOLOWER
 * converts the word to lower letter by letter
 ****************************************/
string tolower(string convert)
{
   for(int i = 0; i < convert.length(); ++i) {
       convert[i] = tolower(convert[i]);
   }   

   return convert;
}

/*****************************************
 * SPELL CHECK
 * Prompt the user for a file to spell-check
 ****************************************/
void spellCheck()
{
	SHash dictionary(500);
   
   readDictionary(dictionary);


	string filename;

	cout << "What file do you want to check? ";
	cin >> filename;

	readFile (filename, dictionary);
	

}

/*****************************************
 * READFILE
 * Opens the file, reads it and closes it. 
 ****************************************/
void readFile (string filename, SHash dictionary)
{

   //open file
   ifstream fin(filename);
   if ( fin.is_open() )
   {
      string word;
		
		int count = 0;
		bool checked = true;

      while (fin >> word)
      {
			string smallWord = word;
			smallWord = tolower(smallWord);
	   	if(!(dictionary.find(smallWord)) && count == 0)
	        {
	            cout << "Misspelled: " << word << ", ";
	            count++;
	            checked = false;
	        }
	        else if(!(dictionary.find(smallWord)))
	        {
	            cout << word;
	        }
	   }

		if (checked)
	        cout << "File contains no spelling errors\n";
	   else
	        cout << endl;

	}
	else
   {
      cout << "Error reading file \"" << filename << "\"\n";   
   }   


      	fin.close();

}

/*****************************************
 * READDICTIONARY
 * Opens the file, reads it and closes it. 
 ****************************************/
void readDictionary(SHash &dictionary)
{

	string dictionaryLocation = "/home/cs235e/week12/dictionary.txt";

   ifstream fin(dictionaryLocation);
   if ( fin.is_open() )
   {
      string word;

      while (fin >> word)
      {
			dictionary.insert(tolower(word));
      }
   }
   else
   {
      cout << "Error reading file \"" << dictionaryLocation << "\"\n";   
   }

	fin.close();

}