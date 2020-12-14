// File FHsort.h
// Template definitions for vector sorting.  Specifically, include this file
// to use for any array sort when the class overloads the < operator

#include "FHvector.h"

// version that takes vector
template <typename Comparable>
void insertionSort( FHvector<Comparable> & a )
{
    int k, pos, array_size;
    Comparable tmp;
    
    array_size = a.size();
    for(pos = 1; pos < array_size; pos++ )
    {
        tmp = a[pos];
        for(k = pos; k > 0 && tmp < a[k - 1]; k--)
            a[k] = a[k - 1];
        a[k] = tmp;
    }
}

// internal ugly version
template <typename Iterator, typename Comparable>
void insertionSort(Iterator begin, Iterator end, Comparable x)
{
   Iterator pos, k;
   Comparable tmp;
    
   for(pos = begin; pos != end; pos++ )
   {
      tmp = *pos;
      for(k = pos; k != begin && tmp < *(k-1); k-- )
         *k = *(k-1);
      *k = tmp;
   }
}

// version that takes two iterators, compatible with STL iterators
template <typename Iterator>
void insertionSort(Iterator begin, Iterator end)
{
   if (begin != end)
      insertionSort(begin, end, *begin);
}

// alternative that allows client to pass type, but requires instantiation
template <class Comparable>
class InsertionSortOfType
{
public:
   template <typename Iterator>
   InsertionSortOfType(Iterator begin, Iterator end)
   {
      Iterator pos, k;
      Comparable tmp;

      for(pos = begin; pos != end; pos++ )
      {
         tmp = *pos;
         for(k = pos; k != begin && tmp < *(k-1); k-- )
            *k = *(k-1);
         *k = tmp;
      }
   }
};

// version that takes vector and range
template <typename Comparable>
void insertionSort(FHvector<Comparable> & a, int left, int right)
{
    int k, pos;
    Comparable tmp;
    
    for(pos = left + 1; pos <= right; pos++ )
    {
        tmp = a[pos];
        for(k = pos; k > left && tmp < a[k - 1]; k--)
            a[k] = a[k - 1];
        a[k] = tmp;
    }
}

// shell sort #1 -- using shell's outer loop
template <typename Comparable>
void shellSort1( FHvector<Comparable> & a )
{
   int k, pos, array_size, gap;
   Comparable tmp;
    
   array_size = a.size();
   for (gap = array_size/2;  gap > 0;  gap /= 2)  // outer gap loop
      for(pos = gap ; pos < array_size; pos++ )   // middle loop (outer of "insertion-sort")
      {
         tmp = a[pos];
         for(k = pos; k >= gap && tmp < a[k - gap]; k -= gap )   // inner loop
            a[k] = a[k - gap];
         a[k] = tmp;
   }
}

// mergesort helper, merge
template <typename Comparable>
void merge(FHvector<Comparable> & client, FHvector<Comparable> & working,
   int left_pos, int right_pos, int right_stop)
{
   int left_stop, working_pos, array_size;

   working_pos = left_pos;
   left_stop = right_pos - 1;
   array_size = right_stop - left_pos + 1;

   // as soon as we reach the end of either input array, stop
   while(left_pos <= left_stop && right_pos <= right_stop)
      if(client[left_pos] < client[right_pos])
         working[working_pos++] = client[left_pos++];
      else
         working[working_pos++] = client[right_pos++];

   // merge is over; copy the remainder of one or the other input array
   while(left_pos <= left_stop)
      working[working_pos++] = client[left_pos++];
   while( right_pos <= right_stop )
      working[working_pos++] = client[right_pos++];

   // copy back into client array
   for( ; array_size > 0; array_size--, right_stop-- )
      client[right_stop] = working[right_stop];
}

// mergesort internal
template <typename Comparable>
void mergeSort(FHvector<Comparable> & a, FHvector<Comparable> & working,
   int start, int stop)
{
   int right_start;

   if (stop - start < 1)
      return;

   right_start = (start + stop)/2 + 1;
   mergeSort(a, working, start, right_start - 1);
   mergeSort(a, working, right_start, stop);
   merge(a, working, start, right_start, stop);
}

// mergesort public driver 
template <typename Comparable>
void mergeSort(FHvector<Comparable> & a)
{
   if (a.size() < 2)
      return;

   FHvector<Comparable> working(a.size());
   mergeSort(a, working, 0, a.size() - 1);
}

template <typename Comparable>
void percolateDown(FHvector<Comparable> & in_array, int hole, int array_size)
{ 
   int child;
   Comparable tmp;

   for( tmp = in_array[hole]; 2 * hole + 1 < array_size; hole = child )
   {
      child = 2 * hole + 1;
      // if 2 children, get the GREATER of the two (because MAX heap)
      if( child < array_size - 1 && in_array[child] < in_array[child + 1])
         child++;
      if( tmp < in_array[child] )   // MAX heap, not min heap
         in_array[hole] = in_array[child];
      else
         break;
   }
   in_array[hole] = tmp;
}

