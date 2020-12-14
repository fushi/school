// File FHvector.h
// Template definitions for FHvectors.  Specifically, include this file
// to create FHvector classes in a manner similar to STD vectors
#ifndef FHVECTOR_H
#define FHVECTOR_H

#include <stdlib.h>

// ---------------------- FHvector Prototype --------------------------
template <class Object>
class FHvector
{
private:
   int m_size;
   int m_capacity;
   Object *m_objects;

   static const int m_SPARE_CAPACITY = 16;

public:
   FHvector( int initSize = 0 );
   FHvector( const FHvector& rhs );
   ~FHvector () { delete[] m_objects; }

   const FHvector& operator= ( const FHvector& rhs );
   void resize( int new_size );
   void reserve( int new_capacity );

   Object& operator[]( int index );
   const Object& operator[] (int index ) const;

   // thrown in for stl vector compatibility
   Object& at( int index ) { return (*this)[index]; }
   const Object& at (int index ) const  { return (*this)[index]; }

   bool empty() const { return m_size == 0; }
   int size() const { return m_size; }
   int capacity() const { return m_capacity; }

   void push_back( const Object& x );
   void pop_back();
   const Object& back() const;
   const Object& front() const;
   void clear() { *this = FHvector<Object>(); }

   typedef Object *iterator;
   typedef const Object *const_iterator;

   iterator begin() { return &m_objects[0]; }
   const_iterator begin() const { return &m_objects[0]; }
   iterator end() { return &m_objects[ size() ]; }
   const_iterator end() const { return &m_objects[ size() ]; }

   iterator erase( iterator first, iterator last );
   iterator erase( iterator item_to_erase );

private:
   void setSize(int size);
   void setCapacity(int capacity); 

public:
   // for exception throwing
   class OutOfBoundsException { };
   class VectorEmptyException { };
};

// FHvector method definitions -------------------
// private utilities for member methods
template <class Object>
void FHvector<Object>::setSize(int size)
{
   m_size = (size < 0)? 0 : size;
}

template <class Object>
void FHvector<Object>::setCapacity(int capacity)
{
   m_capacity = (capacity <= m_size)? m_size + m_SPARE_CAPACITY : capacity;
}

// public interface
template <class Object>
FHvector<Object>::FHvector(int initSize)
{
   setSize(initSize);
   setCapacity(m_size + m_SPARE_CAPACITY);
   m_objects = new Object[m_capacity];
}

template <class Object>
FHvector<Object>::FHvector(const FHvector<Object>& rhs)
{
   m_objects = NULL;   // needed for following
   operator=(rhs);
}

template <class Object>
const FHvector<Object>& FHvector<Object>::operator= ( const FHvector& rhs )
{
   int k;

   if (this == &rhs)
      return *this;
   delete[] m_objects;
   setSize(rhs.m_size);
   setCapacity(rhs.m_capacity);
   m_objects = new Object[m_capacity];
   for (k = 0; k < m_size; k++)
      m_objects[k] = rhs.m_objects[k];
   return *this;
}

template <class Object>
void FHvector<Object>::resize( int new_size )
{
   if (new_size <= m_capacity)
   {
      setSize(new_size);
      return;
   }
   reserve(2*new_size + 1);
   setSize(new_size);
}

template <class Object>
void FHvector<Object>::reserve( int new_capacity )
{
   Object *old_objects;
   int k;

   if (new_capacity < m_size)
      return;
 
   setCapacity(new_capacity);
   old_objects = m_objects;
   m_objects = new Object[m_capacity];

   for (k = 0; k < m_size; k++)
      m_objects[k] = old_objects[k];
   delete[] old_objects;
}

template <class Object>
Object& FHvector<Object>::operator[]( int index )
{
   if (index < 0 || index >= m_size)
      throw OutOfBoundsException();
   return m_objects[index];
}

template <class Object>
const Object& FHvector<Object>::operator[] (int index ) const
{
   if (index < 0 || index >= m_size)
      throw OutOfBoundsException();
   return m_objects[index];
}

template <class Object>
void FHvector<Object>::push_back( const Object& x )
{
   if (m_size == m_capacity)
      reserve(2*m_capacity + 1);
   m_objects[m_size++] = x;
}

template <class Object>
void FHvector<Object>::pop_back()
{
   if (m_size > 0)
      m_size--;
}

template <class Object>
const Object& FHvector<Object>::back() const
{
  if (m_size <= 0)
      throw VectorEmptyException();
  return m_objects[m_size - 1];
}

template <class Object>
const Object& FHvector<Object>::front() const
{
  if (m_size <= 0)
      throw VectorEmptyException();
  return m_objects[0];
}

template <class Object>
Object * FHvector<Object>::erase( iterator first, iterator last )
{
   iterator iter_1, iter_2, ret_val, end_val;

   if (first < begin() || last > end() || first >= last)
      return NULL;
   
   ret_val = first; // prepare a return value (first element after erase block)
   end_val = end(); // for faster looping

   for (iter_1 = first, iter_2 = last;  iter_2 != end_val; )
      *iter_1++ = *iter_2++;   // objects must have good deep copy management

   setSize(m_size - (last - first));
   return ret_val;  // points to first element not erased after block
}

template <class Object>
Object * FHvector<Object>::erase( iterator item_to_erase ) 
{
   return erase(item_to_erase, item_to_erase + 1);
}

#endif