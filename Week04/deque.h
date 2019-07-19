/***********************************************************************
* Header:
*    Deque
* Summary:
*    This class contains the notion of a deque: a bucket to hold
*    data for the user. This is just a starting-point for more advanced
*    constainers such as the deque, set, deque, deque, deque, and map
*    which we will build later this semester.
*
*    This will contain the class definition of:
*        Deque         : A class that holds stuff
*        DequeIterator : An interator through Deque
* Author
*    Br. Helfrich
************************************************************************/
#ifndef DEQUE_H
#define DEQUE_H

#include <cassert>

/************************************************
 * DEQUE
 * A class that holds stuff
 ***********************************************/
template <class T>
class Deque
{
	public:
	// constructors and destructors
	Deque() : numItems(0), cap(0), data(NULL), myFront(0), myBack(0) {}
	Deque(int capacity) throw (const char *);
	~Deque()        { if (cap) delete [] data; }

	// Copy Constructor
	Deque(const Deque & rhs) throw (const char *);

	// returns the number of items currently in the Deque
	int size() const 	{ return numItems; }

	// returns the remaning capacity of the Deque
	int capacity() const 	{ return cap; }

	// returns boolean if the Deque is empty or not
	bool empty() const  { return numItems == 0; }

	// remove all the items from the Deque
   void clear()        { numItems = 0; myFront = 0; myBack = -1; }

   // Assignment operator
   Deque & operator = (const Deque & rhs) throw (const char *);

	T & front() throw (const char *);
	const T & front() const throw (const char *);

	T & back() throw (const char *);
	const T & back() const throw (const char *);

   // removes the item from the front of the deque
   void pop_front();

   // removes the item from the back of the deque
   void pop_back();

   // add an item to the deque
   void push_front(const T & t) throw (const char *);

   // add an item to the deque
   void push_back(const T & t) throw (const char *);

private:
	T * data;			// Allocation of Deque
	int numItems;		// number of items currently in the Deque
	int cap;				// remaning capacity of the Deque
	int myFront;		// the first item in the deque
	int myBack;			// the last item in the deque
};

