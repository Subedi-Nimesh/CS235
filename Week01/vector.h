/***********************************************************************
* Header:
*    Container
* Summary:
*    This class contains the notion of a container: a bucket to hold
*    data for the user. This is just a starting-point for more advanced
*    constainers such as the vector, set, stack, queue, deque, and map
*    which we will build later this semester.
*
*    This will contain the class definition of:
*        Container         : A class that holds stuff
*        ContainerIterator : An interator through Container
* Author
*    Br. Helfrich
************************************************************************/

#ifndef VECTOR_H
#define VECTOR_H

#include <cassert>

// forward declaration for VectorIterator
template <class T>
class VectorIterator;

/************************************************
 * Vector
 * A class that holds vector
 ***********************************************/
template <class T>
class Vector
{
public:
	// constructors and destructors
	Vector() : numItems(0), cap(0), data(NULL) {}
	Vector(int capacity) throw (const char *);
	~Vector()        { if (cap) delete [] data; }

	// Copy Constructor
	Vector(const Vector & rhs) throw (const char *);

	// returns the number of items currently in the vector
	int size() const 	{ return numItems; }

	// returns the remaning capacity of the vector
	int capacity() const 	{ return cap; }

	// returns boolean if the vector is empty or not
	bool empty() const  { return numItems == 0; }

	// remove all the items from the vector
   void clear()        { numItems = 0; }

   // add an item to the vector
   void push_back(const T & t) throw (const char *);

   // Assignment operator
   Vector & operator = (const Vector & rhs) throw (const char *);

	// returns by reference 
   T & operator [] (int index)       throw (const char *)
   {
      return data[index];
   }

   const T & operator [] (int index) const throw (const char *)
   {
      return data[index];
   }

   // return an iterator to the beginning of the list
   VectorIterator <T> begin() { return VectorIterator<T>(data); }

   // return an iterator to the end of the list
   VectorIterator <T> end() { return VectorIterator<T>(data + numItems);}


private:
	T * data;			// Allocation of vector
	int numItems;		// number of items currently in the vector
	int cap;				// remaning capacity of the vector
};


/**************************************************
 * VECTOR ITERATOR
 * An iterator through Vector
 *************************************************/
template <class T>
class VectorIterator
{
  public:
   // default constructor
  VectorIterator() : p(NULL) {}

   // initialize to direct p to some item
  VectorIterator(T * p) : p(p) {}

  // Assignment operator
   VectorIterator & operator = (const VectorIterator & rhs)
   {
      this->p = rhs.p;
      return *this;
   }

   // copy constructor
   VectorIterator(const VectorIterator & rhs) { *this = rhs; }

	// equals operator
   bool operator == (const VectorIterator & rhs) const
   {
      return rhs.p == this->p;
   }

   // not equals operator
   bool operator != (const VectorIterator & rhs) const
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
   VectorIterator <T> & operator ++ ()
   {
      p++;
      return *this;
   }

   // postfix increment
   VectorIterator <T> operator++(int postfix)
   {
      VectorIterator tmp(*this);
      p++;
      return tmp;
   }
   
  private:
   T * p;
};

/**********************************************
* VECTOR : NON-DEFAULT CONSTRUCTOR
* Preallocate the vector to "capacity"
**********************************************/
template <class T>
Vector <T> :: Vector(int capacity) throw (const char *)
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

	// initialize the vector by calling the default constructor
	for (int i = 0; i < capacity; i++)
		data[i] = T();
}


/*******************************************
* VECTOR :: COPY CONSTRUCTOR
*******************************************/
template <class T>
Vector <T> :: Vector(const Vector <T> & rhs) throw (const char *)
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
 * VECTOR :: PUSH_BACK
 * Insert an item on the end of the vector
 **************************************************/
template <class T>
void Vector <T> :: push_back(const T & text) throw (const char *)
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
         throw "ERROR";
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
 * VECTOR :: Assignment
 **************************************************/
template <class T>
Vector <T> & Vector <T> :: operator = (const Vector <T> & rhs) 
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
      throw "ERROR: Unable to copy vectors of different sizes";
   }

   for (int i = 0; i < numItems; i++)
      data[i] = rhs.data[i];

   return *this;
}

#endif //VECTOR_H