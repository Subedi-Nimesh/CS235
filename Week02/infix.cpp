/***********************************************************************
 * Module:
 *    Week 02, Stack
 *    Brother Helfrich, CS 235
 * Author:
 *    Nimesh Subedi
 * Summary:
 *    This program will implement the testInfixToPostfix()
 *    and testInfixToAssembly() functions
 ************************************************************************/

#include <iostream>    // for ISTREAM and COUT
#include <string>      // for STRING
#include <cassert>     // for ASSERT
#include "stack.h"     // for STACK
using namespace std;

/*****************************************************
 * CONVERT INFIX TO POSTFIX
 * Convert infix equation "5 + 2" into postifx "5 2 +"
 *****************************************************/
string convertInfixToPostfix(const string & infix)
{
   string postfix;
   char character;
   char alpha;
   Stack <char> temp;

   for (int i = 0; i < infix.length(); i++)
   {
      character = infix[i];
      switch(character)
      {
         case ' ': break;
         case '(': temp.push(character);break;
         case ')': break;
         case '^':
         case '/':
         case '*':
         case '+': 
         case '-':
            for ( ; ; )
            {
               if (temp.empty() || temp.top() == '(' || (character == '^') || (character == '/' || character == '*') && (temp.top() == '+' || temp.top() == '-'))
               {
               	temp.push(character);
               	break;
               }
               else
               {
                  alpha = temp.top();
                  temp.pop();
                  postfix += " ";
                  postfix += alpha;
               }
            }
            break;
         
         default:
         if (infix[i - 1] == '.')
         {
            postfix += character;
         }
         else if (!isalnum(infix[i - 1]))
         {
            postfix += " ";
            postfix += character;
         }
         else
         {
            postfix += character;
         }
            break;
      }
         
   }


   while (!temp.empty())
   {
   	if (temp.top() == '(')
   		temp.pop();
   	else
   	{
   		postfix += " ";
      	postfix += temp.top();
      	temp.pop();
   	}
   }

   return postfix;
}

/*****************************************************
 * TEST INFIX TO POSTFIX
 * Prompt the user for infix text and display the
 * equivalent postfix expression
 *****************************************************/
void testInfixToPostfix()
{
   string input;
   cout << "Enter an infix equation.  Type \"quit\" when done.\n";
   
   do
   {
      // handle errors
      if (cin.fail())
      {
         cin.clear();
         cin.ignore(256, '\n');
      }
      
      // prompt for infix
      cout << "infix > ";
      getline(cin, input);

      // generate postfix
      if (input != "quit")
      {
         string postfix = convertInfixToPostfix(input);
         cout << "\tpostfix: " << postfix << endl << endl;
      }
   }
   while (input != "quit");
}

/**********************************************
 * CONVERT POSTFIX TO ASSEMBLY
 * Convert postfix "5 2 +" to assembly:
 *     LOAD 5
 *     ADD 2
 *     STORE VALUE1
 **********************************************/
string convertPostfixToAssembly(const string & postfix)
{
   string assembly;

   return assembly;
}

/*****************************************************
 * TEST INFIX TO ASSEMBLY
 * Prompt the user for infix text and display the
 * resulting assembly instructions
 *****************************************************/
void testInfixToAssembly()
{
   string input;
   cout << "Enter an infix equation.  Type \"quit\" when done.\n";

   do
   {
      // handle errors
      if (cin.fail())
      {
         cin.clear();
         cin.ignore(256, '\n');
      }
      
      // prompt for infix
      cout << "infix > ";
      getline(cin, input);
      
      // generate postfix
      if (input != "quit")
      {
         string postfix = convertInfixToPostfix(input);
         cout << convertPostfixToAssembly(postfix);
      }
   }
   while (input != "quit");
      
}
