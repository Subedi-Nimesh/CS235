/***********************************************************************
 * Module:
 *    Week 12, HASH
 * Author:
 *    Nimesh Subedi
 * Summary:
 *    This program will implement the Hash as a data structure.
 ************************************************************************/


#ifndef HASH_H
#define HASH_H

#include <list>
#include <iostream> 


using namespace std;


/***********************************************************************
* HASH: hash class
************************************************************************/
template <class T>
class Hash
{
public:
   // Non-default constructor
   Hash(int numItems) throw (const char *) {
   	try
	   {
	      this->numItems = numItems;
	      cap = 0;
	      data = new list<T>[numItems];
	   }
	   catch (std::bad_alloc)
	   {
	      throw "ERROR: unable to allocate memory for the hash";
	   }
   }
   // Copy constructor
   Hash(const Hash<T>& rhs) throw (const char *){
   	try
	   {
	      this->numItems = rhs.numItems;
	      this->cap = rhs.cap;
	      this->data = new list<T>[numItems];

	      // Copy contents of data
	      for (int i = 0; i < numItems; i++)
	      {
	         // Is data allocated?
	         if (&rhs.data != NULL)
	            data[i] = rhs.data[i];
	      }
	   }
	   catch (std::bad_alloc)
	   {
	      throw "ERROR: unable to allocate memory for the hash";
	   }
   }
   // Delete constructor
   ~Hash() 
   {
      // clear each element
      for (int i = 0; i < numItems; i++)
         data[i].clear();

      // delete data
      delete[] data;
   }

   // Hash functions //
   bool empty() { return cap == 0; }  // True if no data is stored
   int size() { return cap; }         // Returns number of items
   int capacity() const { return numItems; }// Returns number of buckets (capacity)
   void clear();
   bool find(T value);
   void insert(T value);

   
   // Assignment operator
   Hash<T>& operator=(const Hash<T> &rhs)
   {
      clear();
      this->numItems = rhs.numItems;
      this->cap = rhs.cap;
      this->data = new list<T>[numItems];

      for (int i = 0; i < numItems; i++)
         this->data[i] = rhs.data[i];

      return *this;
   }

   // Virtual hash function
   virtual int hash(const T & t) const {return 0;}
   

private:
   int numItems;
   int cap;
   list<T>* data;
};

/***********************************************************************
* Clear: Sets size to 0
************************************************************************/
template<class T>
void Hash<T>::clear()
{
   if (!empty())
   {
      for (int i = 0; i < numItems; i++)
         data[i].clear();

      cap = 0;
   }
}

/***********************************************************************
* Find: Iterates through array of list to find element
************************************************************************/
template<class T>
bool Hash<T>::find(T value)
{

   for (typename list<T>::iterator it = data[hash(value)].begin(); it != data[hash(value)].end(); ++it)
   {
      if (*it == value)
         return true;
   }

   return false;
}

/***********************************************************************
* Insert: Inserts element into a hash
************************************************************************/
template<class T>
void Hash<T>::insert(T value)
{
   if (hash(value) >= 0 && hash(value) < numItems)
   {
      data[hash(value)].push_back(value);
      cap++;
   }
}

#endif
