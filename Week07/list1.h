#ifndef LIST_H
#define LIST_H

#include <cstddef> //to define NULL
#include <cassert>
#include <string>
#include <iostream>

using namespace std;

// forward declaration for ListIterator
template <class T>
class ListIterator;

template <class T>
class List;

/************************************************
 * NODE
 * A class that holds stuff
 ***********************************************/
template <class T>
class Node
{
   friend class List<T>;
   friend class ListIterator<Node<T> >;

   public:
      // default constructor : set pNext to NULL
      Node() : pNext(NULL), pPrev(NULL) {}

      // non-default constructor : take T as parameter
      Node(const T & t) 
      {
         data = t;
         pNext = NULL;
         pPrev = NULL; 
      }

      T data;
      Node<T> * pNext; // pointer to next node
      Node<T> * pPrev; // pointer to previous node

};


/************************************************
 * LIST
 * A class that holds stuff
 ***********************************************/
template <class T>
class List
{
   public:

      friend class ListIterator<T>;

      // default constructor : set pNext to NULL
      List() : frontNode(NULL), backNode(NULL), iSize(0) {}

      // copy constructor
      List(const List<T> & rhs) //{ *this = rhs; }
      {
         iSize = 0;
         frontNode = NULL;
         backNode = NULL;

         for (ListIterator <T> it = rhs.begin(); it != NULL; ++it)
         {
            push_back(*it);
         }
      }

      // destructor
      ~List() { 
         clear();
      }

      // assignment operator
      List & operator = (const List & rhs)
      {
      
         //TODO avoid duplicate code
         iSize = 0;
         frontNode = NULL;
         backNode = NULL;

         for (ListIterator <T> it = rhs.begin(); it != NULL; ++it)
         {
            push_back(*it);
         }

         return *this; // ????????
      }

      // test whether the list is empty
      bool empty() const { return (iSize == 0);  }

      // returns the number of nodes in the list
      int size() const { return iSize; }

      // empty the list of all items
      void clear() { 
         iSize = 0; 
          
         for (ListIterator <T> it = begin(); it != NULL; ++it)
         {
            remove(it);
         }

         frontNode = NULL;
         backNode = NULL; 
      } 

      // adds an item to the back of the list
      void push_back(const T & value)
      {
         try
         {

            _insert(value,backNode,false,true);

         }
         catch (bad_alloc)
         {
            throw "ERROR: unable to allocate a new node for a list";
         }
      }

      // adds an item to the front of the list
      void push_front(const T & value)
      {
         try
         {
            _insert(value,frontNode,true,false);

         }
         catch (bad_alloc)
         {
            throw "ERROR: unable to allocate a new node for a list";
         }
      }

      

      // returns the item currently at the front of the list
      T & front() throw (const char *)
      {
         if ( frontNode != NULL && !empty())
         {
            return frontNode->data;   
         }
         else
         {
            throw "ERROR: unable to access data from an empty list";
         }
      }

      // returns the item currently at the back of the list
      T & back() throw (const char *)
      {
         if ( backNode != NULL && !empty() )
         {
            return backNode->data;   
         }
         else
         {
            throw "ERROR: unable to access data from an empty list";
         }
         
      }

      // inserts an item in the middle of a list
      ListIterator<T> insert(ListIterator<T> & pos, const T & value)
      {

         _insert(value,pos.p->pPrev,(pos == begin()),(pos == end()));

         return pos;
      }

      // removes an item from the middle of the list
      void remove(ListIterator<T> & pos)
      {
         Node <T> * position = pos.p;

         if ( position->pNext != NULL){
            position->pNext->pPrev = position->pPrev;
         
         }
         else
         {
            //if null, then is the last element
            backNode = position->pPrev;  
         }
         
         if ( position->pPrev != NULL){
            position->pPrev->pNext = position->pNext;
         }
         else
         {
            //if null, then is the first element
            frontNode = position->pNext;
         }

         delete position;
         position = NULL;
      }

      // returns an iterator to the first element in the list
      ListIterator<T> begin() const
      { 
         if ( frontNode != NULL )
         {
            return ListIterator<T>(frontNode);   
         }
         else
         {
            return NULL;
         }
         
      } 

      // returns an iterator referring to the past-the-end element in the list
      ListIterator<T> end() const 
      { 
      
         Node<T> * last = backNode;

         if ( backNode != NULL )
         {
            last = backNode->pNext;
         }

         return ListIterator<T>(last);
      } 


      // returns an iterator to the last element in the list
      ListIterator<T> rbegin() const 
      {          
         if ( backNode != NULL )
         {
            return ListIterator<T>(backNode);   
         }
         else
         {
            return NULL;
         }
      } 
      
