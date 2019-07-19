/***********************************************************************
* Header:
*    Node
*
* Author:
*    Nimesh Subedi
************************************************************************/
#ifndef NODE_H
#define NODE_H

#include <iostream>
using namespace std;

/************************************************
 * NODE
 * A class that holds node
 ***********************************************/
template <class T>
class Node
{
  public:
   Node() : pNext(NULL) {}
	Node(const T & t)
	{ 
		data = t; pNext = NULL;
	}

   T data;
   Node<T> * pNext;
};

/***************************************************
* NODE :: COPY
**************************************************/
template <class T>
Node<T> * copy(Node<T> * pNode)
{
 
   Node<T> * pNew = NULL;
   if ( pNode != NULL )
   {
      insert(pNode->data, pNew, true);
      pNode = pNode->pNext;
   }
   Node<T> * ptr = pNew;
   while (pNode)
   {
      insert(pNode->data,pNew);
      pNode = pNode->pNext;
      pNew = pNew->pNext;
   }
   return ptr;
}

/***************************************************
* NODE :: INSERT
**************************************************/
template <class T>
void insert(T data, Node<T> * & afterMe, bool front = false)
{
	Node<T> * pNew = new Node<T>;
	pNew->data = data;
   
   if (afterMe == NULL)
   {   
	   pNew->pNext = NULL;
	   afterMe = pNew;
	}
   else if (!front)
	{
	   pNew->pNext = afterMe->pNext;
	   afterMe->pNext = pNew;
	}
   else
	{
   	pNew->pNext = afterMe;
   	afterMe = pNew;
	}
}

/***************************************************
* NODE :: FIND
**************************************************/
template <class T>
Node<T> * find(Node<T> * pHead, T data)
{
	if(pHead)
	{
		if(pHead->data == data)
		{
			return pHead;
		}
		else
			return find(pHead->pNext, data);
	}
	else 
		return NULL;
}

/***************************************************
* NODE :: << OPERATOR
**************************************************/
template <class T>
ostream & operator << (ostream & display, const Node<T> * rhs)
{
   while (rhs){
      display << rhs->data;
      if (rhs->pNext != NULL)
      {
         display << ", ";
      }
      rhs = rhs->pNext;
   }
   return display;
}

/***************************************************
* NODE :: FREE DATA
**************************************************/
template <class T>
void freeData(Node<T> * & pHead)
{   
   if (pHead != NULL)
   {
      Node<T> * pNew = pHead->pNext;
      delete pHead;
      pHead = pNew;
      freeData(pHead);
   }
}

#endif // NODE_H