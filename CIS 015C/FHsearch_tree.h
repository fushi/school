// File FHsearch_tree.h
// Template definitions for FHsearch_trees, which are general trees

#include <stdlib.h>

#ifndef FHSEARCHTREE_H
#define FHSEARCHTREE_H

// ---------------------- FHs_treeNode Prototype --------------------------
template <class Comparable>
class FHs_treeNode
{
public:
   FHs_treeNode( const Comparable & d = Comparable(), 
      FHs_treeNode *lt = NULL, 
      FHs_treeNode *rt = NULL)
      : l_child(lt), r_child(rt), data(d)
   { }

   FHs_treeNode *l_child, *r_child;
   Comparable data;

   // for use only with AVL Trees
   virtual int getHeight() const { return 0; }
   virtual bool setHeight(int height) { return true; }
}; 

// ---------------------- FHsearch_tree Prototype --------------------------
template <class Comparable>
class FHsearch_tree
{
protected:
   int m_size;
   FHs_treeNode<Comparable> *m_root;

public:
   FHsearch_tree() { m_size = 0; m_root = NULL; }
   FHsearch_tree(const FHsearch_tree &rhs) 
      { m_root = NULL; m_size = 0; *this = rhs; }
   ~FHsearch_tree() { clear(); }

   const Comparable &findMin() const;
   const Comparable &findMax() const;
   const Comparable &find(const Comparable &x) const;

   bool empty() const { return (m_size == 0); }
   int size() const { return m_size; }
   void clear() { make_empty(m_root); }
   const FHsearch_tree & operator=(const FHsearch_tree &rhs);

   bool insert(const Comparable &x);
   bool remove(const Comparable &x);
   bool contains(const Comparable &x) const { return find(m_root, x) != NULL; }

   template <class Processor>
   void traverse(Processor func) const { traverse(m_root, func); }
   int showHeight() const { return findHeight(m_root); }

protected:
   FHs_treeNode<Comparable> *clone( FHs_treeNode<Comparable> *root) const;
   FHs_treeNode<Comparable> *findMin(FHs_treeNode<Comparable> *root) const;
   FHs_treeNode<Comparable> *findMax(FHs_treeNode<Comparable> *root) const;
   FHs_treeNode<Comparable> *find(FHs_treeNode<Comparable> *root,
      const Comparable &x) const;
   bool insert(FHs_treeNode<Comparable> * &root,
      const Comparable &x);
   bool remove(FHs_treeNode<Comparable> * &root, const Comparable &x);
   void make_empty(FHs_treeNode<Comparable> * &subtree_to_delete);
   template <class Processor>
   void traverse(FHs_treeNode<Comparable> *tree_node, 
      Processor func, int level = -1) const;
   int findHeight(FHs_treeNode<Comparable> *tree_node, int height = -1) const;
   
public:
   // for exception throwing
   class EmptyTreeException {};
   class NotFoundException {};
};

// FHsearch_tree public method definitions -----------------------------
template <class Comparable>
const Comparable & FHsearch_tree<Comparable>::findMin() const
{
   if (m_root == NULL)
      throw EmptyTreeException();
   return findMin(m_root)->data;
}

template <class Comparable>
const Comparable & FHsearch_tree<Comparable>::findMax() const
{
   if (m_root == NULL)
      throw EmptyTreeException();
   return findMax(m_root)->data;
}

template <class Comparable>
const Comparable &FHsearch_tree<Comparable>::find(
   const Comparable &x) const
{ 
   FHs_treeNode<Comparable> *result_node;
   
   result_node = find(m_root, x);
   if (result_node == NULL)
      throw NotFoundException();
    return result_node->data;
}

template <class Comparable>
const FHsearch_tree<Comparable> &FHsearch_tree<Comparable>::operator=
   (const FHsearch_tree &rhs)
{
   if (&rhs != this) 
   {
      clear();
      m_root = clone(rhs.m_root);
      m_size = rhs.size();
   }
   return *this;
}

template <class Comparable>
bool FHsearch_tree<Comparable>::insert(const Comparable &x)
{
   if (insert(m_root, x))
   {
      m_size++;
      return true;
   }
   return false;
}

