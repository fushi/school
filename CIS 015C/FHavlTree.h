// File FHavlTree.h
// Template definitions for FHavlTrees.  
#ifndef FHAVLTREE_H
#define FHAVLTREE_H
#include "FHsearch_tree.h"

// ---------------------- AvlNode --------------------------
template <class Comparable>
class AvlNode : public FHs_treeNode<Comparable>
{
public: 
   AvlNode(const Comparable &d, AvlNode *l_child, AvlNode *r_child, int ht = 0)
      : FHs_treeNode<Comparable>(d, l_child, r_child), height(ht)
   { }

   int height;

   int getHeight() const { return height; }
   bool setHeight(int height);
};

template <class Comparable>
bool AvlNode<Comparable>::setHeight(int height) 
{
   if (height < -1) 
      return false;
   this->height = height;
   return true;
}

// ---------------------- FHavlTree Prototype --------------------------
template <class Comparable>
class FHavlTree : public FHsearch_tree<Comparable>
{
public:
   // we need our own copy constructor and op= because of height info
   FHavlTree(const FHavlTree &rhs) 
      { this->m_root = NULL; this->m_size = 0; *this = rhs; }

   // need a default because above hides it.  Simply chain to base class
   FHavlTree() : FHsearch_tree<Comparable>() { }

   const FHavlTree & operator=(const FHavlTree &rhs);

   // override base class insert/remove
   bool insert(const Comparable &x);
   bool remove(const Comparable &x);

   // a fun and informative touch
   int showHeight() const { return heightOf(this->m_root); }

protected:
   // static because the node whose height we want might be null
   static int heightOf(FHs_treeNode<Comparable> *t)
      { return t == NULL? -1 : t->getHeight(); }
   AvlNode<Comparable> *clone( FHs_treeNode<Comparable> *root) const;

   bool insert( const Comparable & x, FHs_treeNode<Comparable> * & root );
   bool remove( const Comparable & x, FHs_treeNode<Comparable> * & root );
   void rotateWithLeftChild( FHs_treeNode<Comparable> * & k2 );
   void doubleWithLeftChild( FHs_treeNode<Comparable> * & k3 );
   void rotateWithRightChild( FHs_treeNode<Comparable> * & k2 );
   void doubleWithRightChild( FHs_treeNode<Comparable> * & k3 );
   int max(int a, int b) { return (a < b)? b : a ; }
};

// FHavlTree method definitions -------------------
// private utilities for member methods
template <class Comparable>
bool FHavlTree<Comparable>::insert( const Comparable & x, 
   FHs_treeNode<Comparable> * & root )
{
   if( root == NULL )
   {
      // found a place to hang new node
      root = new AvlNode<Comparable>(x, NULL, NULL, 0);
      return true;
   }
   else if( x < root->data )
   {
      if ( !insert(x, root->l_child) )
         return false;
      if(heightOf(root->l_child) - heightOf(root->r_child) == 2)
         if( x < root->l_child->data )
            rotateWithLeftChild(root);
         else
            doubleWithLeftChild(root);
   }
   else if(root->data < x)
   {
      if ( !insert(x, root->r_child) )
         return false;
      if(heightOf(root->r_child) - heightOf(root->l_child) == 2)
         if(root->r_child->data < x)
            rotateWithRightChild(root);
         else
            doubleWithRightChild(root);
   }
   else
      return false;

   // successfully inserted at this or lower level; adjust height
   root->setHeight( max(heightOf(root->l_child), heightOf(root->r_child)) + 1);
   return true;
}

