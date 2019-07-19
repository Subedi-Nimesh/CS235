/***********************************************************************
* Header:
*    Container
* Summary:
*    This class contains the notion of a container: a bucket to hold
*    data for the user. This is just a starting-point for more advanced
*    constainers such as the set, set, stack, queue, deque, and map
*    which we will build later this semester.
*
*    This will contain the class definition of:
*        Container         : A class that holds stuff
*        ContainerIterator : An interator through Container
* Author
*    Br. Helfrich
************************************************************************/

#ifndef SET_H
#define SET_H

#include <cassert>
#include <cstddef>
#include <string>
#include <iostream>

// forward declaration for SetIterator
template <class T>
class SetIterator;

/************************************************
 * Set
 * A class that holds set
 ***********************************************/
template <class T>
class Set
{
public:
	// constructors and destructors
	Set() : numItems(0), cap(0), data(NULL) {}
	Set(int capacity) throw (const char *);
	~Set()        { if (cap) delete [] data; }

	// Copy Constructor
	Set(const Set & rhs) throw (const char *);

	// returns the number of items currently in the set
	int size() const 	{ return numItems; }

	// returns the remaning capacity of the set
	int capacity() const 	{ return cap; }

	// returns boolean if the set is empty or not
	bool empty() const  { return numItems == 0; }

	// remove all the items from the set
   void clear()        { numItems = 0; }

   // add an item to the set
   void push_back(const T & t) throw (const char *);

   // Assignment operator
   Set & operator = (const Set & rhs) throw (const char *);

	// returns by reference 
   T & operator [] (int index)       throw (const char *)
   {
      return data[index];
   }

   const T & operator [] (int index) const throw (const char *)
   {
      return data[index];
   }

   // inserts a item in the set
   void insert(const T & t) throw (const char *);

	// remove an element from the set
   void erase(SetIterator<T> t);

	//finds an desired item in the Set
   // SetIterator<T> find(const T & t) const throw (const char*);

   // intersection operator
   Set<T>  operator && (const Set<T>  rhs);
   
   //union operator
   Set<T>  operator || (const Set<T> rhs);

   // return an iterator to the beginning of the list
   SetIterator <T> begin() { return SetIterator<T>(data); }

   // return an iterator to the end of the list
   SetIterator <T> end() { return SetIterator<T>(data + numItems);}

	// sorts the set in ascending order
   void sort();

   // changes the size of the set
   void resize();



private:
	T * data;			// Allocation of set
	int numItems;		// number of items currently in the set
	int cap;				// remaning capacity of the set
};


/**************************************************
 * SET ITERATOR
 * An iterator through Set
 *************************************************/
template <class T>
class SetIterator
{
  public:
   // default constructor
  SetIterator() : p(NULL) {}

   // initialize to direct p to some item
  SetIterator(T * p) : p(p) {}

  // Assignment operator
   SetIterator & operator = (const SetIterator & rhs)
   {
      this->p = rhs.p;
      return *this;
   }

   // copy constructor
   SetIterator(const SetIterator & rhs) { *this = rhs; }

	// equals operator
   bool operator == (const SetIterator & rhs) const
   {
      return rhs.p == this->p;
   }

   // not equals operator
   bool operator != (const SetIterator & rhs) const
   {
      return rhs.p != this->p;
   }

   // dereference operator
   T & operator * ()
   {
      return *p;
   }

   const T & operator * () const
   {
   		return *p;
   }

   // prefix increment
   SetIterator <T> & operator ++ ()
   {
      p++;
      return *this;
   }

   // postfix increment
   SetIterator <T> operator++(int postfix)
   {
      SetIterator tmp(*this);
      p++;
      return tmp;
   }
   
  private:
   T * p;
};

/**********************************************
* SET : NON-DEFAULT CONSTRUCTOR
* Preallocate the set to "capacity"
**********************************************/
template <class T>
Set <T> :: Set(int capacity) throw (const char *)
{
	assert(capacity >= 0);

	// do nothing if there is nothing to do
	if (capacity == 0)
	{
		this->cap = this->numItems = 0;
		this->data = NULL;
		return;
	}

	// attempt to allocate
	try
	{
		data = new T[capacity];
	}
	catch (std::bad_alloc)
	{
		throw "ERROR: Unable to allocate buffer";
	}


	// copy over the stuff
	this->cap = capacity;
	this->numItems = 0;

	// initialize the set by calling the default constructor
	for (int i = 0; i < capacity; i++)
		data[i] = T();
}