template <class Comparable>
bool FHsearch_tree<Comparable>::remove(const Comparable &x)
{
   if (remove(m_root, x))
   {
      m_size--;
      return true;
   }
   return false;
}

template <class Comparable>
template <class Processor>
void FHsearch_tree<Comparable>::traverse( FHs_treeNode<Comparable> *tree_node,
   Processor func, int level) const
{
   if (tree_node == NULL)
      return;
   // we're not doing anything with level but its there in case we want it
   traverse(tree_node->l_child, func, level + 1);
   func(tree_node->data);
   traverse(tree_node->r_child, func, level + 1);
}


// FHsearch_tree private method definitions -----------------------------
template <class Comparable>
FHs_treeNode<Comparable> *FHsearch_tree<Comparable>::clone(
   FHs_treeNode<Comparable> *root) const
{
   FHs_treeNode<Comparable> *new_node;
   if (root == NULL)
      return NULL;

   new_node =  new FHs_treeNode<Comparable>(
      root->data, 
      clone(root->l_child), clone(root->r_child));
   return new_node;
}

template <class Comparable>
FHs_treeNode<Comparable> *FHsearch_tree<Comparable>::findMin(
   FHs_treeNode<Comparable> *root) const
{
   if (root == NULL)
      return NULL;
   if (root->l_child == NULL)
      return root;
   return findMin(root->l_child);
}

template <class Comparable>
FHs_treeNode<Comparable> *FHsearch_tree<Comparable>::findMax(
   FHs_treeNode<Comparable> *root) const
{
   if (root == NULL)
      return NULL;
   if (root->r_child == NULL)
      return root;
   return findMax(root->r_child);
}

template <class Comparable>
FHs_treeNode<Comparable>* FHsearch_tree<Comparable>::find(
   FHs_treeNode<Comparable> *root, const Comparable &x) const
{
   if (root == NULL)
      return NULL;

   if (x < root->data)
      return find(root->l_child, x);
   if (root->data < x)
      return find(root->r_child, x);
   return root;
}

template <class Comparable>
bool FHsearch_tree<Comparable>::insert(
   FHs_treeNode<Comparable> * &root, const Comparable &x)
{
   if (root == NULL)
   {
      root = new FHs_treeNode<Comparable>(x, NULL, NULL);
      return true;
   }
   else if (x < root->data)
      return insert(root->l_child, x);
   else if (root->data < x)
      return insert(root->r_child, x);

   return false; // duplicate
}

template <class Comparable>
bool FHsearch_tree<Comparable>::remove(
   FHs_treeNode<Comparable> * &root, const Comparable &x)
{
   if (root == NULL)
      return false;

   if (x < root->data)
      return remove(root->l_child, x);
   if (root->data < x)
      return remove(root->r_child, x);

   // found the node
   if (root->l_child != NULL && root->r_child != NULL)
   {
      FHs_treeNode<Comparable> *min_node = findMin(root->r_child);
      root->data = min_node->data;
      remove(root->r_child, min_node->data);
   }
   else
   {
      FHs_treeNode<Comparable> *node_to_remove = root;
      root = (root->l_child != NULL)? root->l_child : root->r_child;
      delete node_to_remove;
   }
   return true;
}

template <class Comparable>
void FHsearch_tree<Comparable>::make_empty(
   FHs_treeNode<Comparable> * &subtree_to_delete)
{
   if (subtree_to_delete == NULL)
      return;

   // remove children
   make_empty(subtree_to_delete->l_child);
   make_empty(subtree_to_delete->r_child);

   // clear client's pointer
   delete subtree_to_delete;
   subtree_to_delete = NULL;
   --m_size;
}

template <class Comparable>
int FHsearch_tree<Comparable>::findHeight( FHs_treeNode<Comparable> *tree_node,
   int height ) const
{
   int left_height, right_height;

   if (tree_node == NULL)
      return height;
   height++;
   left_height = findHeight(tree_node->l_child, height);
   right_height = findHeight(tree_node->r_child, height);
   return (left_height > right_height)? left_height : right_height;
}
#endif