      // returns an iterator referring to the past-the-front element in the list 
      ListIterator<T> rend() const 
      { 
      
         Node<T> * first = frontNode;

         if ( frontNode != NULL )
         {
            first = frontNode->pPrev;
         }

         return ListIterator<T>(first);
      } 

      friend ostream& operator << (ostream &out, const List<T>& rhs);

      ostream& display(ostream &out)
      {
          // while we have data
         for (ListIterator <T> it = begin(); it != NULL; ++it)
         {
            ListIterator <T> tmp = it;
            out << *tmp; // display data
            ++tmp;

            if (tmp != NULL) // if not the end of list
            {
               out << ","; // separate data with commas
            }
         }

         return out;
      }

  private:
      //internal size control
      int iSize;      
      //Pointer to the front 
      Node<T> * frontNode;
      //Pointer to the back 
      Node<T> * backNode;

   /***************************************************
    * NODE :: INSERT TO NEW LIST
    * Insert a new node to head of a new linked list
    **************************************************/
   Node<T> * insertToNewList(T data)
   {
      // allocate the node
      Node<T> * pNew = new Node<T>;

      // set the data member variable
      pNew->data = data;

      // there is no data after
      pNew->pNext = NULL;

      // pNew is the new head
      frontNode = pNew;
      // pNew is the new back
      backNode = pNew;
      
      return pNew;
   }

   /***************************************************
    * NODE :: INSERT TO HEAD
    * Insert a new node to head of the current linked list
    **************************************************/
   Node<T> * insertToHead(T data)
   {
      // allocate the node
      Node<T> * pNew = new Node<T>;

      // set the data member variable
      pNew->data = data;

      // put frontNode in line after the new node
      pNew->pNext = frontNode;
      frontNode->pPrev = pNew;

      //is the first element there is no prev
      pNew->pPrev = NULL;

      // pNew is the new head
      frontNode = pNew;

      return pNew;
   }

   /***************************************************
    * NODE :: INSERT TO BACK
    * Insert a new node to the end of the current linked list
    **************************************************/
   Node<T> * insertToBack(T data)
   {
      // allocate the node
      Node<T> * pNew = new Node<T>;

      // set the data member variable
      pNew->data = data;

      // link to the last element
      pNew->pPrev = backNode;
      backNode->pNext = pNew;

      //Now is the last element there is no next
      pNew->pNext = NULL;

      // pNew is the new head
      backNode = pNew;

      return pNew;
   }

   /***************************************************
    * NODE :: INSERT TO MIDDLE
    * Insert a new node to middle of the current linked list
    **************************************************/
   Node<T> * insertToMiddle(T data, Node<T> * pPrevious)
   {
      // allocate the node
      Node<T> * pNew = new Node<T>;

      // set the data member variable
      pNew->data = data;

      // assign the pNext pointer from pNew to the spot after it in the list
      pNew->pNext = pPrevious->pNext;
      // assign pPrev to the previous element
      pNew->pPrev = pPrevious;

      // point the next element prev oointer to the new element
      if ( pPrevious->pNext != NULL )
      {
         pPrevious->pNext->pPrev = pNew;  
      }

      // get pNode->pNext to point to pNew instead of the old node
      pPrevious->pNext = pNew;

      return pNew;
   }

   /***************************************************
    * NODE :: INSERT IN ORDER
    * Insert a new node into the current linked list
    * and sort it
    **************************************************/
   Node<T> *  insertInOrder(T data, Node<T> * & pPrevious)
   {
      // allocate the node
      Node<T> * pNew = new Node<T>;
      // set the data member variable
      pNew->data = data;
      // set temporarely the next to NULL
      pNew->pNext = NULL;

      Node<T> * current = pPrevious;

      // Special case for the head end
      if (pPrevious == NULL || pPrevious->data >= data) // if this is the case,
      {
         pNew->pNext = pPrevious;                       // switch pNew and pPrevious
         pPrevious = pNew;
      }
      else
      {
         // Locate the node before the point of insertion
         while (current->pNext != NULL &&            // if not end of linked list
                current->pNext->data < pNew->data)    // or this is the case
         {
            current = current->pNext; // find current which is bigger than new
         }
         // assign the pNext point from pNew to the spot after it in the list
         pNew->pNext = current->pNext;
         // get current->pNext to point to pNew instead of old node
         current->pNext = pNew;
      }

      return pNew;
   }


