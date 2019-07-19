/***********************************************************************
* Header:
*    Queue
* Summary:
*    This class contains the notion of a queue: a bucket to hold
*    data for the user. This is just a starting-point for more advanced
*    constainers such as the queue, set, queue, queue, deque, and map
*    which we will build later this semester.
*
*    This will contain the class definition of:
*        Queue         : A class that holds stuff
*        QueueIterator : An interator through Queue
* Author
*    Br. Helfrich
************************************************************************/
#ifndef QUEUE_H
#define QUEUE_H

#include <cassert>

/************************************************
 * QUEUE
 * A class that holds stuff
 ***********************************************/
template <class T>
class Queue
{
	public:
	// constructors and destructors
	Queue() : numItems(0), cap(0), data(NULL), myFront(0), myBack(0) {}
	Queue(int capacity) throw (const char *);
	~Queue()        { if (cap) delete [] data; }

	// Copy Constructor
	Queue(const Queue & rhs) throw (const char *);

	// returns the number of items currently in the Queue
	int size() const 	{ return numItems; }

	// returns the remaning capacity of the Queue
	int capacity() const 	{ return cap; }

	// returns boolean if the Queue is empty or not
	bool empty() const  { return numItems == 0; }

	// remove all the items from the Queue
   void clear()        { numItems = 0; }

   // Assignment operator
   Queue & operator = (const Queue & rhs) throw (const char *);

	T & front() throw (const char *);

	T & back() throw (const char *);

   // removes the item on the top
   void pop();

   // add an item to the queue
   void push(const T & t) throw (const char *);


private:
	T * data;			// Allocation of Queue
	int numItems;		// number of items currently in the Queue
	int cap;				// remaning capacity of the Queue
	int myFront;		// the first item in the queue
	int myBack;			// the last item in the queue
};

/**********************************************
* Queue : NON-DEFAULT CONSTRUCTOR
* Preallocate the Queue to "capacity"
**********************************************/
template <class T>
Queue <T> :: Queue(int capacity) throw (const char *)
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

	// initialize the Queue by calling the default constructor
	for (int i = 0; i < capacity; i++)
		data[i] = T();
}


/*******************************************
* Queue :: COPY CONSTRUCTOR
*******************************************/
template <class T>
Queue <T> :: Queue(const Queue <T> & rhs) throw (const char *)
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
 * QUEUE :: POP
 * Removes an item on the top-most of the queue
 **************************************************/
template <class T>
void Queue <T> :: pop()
{
	if (empty())
	{
   	throw "ERROR: attempting to pop from an empty queue";
   }
   else
   {
		myFront = (myFront + 1) % cap;
	   numItems--;
   }


}

/***************************************************
 * QUEUE :: FRONT
 * Returns an item at the front of the queue
 **************************************************/
template <class T>
T & Queue <T> :: front() throw (const char *)
{
   if (empty())
      throw "ERROR: attempting to access an item in an empty queue";
   else
      return data[myFront];
}

/***************************************************
 * QUEUE :: BACK
 * Returns an item at the back of the queue
 **************************************************/
template <class T>
T & Queue <T> :: back() throw (const char *)
{
   if (empty())
      throw "ERROR: attempting to access an item in an empty queue";
   else
   {
   	myBack = numItems;
      return data[myBack-1];
   }
}

/***************************************************
 * Queue :: PUSH
 * Insert an item on the end of the Queue
 **************************************************/
template <class T>
void Queue <T> :: push(const T & text) throw (const char *)
{
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
         throw "ERROR: Unable to allocate a new buffer for queue";
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
   // std::cerr << "first: " << myBack << "    Second: ";
   myBack = (myBack + 1) % cap;
   // std::cerr << myBack;
   numItems++;
}
	

/***************************************************
 * Queue :: Assignment
 **************************************************/
template <class T>
Queue <T> & Queue <T> :: operator = (const Queue <T> & rhs) 
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
         throw "ERROR: Unable to allocate a new buffer for Queue";
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

#endif //Queue_H