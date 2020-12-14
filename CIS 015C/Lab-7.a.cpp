//
//  Lab-7.a.cpp
//  CIS 015C
//
//  Created by John Towler on 5/25/11.
//  Copyright 2011. All rights reserved.
//

#include "FHvector.h"
#include "FHsort.h"
#include <iostream>
using namespace std;

#define DATA_SIZE 500000

int sedg(int i);
int * sedgefunc(int size);

template <typename Comparable>
void shellSortX(FHvector<Comparable> & a, int* gap_array, int gap_size){
    int k, pos, array_size, gap;
    Comparable tmp;
    
    array_size = a.size();
      
    for (int element = gap_size - 1;  element > -1;  element--){ // outer loop
        gap = gap_array[element];
        for(pos = gap ; pos < array_size; pos++ ){ // middle loop
            tmp = a[pos];
            for(k = pos; k >= gap && tmp < a[k - gap]; k -= gap ) // inner loop
                a[k] = a[k - gap];
            a[k] = tmp;
        }
    }
}

int main(){
    FHvector<int> data;
    FHvector<int>::iterator iter;
    clock_t start_time, end_time;
    
    // Generate some numbers
    for (int i = 0; i < DATA_SIZE; i++)
        data.push_back(rand());
    
    // Explicit Gap Sequence
    int explicit_gap[] = { 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 
        4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288, 1048576};
    int explicit_gap_size = sizeof explicit_gap / sizeof( explicit_gap[0] );
    
    // Sedgewick Gap Sequence
    int sedge_size = 20;
    int *sedgewick = sedgefunc(sedge_size);
    
    // My Gap Sequence (Fibbonaci)
    int fib[] = {1, 9, 34, 182, 836, 4025, 19001, 90358, 428481, 2034035,
        9651787, 45806244, 217378076, 1031612713};
    int fib_size = sizeof fib / sizeof( fib[0] );
    
    // My Gap Sequence (Ciura)
    int ciura[] = { 1, 4, 10, 23, 57, 132, 301, 701, 1753, 4383, 10958, 27396, 
        68491, 171228, 428071, 1070178};
    int ciura_size = sizeof ciura / sizeof( ciura[0] );
    
    // Sort!
    start_time = clock();
//    shellSort1(data);
//    shellSortX(data, explicit_gap, explicit_gap_size);
//    shellSortX(data, sedgewick, sedge_size);
//    shellSortX(data, fib, fib_size);
//    shellSortX(data, ciura, ciura_size);
    end_time = clock();
    
    cout << "\nSort Elapsed Time: " 
    << (double)(end_time - start_time)/(double)CLOCKS_PER_SEC 
    << " seconds." << endl << endl;
}

int * sedgefunc(int size){
    int *sequence = (int*) malloc(sizeof(int)*size);
    
    sequence[0] = 1;
    
    for(int i = 1; i < size; i++)
        sequence[i] = sedg(i-1);
    
    cout << "Sedgewick sequence is: " << endl;
    for(int j = 0; j < size; j++)
        cout << sequence[j] << endl;
    
    return sequence;
}

int sedg(int i){ 
    return (i%2) ? (9*(2<<i)-9*(2<<(i/2))+1) : (8*(2<<i)-6*(2<<((i+1)/2))+1);
}

/*
            10000   50000   100000  150000  200000  500000
 
 implicit   0.007   0.054   0.1105  0.1822  0.2593  0.7453
 explicit   0.018   0.142   0.4813  0.7378  1.1335  3.9025
 Sedgewick  0.005   0.038   0.0757  0.1171  0.1681  0.4620
 Fib        0.006   0.040   0.0983  0.1469  0.1840  0.5429
 Ciura      0.005   0.035   0.0744  0.1185  0.1609  0.4374
 
 */
