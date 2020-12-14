// File FHthreadedBST.h
// Template definitions for FHthreadedBSTs, which are general trees
#ifndef FHTHREADTREE_H
#define FHTHREADTREE_H

// --------------------- FHthreadedNode Prototype -------------------------
template <class Comparable>
class FHthreadedNode
{
public:
   FHthreadedNode( const Comparable & d = Comparable(), 
      FHthreadedNode *l = NULL, 
      FHthreadedNode *r = NULL,
      bool l_th = true,
      bool r_th = true,
      int ht = 0)
         : 
         l_child(l), r_child(r), data(d), 
         l_thread(l_th), r_thread(r_th), height(ht)
   { }

   FHthreadedNode *l_child, *r_child;
   Comparable data;
   bool l_thread, r_thread;
   int height;
}; 

// ---------------------- FHthreadedBST Prototype --------------------------
template <class Comparable>
class FHthreadedBST
{
protected:
   int m_size;
   FHthreadedNode<Comparable> *m_root;

public:
   FHthreadedBST() { m_size = 0; m_root = NULL; }
   FHthreadedBST(const FHthreadedBST &rhs) 
      { m_root = NULL; m_size = 0; *this = rhs; }
   ~FHthreadedBST() { clear(); }

   const Comparable &findMin() const;
   const Comparable &findMax() const;
   const Comparable &find(const Comparable &x) const;

   bool empty() const { return (m_size == 0); }
   int size() const { return m_size; }
   void clear() { make_empty(m_root); }
   const FHthreadedBST & operator=(const FHthreadedBST &rhs);

   bool insert(const Comparable &x);
   bool remove(const Comparable &x);
   bool contains(const Comparable &x) const { return find(m_root, x) != NULL; }

   template <class Processor>
   void traverse(Processor func) const;
   int showHeight() const { return findHeight(m_root); }

protected:
   void clone( FHthreadedNode<Comparable> *root, 
      FHthreadedBST<Comparable> &new_tree);
   FHthreadedNode<Comparable> *findMin(FHthreadedNode<Comparable> *root) const;
   FHthreadedNode<Comparable> *findMax(FHthreadedNode<Comparable> *root) const;
   FHthreadedNode<Comparable> *find(FHthreadedNode<Comparable> *root,
      const Comparable &x) const;
   bool remove(FHthreadedNode<Comparable> * &root, const Comparable &x);
   void make_empty(FHthreadedNode<Comparable> * &subtree_to_delete);
   int findHeight(FHthreadedNode<Comparable> *tree_node, int height = -1) const;
   void redirectThreadsPointingToMe(FHthreadedNode<Comparable> *node_to_remove);
   void adjustParentThreadFlags( FHthreadedNode<Comparable> *node_to_remove );

   static FHthreadedNode<Comparable> 
      *successor(FHthreadedNode<Comparable> *node);
   static FHthreadedNode<Comparable> 
      *predecessor(FHthreadedNode<Comparable> *node);

public:
   // for exception throwing
   class EmptyTreeException {};
   class NotFoundException {};
};

// FHthreadedBST public method definitions -----------------------------
template <class Comparable>
const Comparable & FHthreadedBST<Comparable>::findMin() const
{
   if (m_root == NULL)
      throw EmptyTreeException();
   return findMin(m_root)->data;
}

template <class Comparable>
const Comparable & FHthreadedBST<Comparable>::findMax() const
{
   if (m_root == NULL)
      throw EmptyTreeException();
   return findMax(m_root)->data;
}

template <class Comparable>
const Comparable &FHthreadedBST<Comparable>::find(
   const Comparable &x) const
{ 
   FHthreadedNode<Comparable> *result_node;
   
   result_node = find(m_root, x);
   if (result_node == NULL)
      throw NotFoundException();
    return result_node->data;
}

