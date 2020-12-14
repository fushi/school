// File Foothill_Sort.h
// Template definitions for sorting.  Specifically, include this file
// to use for any array sort when the class overloads the < operator
// Invoke:    ArraySort(your_array, array_size);
 
template <typename Comparable>
void my_swap(Comparable &a, Comparable &b);
// #include "FHvector.h"

template <typename Comparable>
void ArraySort(Comparable array[], int array_size)
{
    for (int k = 0; k < array_size; k++)
       if (!FloatLargestToTop(array, array_size-1-k))
          return;
}
// returns true if a modification was made to the array
template <typename Comparable>
bool FloatLargestToTop(Comparable data[], int top)
{
   bool changed = false;
   
   // notice we stop at length -2 because of expr. k+1 in loop
   for (int k =0; k < top; k++)
      if (data[k+1] < data[k] )
      {
         my_swap(data[k], data[k+1]);
         changed = true;
      }
   return changed;
}

template <typename Comparable>
void my_swap(Comparable &a, Comparable &b)
{
   Comparable temp;

   temp = a;
   a = b;
   b = temp;
}



template <typename Comparable>
void InsertionSort(Comparable array[], int array_size)
{
   int k, pos;
   Comparable tmp;

   for(pos = 1; pos < array_size; pos++ )
   {
      tmp = array[pos];
      for(k = pos; k > 0 && tmp < array[k-1]; k-- )
         array[k] = array[k-1];
      array[k] = tmp;
   }
}

// shellsort #1 -- using shell's outer loop
template <typename Comparable>
void ShellSort1( Comparable array[], int array_size )
{
   int k, pos, gap;
   Comparable tmp;
    
   for (gap = array_size/2;  gap > 0;  gap /= 2)
      for(pos = gap ; pos < array_size; pos++ )
      {
         tmp = array[pos];
         for(k = pos; k >= gap && tmp < array[k - gap]; k -= gap )
            array[k] = array[k - gap];
         array[k] = tmp;
   }
}

template <typename Comparable>
void MergeSort(Comparable array[], int array_size)
{
   if (array_size < 2)
      return;

   Comparable *working = new Comparable[array_size];
   MergeSort(array, working, array_size);
   delete[] working;
}

// mergesort internal function
template <typename Comparable>
void MergeSort(Comparable array[], Comparable working_array[], int array_size)
{
   int right_start;

   if (array_size < 2)
      return;

   right_start = array_size/2;
   MergeSort(array, working_array, right_start);
   MergeSort(array + right_start, working_array, array_size - right_start);
   Merge(array, working_array, right_start, array_size);
}

// input array 1:  client[0] ... client[right_pos-1]
// input array 2:  client[right_pos] ... client[array_size - 1]
// working[] array supplied by client to avoid local allocation
template <typename Comparable>
void Merge(Comparable client[], Comparable working[], 
   int right_pos, int array_size)
{
   int left_pos, left_stop, right_stop, working_pos;

   working_pos = left_pos = 0;
   left_stop = right_pos - 1;
   right_stop = array_size - 1;

   // as soon as we reach the end of either input array, stop
   while(left_pos <= left_stop && right_pos <= right_stop)
      if(client[left_pos] <= client[right_pos])
         working[working_pos++] = client[left_pos++];
      else
         working[working_pos++] = client[right_pos++];

   // merge is over; copy the remainder of one or the other input array
   while(left_pos <= left_stop)
      working[working_pos++] = client[left_pos++];
   while( right_pos <= right_stop )
      working[working_pos++] = client[right_pos++];

   // copy back into client array
   for( ; right_stop >= 0; right_stop-- )
      client[right_stop] = working[right_stop];
}