   /***************************************************
    * NODE :: INSERT
    * Insert a new node into the current linked list
    **************************************************/
   Node<T> * _insert(T data, Node<T> * & pHead, bool front = false, bool back = false) // default conditions
   {                                             // not front and not sorted unless specified
      Node<T> * newNode = new Node<T>;
      if (frontNode == NULL && backNode == NULL) // if linked list is empty
      {
         newNode = insertToNewList(data);
      }
      else if (!front && !back) // if we need to insert to middle/end without sorting
      {
         newNode = insertToMiddle(data, pHead);
      }
      else if (back) // if we need to insert to the back
      {
         newNode = insertToBack(data);
      }
      else // if we need to insert to the head of the linked list
      {
         newNode = insertToHead(data);
      }

      // Increase size
      iSize++;

      if (iSize == 1)
      {
         //if size is equal to 1, then both points to the node
         frontNode = newNode;
         backNode  = newNode;
      }

      return newNode;
   }
};

// Display the contents of a given linked list
template <class T>
//ostream & operator << (ostream & out, const List<T> * rhs)
ostream& operator << (ostream &out, const List<T>& rhs)
{

    // while we have data
   for (ListIterator <T> it = rhs->begin(); it != NULL; ++it)
   {
      ListIterator <T> tmp = it;
      out << "data:" <<*it.data; // display data
      ++tmp;

      if (tmp != NULL) // if not the end of list
      {
         out << ","; // separate data with commas
      }
   }

   return out;
}

/**************************************************
 * List ITERATOR
 * An iterator through SET
 *************************************************/
template <class T>
class ListIterator 
{
   template<class C>
   friend class List;
   
   public:
      // default constructor
      ListIterator() : p(NULL) {}

      // initialize to direct p to some item
      ListIterator(Node<T> * p) : p(p) {}

      // copy constructor
      ListIterator(const ListIterator & rhs) { *this = rhs; }

      // assignment operator
      ListIterator & operator = (const ListIterator & rhs)
      {
         this->p = rhs.p;
         return *this;
      }

      // equals operator
      bool operator == (const ListIterator & rhs) const
      {
         return (rhs.p == this->p);
      }

      // not equals operator
      bool operator != (const ListIterator & rhs) const
      {
         return (rhs.p != this->p);
      }

      // dereference operator
      T & operator * ()
      {
         return p->data;
      }

      // prefix increment
      ListIterator <T> & operator++  ()
      {
        if ( p != NULL )
        {
            p = p->pNext; 
        }
        
        return *this;

      }

      // postfix increment
      ListIterator <T> operator ++ (int postfix)
      {
        ListIterator tmp(*this);
        if ( p != NULL )
        {
            p = p->pNext; 
        }
        return tmp;
      }

      // prefix decrement
      ListIterator <T> & operator -- ()
      {
         p = p->pPrev;
         return *this;
      }

      // postfix decrement
      ListIterator <T> operator -- (int postfix)
      {
         ListIterator tmp(*this);
         p = p->pPrev;
         return tmp;
      }



   private:

      Node<T> * p;

};


/**************************************************
 * List Const ITERATOR
 * An iterator through SET
 *************************************************/
template <class T>
class ListConstIterator 
{
   template<class C>
   friend class List;
   
   public:
      // default constructor
      ListConstIterator() : p(NULL) {}

      // initialize to direct p to some item
      ListConstIterator(Node<T> * p) : p(p) {}

      // copy constructor
      ListConstIterator(const ListConstIterator & rhs) { *this = rhs; }

      // assignment operator
      ListConstIterator & operator = (const ListConstIterator & rhs)
      {
         this->p = rhs.p;
         return *this;
      }

      // equals operator
      bool operator == (const ListConstIterator & rhs) const
      {
         return (rhs.p == this->p);
      }

      // not equals operator
      bool operator != (const ListConstIterator & rhs) const
      {
         return (rhs.p != this->p);
      }

      // dereference operator
      T & operator * ()
      {
         return p->data;
      }

      // prefix increment
      ListConstIterator <T> & operator++  ()
      {
        if ( p != NULL )
        {
            p = p->pNext; 
        }
        
        return *this;

      }

      // postfix increment
      ListConstIterator <T> operator ++ (int postfix)
      {
        ListConstIterator tmp(*this);
        if ( p != NULL )
        {
            p = p->pNext; 
        }
        return tmp;
      }

      // prefix decrement
      ListConstIterator <T> & operator -- ()
      {
         p = p->pPrev;
         return *this;
      }

      // postfix decrement
      ListConstIterator <T> operator -- (int postfix)
      {
         ListConstIterator tmp(*this);
         p = p->pPrev;
         return tmp;
      }



   private:

      Node<T> * p;

};
#endif // LIST_H