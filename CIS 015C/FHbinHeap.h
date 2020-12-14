// File FHbinHeap.h
// Template definitions for FHbinHeap.  
// Binary heaps for priority queues and heap sorts
#ifndef FHBINHEAP_H
#define FHBINHEAP_H
#include "FHvector.h"
using namespace std;

// ---------------------- FHbinHeap Prototype --------------------------
template <class Comparable>
class FHbinHeap
{
   static const int INIT_CAPACITY = 64; // perfect tree of size 63

private:
   FHvector<Comparable> m_array;
   int m_size;
   int m_capacity;

public:
   FHbinHeap(int capacity = INIT_CAPACITY);
   FHbinHeap(const FHvector<Comparable> & items );
   bool empty() const { return m_size == 0; }
   void makeEmpty() { m_size = 0; };
   void insert(const Comparable & x);
   Comparable & remove();

   int size() const { return m_size; }

   // for exception throwing
   class HeapEmptyException { };

private:
   void orderHeap();
   void percolateDown( int hole );
};

// FHbinHeap method definitions -------------------
template <class Comparable>
FHbinHeap<Comparable>::FHbinHeap(int capacity)
{
   // choose a capacity that is exactly 2^N - 1 for some N (esthetic)
   // which leads to m_capacity 2^N, internally -- user asks for 127, we
   // reserve 128, if they want 128, we have to reserve 256.
   for (m_capacity = INIT_CAPACITY; 
      m_capacity <= capacity;
      m_capacity = 2 * m_capacity
      )
   {
      if (m_capacity < 0)
      {
         m_capacity = INIT_CAPACITY; // give up - overflow
         break;
      }
   }
   m_array.resize(m_capacity);
   makeEmpty();
}

template <class Comparable>
FHbinHeap<Comparable>::FHbinHeap( const FHvector<Comparable> & items )
: m_size(items.size())
{
   int k;

   // find the first perfect tree size > items.size() and INIT_CAPACITY
   for (m_capacity = INIT_CAPACITY; 
      m_capacity <= m_size;
      m_capacity = 2 * m_capacity
      )
   {
      if (m_capacity < 0)
         m_capacity = m_size + 1; // give up - overflow, and not perfect
   }
   m_array.resize(m_capacity);

   // copy starting with position 1 - no ordering yet
   for(k = 0; k < m_size; k++ )
      m_array[k+1] = items[k];

   // order the heap
   orderHeap( );
}

template <class Comparable>
void FHbinHeap<Comparable>::insert(const Comparable & x)
{
   int hole;

   if( m_size == m_capacity - 1 )
   {
      m_capacity = 2 * m_capacity;
      m_array.resize(m_capacity);
   }

   // percolate up
   hole = ++m_size;
   for( ; hole > 1 && x < m_array[hole/2]; hole /= 2 )
      m_array[hole] = m_array[hole/2];
   m_array[hole] = x;
}

template <class Comparable>
Comparable & FHbinHeap<Comparable>::remove()
{
   static Comparable min_object;

   if( empty() )
      throw HeapEmptyException();

   min_object = m_array[1];

   m_array[1] = m_array[m_size--];
   percolateDown(1);

   return min_object;
}

template <class Comparable>
void FHbinHeap<Comparable>::percolateDown(int hole)
{ 
   int child;
   Comparable tmp;

   for( tmp = m_array[hole]; 2 * hole <= m_size; hole = child )
   {
      child = 2 * hole;
      // if 2 children, get the lesser of the two
      if( child < m_size && m_array[child + 1] < m_array[child] )
         child++;
      if( m_array[child] < tmp )
         m_array[hole] = m_array[child];
      else
         break;
   }
   m_array[hole] = tmp;
}

template <class Comparable>
void FHbinHeap<Comparable>::orderHeap()
{
   int k;

   for(k = m_size/2; k > 0; k-- )
      percolateDown(k);
}

#endif