/*******************************************
* SET :: COPY CONSTRUCTOR
*******************************************/
template <class T>
Set <T> :: Set(const Set <T> & rhs) throw (const char *)
{
	assert(rhs.cap >= 0);

	// do nothing if there is nothing to do
	if (rhs.cap == 0)
	{
		cap = 0;
		numItems = 0;
		data = NULL;
		return;
	}

	// attempt to allocate
	try
	{
		data = new T[rhs.cap];
	}
	catch (std::bad_alloc)
	{
		throw "ERROR: Unable to allocate buffer";
	}

	// copy over the capacity and size
	assert(rhs.numItems >= 0 && rhs.numItems <= rhs.cap);
	cap = rhs.cap;
	numItems = rhs.numItems;

	// copy the items over one at a time using the assignment operator
	for (int i = 0; i < numItems; i++)
		data[i] = rhs.data[i];

	// the rest needs to be filled with the default value for T
	for (int i = numItems; i < cap; i++)
		data[i] = T();
}

// /***************************************************
//  * SET :: PUSH_BACK
//  * Insert an item on the end of the set
//  **************************************************/
// template <class T>
// void Set <T> :: push_back(const T & text) throw (const char *)
// {
// 	T * temp;
// 	temp = data;
//    // do we have space?
// 	if (cap == 0)
// 	{
// 		cap++;
// 		data = new T[cap];
// 	}
	
// 	if (cap == numItems)
// 	{
// 		try{
// 			cap = cap * 2;
// 			data = new T[cap];
// 		}
// 		catch (std::bad_alloc)
//       {
//          throw "ERROR";
//       }
// 	}
	
// 	for (int i = 0; i < numItems; i++)
// 	{
// 		data[i] = temp[i];
// 	}

// 	// add an item to the end
// 	data[numItems++] = text;
// }

/***************************************************
 * SET :: Assignment
 **************************************************/
template <class T>
Set <T> & Set <T> :: operator = (const Set <T> & rhs) 
	throw (const char *)
{
	cap = rhs.cap;
	numItems = rhs.numItems;
	try{
		data = new T[cap];
	}
	catch (std::bad_alloc){
		throw "Error: Allocation failed";
	}

   if (rhs.size() != size())
   {
      throw "ERROR: Unable to copy sets of different sizes";
   }

   for (int i = 0; i < numItems; i++)
      data[i] = rhs.data[i];

   return *this;
}

/**************************************************
 *SORT Function
 ************************************************/
template<class T>
void Set<T> :: sort()
{
   T * temp;
   for(int i = 0; i < numItems; i++)
   {
      for(int j = i + 1; j < numItems; j++)
      {
         if(data[i] > data[j])
         {
            temp=data[i];
            data[i]=data[j];
            data[j]=temp;
         }
      }
   }
}


/*************************************************
* SET :: RESIZE Function
*************************************************/
template <class T>
void Set <T> :: resize() {
	T * temp;
	temp = data;
   // do we have space?
	if (cap == 0)
	{
		cap++;
		data = new T[cap];
	}
	
	if (cap == numItems)
	{
		try{
			cap = cap * 2;
			data = new T[cap];
		}
		catch (std::bad_alloc)
      {
         throw "ERROR: Unable to allocate buffer";
      }
	}

   int index = 0;
   
   for (SetIterator<T> it = this->begin(); it != this->end(); ++it)
   {
      temp[index++]= *it;
   }
   
   delete [] data;
   data = temp;
}


/***************************************************
* SET :: INSERT
 * Insert an item on the end of the set
 **************************************************/
template <class T>
void Set <T> :: insert(const T & t) throw (const char *)
{
	resize();

   if(empty())
   {
      data[0]=t;
      numItems++;
   }
      else //if(find(t) == end())
      {
         for (int i = 0; i < numItems; i++)
         {
            if (data[i] > t)
            {
               for (int j = numItems-1; j >= i; j--)
               {
                  data[j+1] = data[j];
               }
               data[i] = t;
               numItems++;
               return;
            }
            else if(t > data[numItems-1])
            {
               data[numItems]=t;
               numItems++;
               return;
            }
         }
      }

}


/***************************************************
 * SET :: ERASE
 * Removes an element from the set
 **************************************************/
template <class T>
void Set <T> :: erase(SetIterator<T> t)
{
	int loop = numItems;
   for (int i = 0; i < loop; i++)
   {
      if (data[i] == *t)
      {
         data[i] = data[numItems--];
      }
   }

   sort();

}



// /*****************************************************
//  *  SET :: FIND
//  ******************************************************/
// template <class T>
// SetIterator<T> Set <T> :: find(const T & t) const throw (const char *)
// {
//    SetIterator<T> location;

//    for(location = this->begin(); location != this->end(); location++)
//    {
//       if(*location==t)
//          return location;
//    }
//    return location;

// }

#endif //SET_H