template <class Comparable>
const FHthreadedBST<Comparable> &FHthreadedBST<Comparable>::operator=
   (const FHthreadedBST &rhs)
{
   if (&rhs != this) 
   {
      clear();
      clone(rhs.m_root, *this);
   }
   return *this;
}

template <class Comparable>
bool FHthreadedBST<Comparable>::remove(const Comparable &x)
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
void FHthreadedBST<Comparable>::traverse( Processor func) const
{
   if (m_root == NULL)
      return;

   FHthreadedNode<Comparable> *node = findMin(m_root);
   do
   {
      func(node->data);
      node = successor(node);
   } while (node != NULL);
}


// FHthreadedBST private method definitions -----------------------------
template <class Comparable>
void FHthreadedBST<Comparable>::clone( FHthreadedNode<Comparable> *root,
   FHthreadedBST<Comparable> &new_tree )
{
   // to overcome complex threading, simply add node into a new tree
   // and let the insert() algorithm naturally set the threads.
   // nodes will go into new tree root in equivalent order as old

   new_tree.insert(root->data);
   if ( !(root->l_thread) )
      clone(root->l_child, new_tree);
   if ( !(root->r_thread) )
      clone(root->r_child, new_tree);
}

template <class Comparable>
FHthreadedNode<Comparable> *FHthreadedBST<Comparable>::findMin(
   FHthreadedNode<Comparable> *root) const
{
   if (root == NULL)
      return NULL;
   while ( !(root->l_thread) )
      root = root->l_child;

   return root;
}

template <class Comparable>
FHthreadedNode<Comparable> *FHthreadedBST<Comparable>::findMax(
   FHthreadedNode<Comparable> *root) const
{
   if (root == NULL)
      return NULL;
   while ( !(root->r_thread) )
      root = root->r_child;
}

template <class Comparable>
FHthreadedNode<Comparable>* FHthreadedBST<Comparable>::find(
   FHthreadedNode<Comparable> *root, const Comparable &x) const
{
   if (root == NULL)
      return NULL;

   while(true) 
   {
      if (root == NULL)
         return NULL;
      if (x < root->data)
      {
         if(root->l_thread)
            return NULL;
         root = root->l_child;
      }
      else if (root->data < x)
      {
         if(root->r_thread)
            return NULL;
         root = root->r_child;
      }
      else 
         break;
   }
   return root;
}

template <class Comparable>
bool FHthreadedBST<Comparable>::insert(const Comparable &x)
{
   if (m_root == NULL)
   {
      m_root = new FHthreadedNode<Comparable>(x, NULL, NULL, true, true, 0);
      m_size++;
      return true;
   }

   FHthreadedNode<Comparable> *new_node, *parent;
   parent = m_root;
   while(true) 
   {
      if (x < parent->data)
      {
         if( !(parent->l_thread) )
            parent = parent->l_child;
         else
         {
            // place as new left child
            new_node = new FHthreadedNode<Comparable>
               (x, parent->l_child, parent, true, true, 0);
            parent->l_child = new_node;
            parent->l_thread = false;
            break;
         }
      }
      else if (parent->data < x)
      {
         if( !(parent->r_thread) )
            parent = parent->r_child;
         else
         {
            // place as new right child
            new_node = new FHthreadedNode<Comparable>
               (x, parent, parent->r_child, true, true, 0);
            parent->r_child = new_node;
            parent->r_thread = false;
            break;
         }
      }
      else 
         return false; // duplicate;
   }

   m_size++;
   return true;
}

