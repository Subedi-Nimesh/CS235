#ifndef BNODE_H
#define BNODE_H

#include <iostream> 
#include <cassert>

/*****************************************************************
 * BINARY NODE
 * A single node in a binary tree.  Note that the node does not know
 * anything about the properties of the tree so no validation can be done.
 *****************************************************************/
template <class T>
class BinaryNode
{
public:
   // return size (i.e. number of nodes in tree)
   int size() const
   {
            return 1 +
               (pLeft== NULL? 0 : pLeft->size()) +
               (pRight == NULL ? 0 : pRight->size());
   }
   
   // add a node to the left/right
   void addLeft (BinaryNode <T> * pNode) 
   {
   	pLeft = pNode;
   	if(pNode != NULL)
   		pNode->pParent = this;
   }
   void addRight(BinaryNode <T> * pNode)
   {
      pRight = pNode;
      if (pNode != NULL)
         pNode->pParent = this;
   }

   // create a node and add it to the left/right
   void addLeft (const T & t) throw (const char *)
   {
   	BinaryNode<T> * pNew;
      try {
      	pNew = new BinaryNode<T>;
      }
      catch (std::bad_alloc) {
      	throw "ERROR: Unable to allocate a node";
      }
      pNew->data = t;
      pLeft = pNew;
      if (pNew != NULL)
      {
      	pNew->pParent = this;
      }
   }
   void addRight(const T & t) throw (const char *)
   {
   	BinaryNode<T> * pNew;
      try {
         pNew = new BinaryNode<T>;
      }
      catch (std::bad_alloc) {
      	throw "ERROR: Unable to allocate a node";
      }
      pNew->data = t;
      pRight = pNew;
      if (pNew != NULL)
      {
      	pNew->pParent = this;
      }
   }
   
   // since no validation is done, everything is public
   BinaryNode <T> * pLeft;
   BinaryNode <T> * pRight;
   BinaryNode <T> * pParent;
   T data;

   BinaryNode() : pRight(NULL), pLeft(NULL), pParent(NULL) {}

   BinaryNode(const T & t) 
   {
      // declaration of default values
      data = t;
      pRight = NULL;
      pLeft = NULL;
      pParent = NULL;
   }
};

template <class T>
void deleteBinaryTree(BinaryNode<T> * & pNode)
{
	if(pNode->pLeft != NULL || pNode->pRight !=NULL)
	{
		if(pNode->pLeft != NULL)
		{
			deleteBinaryTree(pNode->pLeft);
		}

		if(pNode->pRight != NULL)
		{
			deleteBinaryTree(pNode->pRight);
		}
		delete pNode;
	}
}

template <class T> 
std::ostream & operator << (std::ostream & display, const BinaryNode<T> * rhs)
{
   if (rhs->pLeft != NULL)
      display << rhs->pLeft; 

   display << rhs->data << " ";

   if (rhs->pRight != NULL)
      display << rhs->pRight ;
   
   return display;
}

#endif // BNODE_H