template <class Comparable>
bool FHavlTree<Comparable>::remove( const Comparable & x, 
   FHs_treeNode<Comparable> * & root )
{
   if (root == NULL)
      return false;

   if (x < root->data)
   {
      if ( !remove(x, root->l_child) )
         return false;

      // rebalance - shortened left branch so right may now be higher by 2
      if(heightOf(root->r_child) - heightOf(root->l_child) == 2)
         if(heightOf(root->r_child->r_child) < heightOf(root->r_child->l_child))
            doubleWithRightChild(root);
         else
            rotateWithRightChild(root);
   }
   else if (root->data < x)
   {
      if ( !remove(x, root->r_child) )
         return false;

      // rebalance - shortened right branch so left may now be higher by 2
      if(heightOf(root->l_child) - heightOf(root->r_child) == 2)
         if(heightOf(root->l_child->l_child) < heightOf(root->l_child->r_child))
            doubleWithLeftChild(root);
         else
            rotateWithLeftChild(root);
   }

   // found the node
   else if (root->l_child != NULL && root->r_child != NULL)
   {
      // first simply copy min right data into the node marked for deletion
      FHs_treeNode<Comparable> *min_node = findMin(root->r_child);
      root->data = min_node->data;

      // now  do a real deletion:  the old min is still in the right sub-tree
      remove(min_node->data, root->r_child);

      // rebalance - shortened right branch so left may now be higher by 2
      if(heightOf(root->l_child) - heightOf(root->r_child) == 2)
         if(heightOf(root->l_child->l_child) < heightOf(root->l_child->r_child))
            doubleWithLeftChild(root);
         else
            rotateWithLeftChild(root);
   }
   else
   {
      // no rebalancing needed at this external (1+ NULL children) node
      FHs_treeNode<Comparable> *node_to_remove = root;
      root = (root->l_child != NULL)? root->l_child : root->r_child;
      delete node_to_remove;
      return true;

   }
   // successfully removed and rebalanced at this and lower levels; 
   // now adjust height
   root->setHeight(max(heightOf(root->l_child), heightOf(root->r_child)) + 1);
   return true;
}

template <class Comparable>
void FHavlTree<Comparable>::rotateWithLeftChild( 
   FHs_treeNode<Comparable> * & k2 )
{
   FHs_treeNode<Comparable> *k1 = k2->l_child;
   k2->l_child = k1->r_child;
   k1->r_child = k2;
   k2->setHeight( max( heightOf(k2->l_child),  heightOf(k2->r_child) ) + 1 );
   k1->setHeight( max( heightOf(k1->l_child),  k2->getHeight() ) + 1 );
   k2 = k1;
}

template <class Comparable>
void FHavlTree<Comparable>::doubleWithLeftChild( 
   FHs_treeNode<Comparable> * & k3 )
{
   rotateWithRightChild(k3->l_child);
   rotateWithLeftChild(k3);
}

template <class Comparable>
void FHavlTree<Comparable>::rotateWithRightChild( 
   FHs_treeNode<Comparable> * & k2 )
{
   FHs_treeNode<Comparable> *k1 = k2->r_child;
   k2->r_child = k1->l_child;
   k1->l_child = k2;
   k2->setHeight( max( heightOf(k2->l_child), heightOf(k2->r_child) ) + 1 );
   k1->setHeight( max( heightOf(k1->r_child), k2->getHeight() ) + 1 );
   k2 = k1;
}

template <class Comparable>
void FHavlTree<Comparable>::doubleWithRightChild( 
   FHs_treeNode<Comparable> * & k3 )
{
   rotateWithLeftChild(k3->r_child);
   rotateWithRightChild(k3);
}

// FHsearch_tree private method definitions -----------------------------
template <class Comparable>
AvlNode<Comparable> *FHavlTree<Comparable>::clone(
   FHs_treeNode<Comparable> *root) const
{
   AvlNode<Comparable> *new_node;
   if (root == NULL)
      return NULL;

   new_node =  new AvlNode<Comparable>(
      root->data, 
      clone(root->l_child), clone(root->r_child), root->getHeight());
   return new_node;
}

// public interface
template <class Comparable>
bool FHavlTree<Comparable>::insert( const Comparable &x )
{
   if (insert(x, this->m_root))
   {
      this->m_size++;
      return true;
   }
   return false;
}

template <class Comparable>
bool FHavlTree<Comparable>::remove( const Comparable &x )
{

   if (remove(x, this->m_root))
   {
      this->m_size--;
      return true;
   }
   return false;
}

template <class Comparable>
const FHavlTree<Comparable> &FHavlTree<Comparable>::operator=
   (const FHavlTree &rhs)
{
   if (&rhs != this) 
   {
      this->clear();
      this->m_root = clone(rhs.m_root);
      this->m_size = rhs.size();
   }
   return *this;
}
#endif