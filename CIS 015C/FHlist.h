// File FHlist.h
// Template definitions for FHlists.  Specifically, include this file
// to create FHlist classes in a manner similar to STD lists
#ifndef FHLIST_H
#define FHLIST_H

#include <stdlib.h>
// ---------------------- FHlist Prototype --------------------------
template <class Object>
class FHlist
{
private:
   // Node prototype - this nested template is defined outside
   class Node;

   // private data for FHlist
   int m_size;
   Node *m_head;
   Node *m_tail;

public:
   FHlist() { init(); }
   ~FHlist() { clear(); delete m_head; delete m_tail; }
   bool empty() const { return (m_size == 0); }
   int size() const { return m_size; }
   void clear();
   void pop_front();
   void pop_back();
   void push_front( const Object &x );
   void push_back( const Object &x );
   Object & front() { return m_head->next->data; }
   const Object & front() const   { return m_head->next->data; }
   Object & back() { return m_tail->prev->data; }
   const Object & back() const   { return m_tail->prev->data; }

   // iterator prototypes - these nested classes are defined outside
   class const_iterator;
   class iterator;
    
   // iterator based functions
   iterator insert(iterator iter, const Object &x);
   iterator erase( iterator iter );
   iterator erase( iterator start, iterator stop );

   // for exception throwing
   class NullIteratorException { };
   class IteratorMismatchException { };

   const_iterator begin() const { return const_iterator(m_head->next, *this); }
   const_iterator end() const { return const_iterator(m_tail, *this); }
   iterator begin()  { return iterator(m_head->next, *this); }
   iterator end()  { return iterator(m_tail, *this); }

   const FHlist & operator=( const FHlist & rhs );
   FHlist( const FHlist &rhs ) { init(); *this = rhs; }

   // syntax too difficult to define outside
//    iterator insert( iterator iter, const Object &x )
//   {
//      if (iter.my_list != this)
//         throw IteratorMismatchException();
//
//      Node *p = iter.current;
//       if (p == NULL)
//         throw NullIteratorException();
//      if (p->prev == NULL)
//         throw NullIteratorException();
//
//      // build a node around x and link it up
//      Node *new_node = new Node(x, p->prev, p);
//      p->prev->next = new_node;
//      p->prev = new_node;    
//      iterator new_iter(new_node, *this);
//      m_size++;
//      return new_iter;
//   }
//
//   iterator erase( iterator iter )
//   {
//      if (iter.my_list != this)
//         throw IteratorMismatchException();
//
//      Node *p = iter.current;
//      if (p == NULL)
//         throw NullIteratorException();
//      if (p->prev == NULL || p->next == NULL)
//         throw NullIteratorException();
//
//      iterator ret_val(p->next, *this);
//      p->prev->next = p->next;
//      p->next->prev = p->prev;
//      delete p;
//      m_size--;
//
//      return ret_val;
//   }
//
//   iterator erase( iterator start, iterator stop )
//   {
//      if (start.my_list != this || stop.my_list != this)
//         throw IteratorMismatchException();
//      if (start.current == NULL || stop.current == NULL)
//         throw NullIteratorException();
//      if (start.current->prev == NULL || start.current->next == NULL
//         || stop.current->prev == NULL)
//         throw NullIteratorException();
//
//      for (iterator iter = start; iter != stop; )
//         iter = erase(iter);  // if this throws, then current erase() will throw, too
//
//      return stop;
//   }

private:
   void init();
};

// FHlist method definitions -------------------
// private utilities for member methods
template <class Object>
void FHlist<Object>::init()
{
   m_size = 0;
   m_head = new Node;
   m_tail = new Node;
   m_head->next = m_tail;
   m_tail->prev = m_head;
}

// public interface
template <class Object>
void FHlist<Object>::clear()
{
   while ( m_size > 0 )
      pop_front();
}

template <class Object>
void FHlist<Object>::pop_front()
{
   Node *p;

   // safer, but a little slower with this test
   if ( m_size == 0 )
      return;

   p = m_head->next;
   m_head->next = p->next;
   m_head->next->prev = m_head;
   delete p;
   m_size--;
}

template <class Object>
void FHlist<Object>::pop_back()
{
   Node *p;

   // safer, but a little slower with this test
   if ( m_size == 0 )
      return;

   p = m_tail->prev;
   m_tail->prev = p->prev;
   m_tail->prev->next = m_tail;
   delete p;
   m_size--;
}

template <class Object>
void FHlist<Object>::push_front( const Object &x )
{
   Node *p = new Node(x, m_head, m_head->next);
   m_head->next->prev = p;
   m_head->next = p;
   m_size++;
}

template <class Object>
void FHlist<Object>::push_back( const Object &x )
{
   Node *p = new Node(x, m_tail->prev, m_tail);
   m_tail->prev->next = p;
   m_tail->prev = p;
   m_size++;
}

