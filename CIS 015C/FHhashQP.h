// File FHhashQP.h
// Template definitions for FHhashQP.  
// Quadratic Probing Hash Table
#ifndef FHHASHQP_H
#define FHHASHQP_H
#include "FHvector.h"
#include <cmath>
using namespace std;

// ---------------------- FHhashQP Prototype --------------------------
template <class Object>
class FHhashQP
{
protected:
   static const int INIT_TABLE_SIZE = 97;
   static const float INIT_MAX_lambda;

   enum ElementState { ACTIVE, EMPTY, DELETED };
   class HashEntry;

   FHvector<HashEntry> m_array;
   int m_size;
   int m_table_size;
   float m_max_lambda;

public:
   FHhashQP(int table_size = INIT_TABLE_SIZE);
   bool contains(const Object & x) const;
   void makeEmpty();
   bool insert(const Object & x);
   bool remove(const Object & x);
   static long nextPrime(long n);
   int size() const { return m_size; }
   bool setMaxlambda( float lm ); 

protected:
   void rehash();
   int myhash(const Object & x) const;
   int findPos( const Object & x ) const;
};

template <class Object>
const float FHhashQP<Object>::INIT_MAX_lambda = 0.49F;

// definition of nested FHhashQP<Object>::HashEntry class ----------------
template <class Object>
class FHhashQP<Object>::HashEntry
{
public:
   Object data;
   ElementState state;
   HashEntry( const Object & d = Object(), ElementState st = EMPTY )
      : data(d), state(st)
   { }
};

// FHhashQP method definitions -------------------
template <class Object>
FHhashQP<Object>::FHhashQP(int table_size) : m_size(0)
{
   if (table_size < INIT_TABLE_SIZE)
      m_table_size = INIT_TABLE_SIZE;
   else
      m_table_size = nextPrime(table_size);
   m_array.resize(m_table_size);
   makeEmpty();
   m_max_lambda = INIT_MAX_lambda;
}

template <class Object>
int FHhashQP<Object>::myhash(const Object & x) const
{
   int hash_val;

   hash_val = hash_func(x) % m_table_size;
   if(hash_val < 0)
      hash_val += m_table_size;

   return hash_val;
}

template <class Object>
void FHhashQP<Object>::makeEmpty()
{
   int k, size = m_array.size();

   for(k = 0; k < size; k++)
      m_array[k].state = EMPTY;
   m_size = 0;
}

template <class Object>
bool FHhashQP<Object>::contains(const Object & x) const
{
   return m_array[findPos(x)].state == ACTIVE;
}

template <class Object>
bool FHhashQP<Object>::remove(const Object & x)
{
   int bucket = findPos(x);

   if ( m_array[bucket].state != ACTIVE )
      return false;

   m_array[bucket].state = DELETED;
   m_size--;
   return true;
}

template <class Object>
bool FHhashQP<Object>::insert(const Object & x)
{
   int bucket = findPos(x);

   if ( m_array[bucket].state == ACTIVE )
      return false;

   m_array[bucket].data = x;
   m_array[bucket].state = ACTIVE;

   // check load factor
   if( ++m_size > m_max_lambda * m_table_size )
      rehash();

   return true;
}
template <class Object>
int FHhashQP<Object>::findPos( const Object & x ) const
{
   int kth_odd_num = 1;
   int index = myhash(x);

   while ( m_array[index].state != EMPTY
      && m_array[index].data != x )
   {
      index += kth_odd_num;  // k squared = (k-1) squared + kth odd #
      kth_odd_num += 2;   // compute next odd #
      if ( index >= m_table_size )
         index -= m_table_size;
   }

   return index;
}

template <class Object>
void FHhashQP<Object>::rehash()
{
   FHvector<HashEntry> old_array = m_array;
   int k, old_table_size = m_table_size;

   m_table_size = nextPrime(2*old_table_size);
   m_array.resize( m_table_size );
   for(k = 0; k < m_table_size; k++)
      m_array[k].state = EMPTY;

   m_size = 0;
   for(k = 0; k < old_table_size; k++)
      if (old_array[k].state == ACTIVE)
         insert( old_array[k].data );
}
template <class Object>
bool FHhashQP<Object>::setMaxlambda(float lam)
{ 
   if (lam < .1 || lam > .49)
      return false;
   m_max_lambda = lam;
   return true;
}

template <class Object>
long FHhashQP<Object>::nextPrime(long n)
{
   long k, candidate, loop_lim;

   // loop doesn't work for 2 or 3
   if (n <= 2 )
      return 2;
   else if (n == 3)
      return 3;

   for (candidate = (n%2 == 0)? n+1 : n ; true ; candidate += 2)
   {
      // all primes > 3 are of the form 6k +/- 1
      loop_lim = (long)( (sqrt((float)candidate) + 1)/6 );

      // we know it is odd.  check for divisibility by 3
      if (candidate%3 == 0)
         continue;

      // now we can check for divisibility of 6k +/- 1 up to sqrt
      for (k = 1; k <= loop_lim; k++)
      {
         if (candidate % (6*k - 1) == 0)
            break;
         if (candidate % (6*k + 1) == 0)
            break;
      }
      if (k > loop_lim)
         return candidate;
   }
}

#endif