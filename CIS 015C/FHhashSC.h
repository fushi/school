// File FHhashSC.h
// Template definitions for FHhashSC.  
// Separate Chaining Hash Table
#ifndef FHHASHSC_H
#define FHHASHSC_H
#include "FHvector.h"
#include "FHlist.h"
#include <cmath>
using namespace std;

// ---------------------- FHhashSC Prototype --------------------------
template <class Object>
class FHhashSC
{
   static const int INIT_TABLE_SIZE = 97;
   static const float INIT_MAX_LAMBDA;
private:
   FHvector<FHlist<Object> > m_lists;
   int m_size;
   int m_table_size;
   float m_max_lambda;

public:
   FHhashSC(int table_size = INIT_TABLE_SIZE);
   bool contains(const Object & x) const;
   void makeEmpty();
   bool insert(const Object & x);
   bool remove(const Object & x);
   static long nextPrime(long n);
   int size() const { return m_size; }
   bool setMaxLambda( float lm ); 

private:
   void rehash();
   int myhash(const Object & x) const;
};

template <class Object>
const float FHhashSC<Object>::INIT_MAX_LAMBDA = 1.5;

// FHhashSC method definitions -------------------
template <class Object>
FHhashSC<Object>::FHhashSC(int table_size) : m_size(0)
{
   if (table_size < INIT_TABLE_SIZE)
      m_table_size = INIT_TABLE_SIZE;
   else
      m_table_size = nextPrime(table_size);

   m_lists.resize(m_table_size);
   m_max_lambda = INIT_MAX_LAMBDA;
}

template <class Object>
int FHhashSC<Object>::myhash(const Object & x) const
{
   int hash_val;

   hash_val = hash(x) % m_table_size;
   if(hash_val < 0)
      hash_val += m_table_size;

   return hash_val;
}

template <class Object>
void FHhashSC<Object>::makeEmpty()
{
   int k, size = m_lists.size();

   for(k = 0; k < size; k++)
      m_lists[k].clear();
   m_size = 0;
}

template <class Object>
bool FHhashSC<Object>::contains(const Object & x) const
{
   const FHlist<Object> & the_list = m_lists[myhash(x)];
   typename FHlist<Object>::const_iterator iter;

   for (iter = the_list.begin(); iter != the_list.end(); iter++)
      if (*iter == x)
         return true;

   // not found
   return false;
}

template <class Object>
bool FHhashSC<Object>::remove(const Object & x)
{
   FHlist<Object> &the_list = m_lists[myhash(x)];
   typename FHlist<Object>::iterator iter;

   for (iter = the_list.begin(); iter != the_list.end(); iter++)
      if (*iter == x)
      {
         the_list.erase(iter);
         m_size--;
         return true;
      }

   // not found
   return false;
}

template <class Object>
bool FHhashSC<Object>::insert(const Object & x)
{
   typename FHlist<Object>::iterator iter; 
   FHlist<Object> &the_list = m_lists[myhash(x)];

   for (iter = the_list.begin(); iter != the_list.end(); iter++)
      if (*iter == x)
         return false;

   // not found so we insert
   the_list.push_back(x);

   // check load factor
   if( ++m_size > m_max_lambda * m_table_size )
      rehash();

   return true;
}

template <class Object>
void FHhashSC<Object>::rehash()
{
   FHvector< FHlist<Object> > old_lists = m_lists;
   typename FHlist<Object>::iterator iter;
   int k, old_table_size = m_table_size;

   m_table_size = nextPrime(2*old_table_size);
   m_lists.resize( m_table_size );

   // only the first old_size lists need be cleared
   for(k = 0; k < old_table_size; k++ )
      m_lists[k].clear();

   m_size = 0;
   for(k = 0; k < old_table_size; k++)
      for(iter = old_lists[k].begin(); iter != old_lists[k].end(); iter++)
         insert(*iter);
}
template <class Object>
bool FHhashSC<Object>::setMaxLambda(float lam)
{ 
   if (lam < .1 || lam > 100)
      return false;
   m_max_lambda = lam;
   return true;
}

template <class Object>
long FHhashSC<Object>::nextPrime(long n)
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