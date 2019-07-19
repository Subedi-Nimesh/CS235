/***********************************************************************
* Header:
*    Container
* Summary:
*    This class contains the notion of a container: a bucket to hold
*    data for the user. This is just a starting-point for more advanced
*    constainers such as the list, set, stack, queue, deque, and map
*    which we will build later this semester.
*
*    This will contain the class definition of:
*        Container         : A class that holds stuff
*        ContainerIterator : An interator through Container
* Author
*    Br. Helfrich
************************************************************************/

#ifndef LIST_H
#define LIST_H

#include <cassert>

// forward declaration for ListIterator
template <class T>
class ListIterator;

/************************************************
 * NODE
 * A class that holds node
 ***********************************************/
template <class T>
class Node
{
  public:
   Node() : pNext(NULL), pPrev(NULL) {}
	Node(const T & t)
	{ 
		data = t; pNext = NULL; pPrev = NULL;
	}

   T data;
   Node<T> * pNext;
   Node<T> * pPrev;
};

/************************************************
 * List
 * A class that holds list
 ***********************************************/
template <class T>
class List
{
public:
	// constructors and destructors
	List() : numItems(0), iHead(NULL), iTail(NULL) {}
	List(int capacity) throw (const char *);
	~List() { clear(); }

	// Copy Constructor
	List(const List<T> & rhs) throw (const char *);

	// returns the number of items currently in the list
	int size() const 	{ return numItems; }

	// returns boolean if the list is empty or not
	bool empty() const  { return numItems == 0; }

	// remove all the items from the list
   void clear()        { numItems = 0; }

   // add an item to the list
   void push_back(const T & t) throw (const char *);

   // add an item to the list
   void push_front(const T & t) throw (const char *);

   // Assignment operator
   List & operator = (const List & rhs) throw (const char *);

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
   ListIterator <T> begin() { return ListIterator<T>(data); }

   // return an iterator to the end of the list
   ListIterator <T> end() { return ListIterator<T>(data + numItems);}


private:
	int numItems;
	Node<T> * iHead;
	Node<T> * iTail;
};


/**************************************************
 * LIST ITERATOR
 * An iterator through List
 *************************************************/
template <class T>
class ListIterator
{
  public:
   // default constructor
  ListIterator() : p(NULL) {}

   // initialize to direct p to some item
  ListIterator(T * p) : p(p) {}

  // Assignment operator
   ListIterator & operator = (const ListIterator & rhs)
   {
      this->p = rhs.p;
      return *this;
   }

   // copy constructor
   ListIterator(const ListIterator & rhs) { *this = rhs; }

	// equals operator
   bool operator == (const ListIterator & rhs) const
   {
      return rhs.p == this->p;
   }

   // not equals operator
   bool operator != (const ListIterator & rhs) const
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

   // returns the item currently at the front of the list
      T & front() throw (const char *)
      {
         if ( iHead != NULL && !empty())
         {
            return iHead->data;   
         }
         else
         {
            throw "ERROR: unable to access data from an empty list";
         }
      }

      // returns the item currently at the back of the list
      T & back() throw (const char *)
      {
         if ( iTail != NULL && !empty() )
         {
            return iTail->data;   
         }
         else
         {
            throw "ERROR: unable to access data from an empty list";
         }
         
      }

      // returns an iterator to the last element in the list
      ListIterator<T> rbegin() const 
      {          
         if ( iTail != NULL )
         {
            return ListIterator<T>(iTail);   
         }
         else
         {
            return NULL;
         }
      } 
      
      // returns an iterator referring to the past-the-front element in the list 
      ListIterator<T> rend() const 
      { 
      
         Node<T> * first = iHead;

         if ( iHead != NULL )
         {
            first = iHead->pPrev;
         }

         return ListIterator<T>(first);
      }

   // prefix increment
   ListIterator <T> & operator ++ ()
   {
      p++;
      return *this;
   }

   // postfix increment
   ListIterator <T> operator++(int postfix)
   {
      ListIterator tmp(*this);
      p++;
      return tmp;
   }
   
  private:
   T * p;
};

/**********************************************
* LIST : NON-DEFAULT CONSTRUCTOR
* Preallocate the list to "capacity"
**********************************************/
template <class T>
List <T> :: List(int capacity) throw (const char *)
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

	// initialize the list by calling the default constructor
	for (int i = 0; i < capacity; i++)
		data[i] = T();
}


/*******************************************
* LIST :: COPY CONSTRUCTOR
*******************************************/
template <class T>
List <T> :: List(const List <T> & rhs) throw (const char *)
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
 * LIST :: PUSH_BACK
 * Insert an item on the end of the list
 **************************************************/
template <class T>
void List <T> :: push_back(const T & text) throw (const char *)
{
	try
   {
      insert(text, iTail, false, true);
   }
   catch (bad_alloc)
   {
      throw "ERROR: unable to allocate a new node for a list";
   }
}

/***************************************************
 * LIST :: PUSH_FRONT
 * Insert an item on the end of the list
 **************************************************/
template <class T>
void List <T> :: push_front(const T & text) throw (const char *)
{
	try
   {
      insert(text, iHead, true, false);
   }
   catch (bad_alloc)
   {
      throw "ERROR: unable to allocate a new node for a list";
   }
}


/***************************************************
 * LIST :: Assignment
 **************************************************/
template <class T>
List <T> & List <T> :: operator = (const List <T> & rhs) 
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
      throw "ERROR: Unable to copy lists of different sizes";
   }

   for (int i = 0; i < numItems; i++)
      data[i] = rhs.data[i];

   return *this;
}

#endif //LIST_H