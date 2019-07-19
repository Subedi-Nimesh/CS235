/***********************************************************************
* Header:
*    Stack
* Summary:
*    This class contains the notion of a stack: a bucket to hold
*    data for the user. This is just a starting-point for more advanced
*    constainers such as the stack, set, stack, queue, deque, and map
*    which we will build later this semester.
*
*    This will contain the class definition of:
*        Stack         : A class that holds stuff
*        StackIterator : An interator through Stack
* Author
*    Br. Helfrich
************************************************************************/
#ifndef STACK_H
#define STACK_H

#include <cassert>

/************************************************
 * STACK
 * A class that holds stuff
 ***********************************************/
template <class T>
class Stack
{
	public:
	// constructors and destructors
	Stack() : numItems(0), cap(0), data(NULL) {}
	Stack(int capacity) throw (const char *);
	~Stack()        { if (cap) delete [] data; }

	// Copy Constructor
	Stack(const Stack & rhs) throw (const char *);

	// returns the number of items currently in the Stack
	int size() const 	{ return numItems; }

	// returns the remaning capacity of the Stack
	int capacity() const 	{ return cap; }

	// returns boolean if the Stack is empty or not
	bool empty() const  { return numItems == 0; }

	// remove all the items from the Stack
   void clear()        { numItems = 0; }

   // Assignment operator
   Stack & operator = (const Stack & rhs) throw (const char *);


   // removes the item on the top
   void pop();

   // replaces the last item
   T & top() throw (const char *);

   // add an item to the stack
   void push(const T & t) throw (const char *);


private:
	T * data;			// Allocation of Stack
	int numItems;		// number of items currently in the Stack
	int cap;				// remaning capacity of the Stack
};

/**********************************************
* Stack : NON-DEFAULT CONSTRUCTOR
* Preallocate the Stack to "capacity"
**********************************************/
template <class T>
Stack <T> :: Stack(int capacity) throw (const char *)
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

	// initialize the Stack by calling the default constructor
	for (int i = 0; i < capacity; i++)
		data[i] = T();
}


/*******************************************
* Stack :: COPY CONSTRUCTOR
*******************************************/
template <class T>
Stack <T> :: Stack(const Stack <T> & rhs) throw (const char *)
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

/***************************************************
 * STACK :: POP
 * Removes an item on the top-most of the stack
 **************************************************/
template <class T>
void Stack <T> :: pop()
{
	if (empty())
    {
    	throw "ERROR: Unable to pop from an empty Stack";
    }
    else
		numItems--;
}

/***************************************************
 * STACK :: TOP
 * Returns an item on the top-most of the stack
 **************************************************/
template <class T>
T & Stack <T> :: top() throw (const char *)
{
   if (empty())
      throw "ERROR: Unable to reference the element from an empty Stack";
   else
      return data[size()-1];
}

/***************************************************
 * Stack :: PUSH
 * Insert an item on the end of the Stack
 **************************************************/
template <class T>
void Stack <T> :: push(const T & text) throw (const char *)
{
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
         throw "ERROR: Unable to allocate a new buffer for Stack";
      }
	}
	
	for (int i = 0; i < numItems; i++)
	{
		data[i] = temp[i];
	}

	// add an item to the end
	data[numItems++] = text;
}

/***************************************************
 * Stack :: Assignment
 **************************************************/
template <class T>
Stack <T> & Stack <T> :: operator = (const Stack <T> & rhs) 
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
      throw "ERROR: Unable to copy Stacks of different sizes";
   }

   for (int i = 0; i < numItems; i++)
      data[i] = rhs.data[i];

   return *this;
}

#endif //Stack_H