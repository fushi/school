// File FHtree.h
// Template definitions for FHtrees, which are general trees
#ifndef FHTREE_H
#define FHTREE_H
#include <string>

// advanced prototype for the FHtreeNode to use to declare a friend
template <class Object>
class FHtree;

// ---------------------- FHtreeNode Prototype --------------------------
template <class Object>
class FHtreeNode
{
   friend class FHtree<Object>;

private: 
   FHtreeNode *first_child, *sib, *prev;
   Object data;
   const FHtreeNode *my_root;  // needed to test for certain error

public:
   FHtreeNode( const Object & d = Object(), 
      FHtreeNode *sb = NULL, FHtreeNode *chld = NULL, FHtreeNode *prv = NULL )
      : first_child(chld), sib(sb), prev(prv), data(d), my_root(NULL)
   { }
   Object GetData() const { return data; }

private:
   // for use only by FHtree
   FHtreeNode( const Object & d, 
      FHtreeNode *sb, FHtreeNode *chld, FHtreeNode *prv,
      const FHtreeNode *root )
      : first_child(chld), sib(sb), prev(prv), data(d), my_root(root)
   { }
}; 
// ---------------------- FHtree Prototype --------------------------
template <class Object>
class FHtree
{
private:
   int m_size;
   FHtreeNode<Object> *m_root;

public:
   FHtree() { m_size = 0; m_root = NULL; }
   FHtree(const FHtree &rhs) { m_root = NULL; m_size = 0; *this = rhs; }
   ~FHtree() { clear(); }
   bool empty() const { return (m_size == 0); }
   int size() const { return m_size; }
   void clear() { remove_node(m_root); }
   const FHtree & operator=(const FHtree &rhs);

   FHtreeNode<Object> *add_child( FHtreeNode<Object> *tree_node, const Object &x );

   FHtreeNode<Object> *find(const Object &x) { return find(m_root, x); }
   FHtreeNode<Object> *find(FHtreeNode<Object> *root, 
      const Object &x, int level = 0);
   const FHtreeNode<Object> *find(const Object &x) const { return find(m_root, x); }
   const FHtreeNode<Object> *find(const FHtreeNode<Object> *root, 
      const Object &x, int level = 0) const;

   bool remove(const Object &x) { return remove(m_root, x); }
   bool remove(FHtreeNode<Object> *root, const Object &x);
   void remove_node(FHtreeNode<Object> *node_to_delete);   

   void display(FHtreeNode<Object> *tree_node = NULL, int level = 0) const;

   template <class Processor>
   void traverse(Processor func, FHtreeNode<Object> *tree_node = NULL) const;

private:
   FHtreeNode<Object> *clone( FHtreeNode<Object> *root) const;
   void set_my_roots(FHtreeNode<Object> *tree_node);
};

// public interface methods of FHtree ------------------------
template <class Object>
const FHtreeNode<Object>* FHtree<Object>::find(const FHtreeNode<Object> *root,
   const Object &x, int level) const
{
   const FHtreeNode<Object> *retval;

   if (m_size == 0 || root == NULL)
      return NULL;

   if (root->data == x)
      return root;

   // otherwise, recurse.  don't process sibs if this was the original call
   if ( level > 0 && (retval = find(root->sib, x, level)))
      return retval;
   return find(root->first_child, x, ++level);
}

template <class Object>
FHtreeNode<Object>* FHtree<Object>::find(FHtreeNode<Object> *root, 
   const Object &x, int level)
{
   FHtreeNode<Object> *retval;
 
   if (m_size == 0 || root == NULL)
      return NULL;

   if (root->data == x)
      return root;

   // otherwise, recurse.  don't process sibs if this was the original call
   if ( level > 0 && (retval = find(root->sib, x, level)))
      return retval;
   return find(root->first_child, x, ++level);
}

template <class Object>
bool FHtree<Object>::remove(FHtreeNode<Object> *root, const Object &x)
{
   FHtreeNode<Object> *tn = NULL;

   if (m_size == 0 || root == NULL)
      return false;
  
   if ( (tn = find(root, x)) != NULL )
   {
      remove_node(tn);
      return true;
   }
   return false;
}