// very hard to remove recursion from this, so adjust pred/succ links
template <class Comparable>
bool FHthreadedBST<Comparable>::remove(
   FHthreadedNode<Comparable> * &root, const Comparable &x)
{
   if (root == NULL)
      return false;

   if (x < root->data)
      if (root->l_thread)
         return false;
      else
         return remove(root->l_child, x);
   if (root->data < x)
      if (root->r_thread)
         return false;
      else
         return remove(root->r_child, x);

   // found the node
   if ( !(root->l_thread) && !(root->r_thread) )
   {
      // two real children
      FHthreadedNode<Comparable> *min_node = findMin(root->r_child);
      root->data = min_node->data;
      remove(root->r_child, min_node->data);
   }
   else
   {
      FHthreadedNode<Comparable> *node_to_remove = root;

      // adjust nodes in root's subtree that "thread directly up" to root
      redirectThreadsPointingToMe(node_to_remove);

      // if a full leaf, we have to modify one of parent's thread flags
      if (node_to_remove->l_thread && node_to_remove->r_thread)
         adjustParentThreadFlags(node_to_remove);

      // finally we can unlink the node
      root = ( !(node_to_remove->l_thread) )? 
         node_to_remove->l_child : node_to_remove->r_child;
      delete node_to_remove;
   }
   return true;
}

template <class Comparable>
void FHthreadedBST<Comparable>::redirectThreadsPointingToMe( 
   FHthreadedNode<Comparable> *node_to_remove )
{
   FHthreadedNode<Comparable>  *min_node, *max_node, *node;

   // adjust nodes in root's subtree that "thread directly up" to root
   min_node = findMin(node_to_remove);
   max_node = findMax(node_to_remove);
   for (node = min_node; node != max_node; node = successor(node))
      if (node->l_child == node_to_remove)
      {
         node->l_child = predecessor(node_to_remove);
         break;  // last of only two possible threads pointing up
      }
      else if (node->r_child == node_to_remove)
      {
         node->r_child = successor(node_to_remove);
         if (node->r_child == NULL)
            break;  // final node in tree
      }
}

// called when both flags are true, meaning one MUST be parent. find out
// which one, so we can set parent's left of right thread flag to true
template <class Comparable>
void FHthreadedBST<Comparable>::adjustParentThreadFlags( 
   FHthreadedNode<Comparable> *node_to_remove )
{
   FHthreadedNode<Comparable> *node;

   node = node_to_remove->r_child;  // successor is parent?
   if ( node != NULL )
   {
      if ( node->l_child == node_to_remove )
         node->l_thread = true;
   }

   // test both in case m_root is leaf
   node = node_to_remove->l_child;  // predecessor is parent?
   if ( node != NULL )
   {
      if ( node->r_child == node_to_remove )
         node->r_thread = true;
   }
}

template <class Comparable>
void FHthreadedBST<Comparable>::make_empty(
   FHthreadedNode<Comparable> * &subtree_to_delete)
{
   if (subtree_to_delete == NULL)
      return;

   // remove children
   if ( !(subtree_to_delete->l_thread) )
      make_empty(subtree_to_delete->l_child);
   if ( !(subtree_to_delete->r_thread) )
      make_empty(subtree_to_delete->r_child);

   // clear client's pointer
   subtree_to_delete = NULL;
   delete subtree_to_delete;
   --m_size;
}

template <class Comparable>
int FHthreadedBST<Comparable>::findHeight( 
   FHthreadedNode<Comparable> *tree_node, int height ) const
{
   int left_height, right_height;

   if (tree_node == NULL)
      return height;
   height++;
   left_height  = tree_node->l_thread ? height 
      : findHeight(tree_node->l_child, height);
   right_height = tree_node->r_thread ? height 
      : findHeight(tree_node->r_child, height);
   return (left_height > right_height)? left_height : right_height;
}

template <class Comparable>
FHthreadedNode<Comparable> *FHthreadedBST<Comparable>::successor(
   FHthreadedNode<Comparable> *node)
{
   if (node->r_thread)
      return node->r_child;
   node = node->r_child;
   while ( !(node->l_thread) )
      node = node->l_child;
   return node;
}

template <class Comparable>
FHthreadedNode<Comparable> *FHthreadedBST<Comparable>::predecessor(
   FHthreadedNode<Comparable> *node)
{
   if (node->l_thread)
      return node->l_child;
   node = node->l_child;
   while ( !(node->r_thread) )
      node = node->r_child;
   return node;
}

#endif