/**********************************************
* Deque : NON-DEFAULT CONSTRUCTOR
* Preallocate the Deque to "capacity"
**********************************************/
template <class T>
Deque <T> :: Deque(int capacity) throw (const char *)
{
	assert(capacity >= 0);

	// do nothing if there is nothing to do
	if (capacity == 0)
	{
		this->cap = this->numItems = 0;
		this->data = NULL;
		myBack = 0;
		myFront = 0;
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
   myBack = 0;
   myFront = 0;

	// initialize the Deque by calling the default constructor
	for (int i = 0; i < capacity; i++)
		data[i] = T();
}


/*******************************************
* Deque :: COPY CONSTRUCTOR
*******************************************/
template <class T>
Deque <T> :: Deque(const Deque <T> & rhs) throw (const char *)
{
	assert(rhs.cap >= 0);

	// do nothing if there is nothing to do
	if (rhs.cap == 0)
	{
		cap = 0;
		numItems = 0;
		data = NULL;
		myFront = 0;
		myBack = 0;
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
   myBack = rhs.myBack;
   myFront = rhs.myFront;

	int tempFront = myFront;
	// copy the items over one at a time using the assignment operator
	for (int i = 0; i < numItems; i++)
	{
		data[tempFront] = rhs.data[tempFront];
		tempFront = (tempFront + 1) % cap;
	}
}

/***************************************************
 * DEQUE :: POP
 * Removes an item on the top-most of the deque
 **************************************************/
template <class T>
void Deque <T> :: pop_front()
{
	if (empty())
	{
   	throw "ERROR: unable to pop from the front of empty deque";
   }
   else
   {
   	// myFront++;
		myFront = (myFront + 1) % cap;
	   numItems--;
   }


}

/***************************************************
 * DEQUE :: POP
 * Removes an item on the top-most of the deque
 **************************************************/
template <class T>
void Deque <T> :: pop_back()
{
	if (empty())
	{
   	throw "ERROR: unable to pop from the back of empty deque";
   }
   else
   {
   	// myBack--;
   	myBack = myBack + cap;
		myBack = (myBack - 1) % cap;
	   numItems--;
   }


}

/***************************************************
 * DEQUE :: FRONT
 * Returns an item at the front of the deque
 **************************************************/
template <class T>
T & Deque <T> :: front() throw (const char *)
{
   if (empty())
      throw "ERROR: unable to access data from an empty deque";
   else
      return data[myFront];
}

template <class T>
const T & Deque <T> :: front() const throw (const char *)
{
   if (empty())
      throw "ERROR: unable to access data from an empty deque";
   else
      return data[myFront];
}

/***************************************************
 * DEQUE :: BACK
 * Returns an item at the back of the deque
 **************************************************/
template <class T>
T & Deque <T> :: back() throw (const char *)
{
   if (empty())
      throw "ERROR: unable to access data from an empty deque";
   else if (myBack == 0)
      return data[myBack];
   else
      return data[myBack - 1];
   // else
   // {
   // 	myBack = numItems;
   // 	myBack = myBack + cap;
   // 	myBack = (myBack - 1) % cap;
   // 	return data[myBack];
   // }
}

template <class T>
const T & Deque <T> :: back() const throw (const char *)
{
   if (empty())
      throw "ERROR: unable to access data from an empty deque";
   else if (myBack == 0)
      return data[myBack];
   else
      return data[myBack - 1];
   // else
   // {
   // 	myBack = numItems;
   // 	myBack = myBack + cap;
   // 	myBack = (myBack - 1) % cap;
   // 	return data[myBack];
   	
   // }
}

/***************************************************
 * Deque :: PUSH
 * Insert an item on the end of the Deque
 **************************************************/
template <class T>
void Deque <T> :: push_back(const T & text) throw (const char *)
{

   if (numItems == 0 && cap != 0)
   {
      myFront = myBack = 0;
   }


	T * temp;

   if (cap == 0)
   {
      cap = 1;
      data = new T[cap];
   }
   else if (numItems >= cap)
   {
      int tempCap = cap;

      try
      {
      	cap = cap * 2;
         temp = new T[cap];
      }
      catch (std::bad_alloc)
      {
         throw "ERROR: Unable to allocate a new buffer for deque";
      }

      int tempFront = myFront;
      for (int i = 0; i < numItems; i++)
      {
         temp[i] = data[tempFront];
         tempFront = (tempFront + 1) % tempCap;
      }
      delete [] data;
      data = temp;
      myFront = 0;
      myBack = numItems;
   }

 
   data[myBack] = text; 
   numItems++;
	myBack = (myBack + 1) % cap;
}
	
/***************************************************
 * Deque :: PUSH
 * Insert an item on the end of the Deque
 **************************************************/
template <class T>
void Deque <T> :: push_front(const T & text) throw (const char *)
{
	T * temp;

   if (cap == 0)
   {
      cap = 1;
      data = new T[cap];
   	myFront = myFront + cap;
   }
   else if (numItems == 0)
   {
      data[myFront] = text;
      numItems++;
      return;
   }
   else if (numItems >= cap)
   {
      int tempCap = cap;

      try
      {
      	cap = cap * 2;
         temp = new T[cap];
      }
      catch (std::bad_alloc)
      {
         throw "ERROR: Unable to allocate a new buffer for deque";
      }

      int tempFront = myFront;
      for (int i = 0; i < numItems; i++)
      {
         temp[i] = data[tempFront];
         tempFront = (tempFront + 1) % tempCap;
      }
      delete [] data;
      data = temp;
      myFront = 0;
   	myFront = myFront + cap;
      myBack = numItems;
   }
   else{
		myFront = myFront + cap;
   }

   myFront = (myFront - 1) % cap;
   data[myFront] = text;
   numItems++;
}

/***************************************************
 * Deque :: Assignment
 **************************************************/
template <class T>
Deque <T> & Deque <T> :: operator = (const Deque <T> & rhs) 
	throw (const char *)
{
	if (cap != rhs.cap)
   {
	   // attempt to allocate
      try
      {
         data = new T[rhs.cap];
      }
      catch (std::bad_alloc)
	   {
         throw "ERROR: Unable to allocate a new buffer for Deque";
      }
   }


   //copy elements
   cap = rhs.cap;
   numItems = rhs.numItems;
   myBack = rhs.myBack;
   myFront = rhs.myFront;
      
   int tempFront = myFront;
   for (int i = 0; i < numItems; i++)
   {
      data[tempFront] = rhs.data[tempFront];
      tempFront = (tempFront + 1) % cap;
   }

      return *this; 
}

#endif //Deque_H