template <typename Comparable>
inline void myswap(Comparable &x, Comparable &y)
{
   Comparable tmp = x;
   x = y;
   y = tmp;
}

template <typename Comparable>
void heapSort(FHvector<Comparable> & in_array)
{
   int k, array_size;

   // order the array using percolate down
   array_size = in_array.size();
   for(k = array_size/2; k >= 0; k-- )
      percolateDown(in_array, k, array_size);

   // now remove the max element (root) and place at end of array
   for(k = array_size - 1; k > 0; k-- )
   {
      myswap(in_array[0], in_array[k]); // "remove" by placing at end of array
      percolateDown( in_array, 0, k );  // k represents the shrinking array size
   }
}

// quicksort helper
// median3 sorts a[left], a[center] and a[right].
// it leaves the smallest in a[left], the largest in a[right]
// and median (the pivot) is moved "out-of-the-way" in a[right-1].
// (a[center] has what used to be in a[right-1])
template <typename Comparable>
const Comparable & median3(FHvector<Comparable> & a, int left, int right)
{
   int center;

   center = (left + right) / 2;
   if(a[center] < a[left])
      myswap(a[left], a[center]);
   if(a[right] < a[left])
     myswap( a[left], a[right] );
   if(a[right] < a[center])
      myswap(a[center], a[right]);

   myswap(a[center], a[right - 1]);
   return a[right - 1];
}

#define QS_RECURSION_LIMIT 15

// quicksort internal
template <typename Comparable>
void quickSort(FHvector<Comparable> & a, int left, int right)
{
   Comparable pivot;
   int i, j;

   if( left + QS_RECURSION_LIMIT <= right )
   {
      pivot = median3(a, left, right);
      for(i = left, j = right - 1; ; )
      {
         while( a[++i] < pivot )
            ;
         while( pivot < a[--j])
            ;
         if(i < j)
            myswap(a[i], a[j]);
         else
            break;
      }

      myswap(a[i], a[right - 1]);  // restore pivot

      // recursive calls on smaller sub-groups
      quickSort(a, left, i - 1);     
      quickSort(a, i + 1, right);    
   }
   else
      // non-recursive escape valve - insertion sort
      insertionSort(a, left, right);
}

// quicksort public driver
template <typename Comparable>
void quickSort( FHvector<Comparable> & a )
{
    quickSort(a, 0, a.size() - 1);
}

// smart pointer for indirect sort
template <typename Comparable>
class SmartPointer
{
private:
   Comparable *pointee;

public:
   Comparable * operator=(Comparable *rhs);
   SmartPointer<Comparable> & operator=(const SmartPointer<Comparable>  &rhs);
   bool operator<( const SmartPointer<Comparable> & rhs ) const;
   bool operator!=(const SmartPointer<Comparable> & rhs) const;
   bool operator!=(const Comparable *rhs) const;
   int operator-(const Comparable *rhs) const;
   Comparable operator*() const  { return *pointee; }
};

// SmartPointer method definitions ----------------
template <typename Comparable>
Comparable * SmartPointer<Comparable>::operator=(Comparable *rhs)
{
   return (pointee = rhs);
}

template <typename Comparable>
SmartPointer<Comparable> & SmartPointer<Comparable>::operator=(
   const SmartPointer<Comparable>  &rhs)
{
   pointee = rhs.pointee;
   return *this;
}

template <typename Comparable>
bool SmartPointer<Comparable>::operator<( const SmartPointer<Comparable> & rhs ) const
{
   return *pointee < *rhs.pointee;
}

template <typename Comparable>
bool SmartPointer<Comparable>::operator!=(const SmartPointer<Comparable> & rhs) const
{
   return pointee != rhs.pointee;
}

template <typename Comparable>
bool SmartPointer<Comparable>::operator!=(const Comparable *rhs) const
{
   return pointee != rhs;
}

template <typename Comparable>
int SmartPointer<Comparable>::operator-(const Comparable *rhs) const
{
   return pointee - rhs;
}

// indirect sort - uses SmartPointer as intermediate type
template <typename Comparable>
void indirectSort( FHvector<Comparable> & a )
{
   int k, j, next_j, array_size = a.size();
   Comparable tmp;
   FHvector< SmartPointer<Comparable> > p(array_size);

   // copy smart pointer to the client array
   for( k = 0; k < array_size; k++ )
      p[k] = &a[k];

   // do the sort - it only changes the smart pointer order
   quickSort(p);

   // untangle the client elements so they match the pointer order
   for(k = 0; k < a.size( ); k++ )
      if( p[k] != &a[k] )
      {
         tmp = a[k];
         for(j = k; p[j] != &a[k]; j = next_j)
         {
            next_j = p[j] - &a[0];
            a[j] = *p[j];
            p[j] = &a[j];
         }
         a[j] = tmp;
         p[j] = &a[j];
      }
}