template <class Object>
const FHtree<Object> &FHtree<Object>::operator=
   (const FHtree &rhs)
{
   if (&rhs != this) 
   {
      clear();
      m_root = clone(rhs.m_root);
      m_size = rhs.m_size;
      set_my_roots(m_root);
   }
   return *this;
}

template <class Object>
void FHtree<Object>::remove_node(FHtreeNode<Object> *node_to_delete)
{
   if (node_to_delete == NULL || m_root == NULL)
      return;
   if (node_to_delete->my_root != m_root)
      return;  // silent error, node does not belong to this tree

   // remove all the children of this node
   while (node_to_delete->first_child)
      remove_node(node_to_delete->first_child);

   if (node_to_delete->prev == NULL)
      m_root = NULL;  // last node in tree
   else if (node_to_delete->prev->sib == node_to_delete)
      node_to_delete->prev->sib = node_to_delete->sib; // adjust left sibling
   else
      node_to_delete->prev->first_child = node_to_delete->sib;  // adjust parent

   // adjust the successor sub's prev pointer
   if (node_to_delete->sib != NULL)
      node_to_delete->sib->prev = node_to_delete->prev;

   delete node_to_delete;
  --m_size;
}

template <class Object>
FHtreeNode<Object> *FHtree<Object>::add_child( 
   FHtreeNode<Object> *tree_node, const Object &x )
{
   // empty tree? - create a root node if user passes in NULL
   if (m_size == 0)
   {
      if (tree_node != NULL)
         return NULL; // silent error something's fishy.  tree_node can't right
      m_root = new FHtreeNode<Object>(x, NULL, NULL, NULL);
      m_root->my_root = m_root;
      m_size = 1;
      return m_root;
   }
   if (tree_node == NULL)
      return NULL; // silent error inserting into a non_null tree with a null parent
   if (tree_node->my_root != m_root)
      return NULL;  // silent error, node does not belong to this tree

   // push this node into the head of the sibling list; adjust prev pointers
   FHtreeNode<Object> *new_node = new FHtreeNode<Object>(x, 
      tree_node->first_child, NULL, tree_node, m_root);  // sib, child, prev, root
   tree_node->first_child = new_node;
   if (new_node->sib != NULL)
      new_node->sib->prev = new_node;
   ++m_size;
   return new_node;
}

template <class Object>
void FHtree<Object>::display(FHtreeNode<Object> *tree_node, int level) const
{
   FHtreeNode<Object> *child;

   // this will be static and so will be shared by all calls
   static string blank_string = "                                    ";
   string indent;

   // stop runaway indentation/recursion
   if  (level > (int)blank_string.length() - 1)
   {
      cout << blank_string << " ... " << endl;
      return;
   }

   indent = blank_string.substr(0, level);

   if (m_root == NULL)
      return;
   if (tree_node == NULL)
   {
      display(m_root);
      return;
   }

   cout << indent << tree_node->data  << endl;
   for (child = tree_node->first_child; child != NULL; child = child->sib)
      display(child, level+1);
}

template <class Object>
template <class Processor>
void FHtree<Object>::traverse(Processor func, FHtreeNode<Object> *tree_node) const
{
   FHtreeNode<Object> *child;

   if (m_root == NULL)
      return;
   if (tree_node == NULL)
   {
      traverse(func, m_root);
      return;
   }

   func(tree_node->data);

   for (child = tree_node->first_child; child != NULL; child = child->sib)
      traverse(func, child);
}

// FHsearch_tree private method definitions -----------------------------
template <class Object>
FHtreeNode<Object> *FHtree<Object>::clone(
   FHtreeNode<Object> *root) const
{
   FHtreeNode<Object> *new_node;
   if (root == NULL)
      return NULL;

   // does not set my_root which must be done by caller
   new_node = new FHtreeNode<Object>(
      root->data, 
      clone(root->sib), clone(root->first_child));
   if (new_node->sib)
      new_node->sib->prev = new_node;
   if (new_node->first_child)
      new_node->first_child->prev = new_node;
   return new_node;
}

template <class Object>
void FHtree<Object>::set_my_roots(FHtreeNode<Object> *tree_node)
{
   FHtreeNode<Object> *child;

   if (m_root == NULL)
      return;

   tree_node->my_root = m_root;
   for (child = tree_node->first_child; child != NULL; child = child->sib)
      set_my_roots(child);
}

#endif