template <class Object>
const FHlist<Object> & FHlist<Object>::operator=( const FHlist & rhs )
{
   const_iterator iter;
   if ( &rhs == this)
      return *this;
   clear();
   for (iter = rhs.begin(); iter != rhs.end(); ++iter)
      this->push_back( *iter );
   return *this;
}

// definition of nested FHlist<Object>::Node class ----------------------
template <class Object>
class FHlist<Object>::Node
{
public: 
   Node *prev, *next;
   Object data;

   Node( const Object & d = Object(), Node *prv = NULL, Node *nxt = NULL )
      : prev(prv), next(nxt), data(d)
   { }
}; 

// definition of nested FHlist<Object>::const_iterator class -------------
template <class Object>
class FHlist<Object>::const_iterator
{
   friend class FHlist;

protected:
   // protected member data
   Node *current;
   const FHlist *my_list;  // needed to test for certain errors

   // protected constructor for use only by derived iterator and friends
   const_iterator(Node *p, const FHlist<Object> &lst) : current(p), my_list(&lst) { }

public:
   const_iterator() : current(NULL), my_list(NULL) { }

   const Object &operator*() const
   {
      if (!current)
         throw NullIteratorException();
      return current->data;
   }

   const_iterator & operator++()
   {
      if (current->next != NULL)
         current = current->next;
      return *this;
   }

   const_iterator & operator--(int)
   {
      static const_iterator old = *this;
      if (current->prev != NULL)
         current = current->prev;
      return old;
   }

   const_iterator & operator--()
   {
      if (current->prev != NULL)
         current = current->prev;
      return *this;
   }

   const_iterator & operator++(int)
   {
      static const_iterator old = *this;
      if (current->next != NULL)
         current = current->next;
      return old;
   }

   bool operator==(const const_iterator &rhs) const 
   {
      return current == rhs.current;
   }
   bool operator!=(const const_iterator &rhs) const
   {
      return !(*this == rhs);
   }
}; 

// definition of nested FHlist<Object>::iterator class ---------------------
template <class Object>
class FHlist<Object>::iterator : public FHlist<Object>::const_iterator
{
   friend class FHlist;

protected:
   // chain to base class 
   iterator(Node *p, const FHlist<Object> & lst) : const_iterator(p, lst) { }

public:
   iterator() { }
   const Object &operator*() const { return const_iterator::operator*(); }
   Object &operator*()
   {
      if (!this->current)
         throw NullIteratorException();
      return this->current->data;
   }
   iterator & operator++()
   {
      if (this->current->next != NULL)
         this->current = this->current->next;
      return *this;
   }
   iterator & operator++(int)
   {
      static iterator old = *this;
      if (this->current->next != NULL)
         this->current = this->current->next;
      return old;
   }

   iterator & operator--()
   {
      if (this->current->prev != NULL)
         this->current = this->current->prev;
      return *this;
   }
   iterator & operator--(int)
   {
      static iterator old = *this;
      if (this->current->prev != NULL)
         this->current = this->current->prev;
      return old;
   }
};

// definition of methods that use iterators
template <class Object>
typename FHlist<Object>::iterator FHlist<Object>::insert(iterator iter, const Object &x){
    if (iter.my_list != this)
        throw IteratorMismatchException();
    
    Node *p = iter.current;
    if (p == NULL)
        throw NullIteratorException();
    if (p->prev == NULL)
        throw NullIteratorException();
    
    // build a node around x and link it up
    Node *new_node = new Node(x, p->prev, p);
    p->prev->next = new_node;
    p->prev = new_node;    
    iterator new_iter(new_node, *this);
    m_size++;
    return new_iter;
}

template <class Object>
typename FHlist<Object>::iterator FHlist<Object>::erase(iterator iter )
{
    if (iter.my_list != this)
        throw IteratorMismatchException();
    
    Node *p = iter.current;
    if (p == NULL)
        throw NullIteratorException();
    if (p->prev == NULL || p->next == NULL)
        throw NullIteratorException();
    
    iterator ret_val(p->next, *this);
    p->prev->next = p->next;
    p->next->prev = p->prev;
    delete p;
    m_size--;
    
    return ret_val;
}

template <class Object>
typename FHlist<Object>::iterator FHlist<Object>::erase( iterator start, iterator stop )
{
    if (start.my_list != this || stop.my_list != this)
        throw IteratorMismatchException();
    if (start.current == NULL || stop.current == NULL)
        throw NullIteratorException();
    if (start.current->prev == NULL || start.current->next == NULL
        || stop.current->prev == NULL)
        throw NullIteratorException();
    
    for (iterator iter = start; iter != stop; )
        iter = erase(iter);  // if this throws, then current erase() will throw, too
    
    return stop;
}
#endif