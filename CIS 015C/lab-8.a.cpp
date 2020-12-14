//
//  lab-8.a.cpp
//  CIS 015C
//
//  Created by John Towler on 6/4/11.
//  Copyright 2011. All rights reserved.
//

#include "FHvector.h"
#include "FHsort.h"

// Public Interface
template <typename Comparable>
void quickSortX( FHvector<Comparable> & a, int rec_limit ){
    quickSortX(a, 0, a.size() - 1, rec_limit);
}

// Workhorse
template <typename Comparable>
void quickSortX(FHvector<Comparable> & a, int left, int right, int rec_limit){
    Comparable pivot;
    int i, j;
    
    if( left + rec_limit <= right ){
        pivot = median3(a, left, right);
        for(i = left, j = right - 1; ; ){
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
        quickSortX(a, left, i - 1, rec_limit);     
        quickSortX(a, i + 1, right, rec_limit);    
    }
    else
        // non-recursive escape valve - insertion sort
        insertionSort(a, left, right);
}

// Comparison of heapsort and quicksort vectors
#include <iostream>
using namespace std;
#include "FHvector.h"
#include <time.h>

// --------------- main ---------------
#define ARRAY_SIZE 2000000

int main(){
    int array_of_ints[ARRAY_SIZE];
    FHvector<int> fh_vector_of_ints;
    clock_t start_time, end_time;
    
    // build both an array and a vector for comparing sorts
    for (int k = 0; k < ARRAY_SIZE; k++)
        array_of_ints[k] = rand()%ARRAY_SIZE;
    
    for (int rec_limit = 2; rec_limit < 101; rec_limit +=2) {
        fh_vector_of_ints.clear();

        for (int k = 0; k < ARRAY_SIZE; k++)
            fh_vector_of_ints.push_back(array_of_ints[k]);
        
        start_time = clock();  // ------------------ start 
        quickSortX(fh_vector_of_ints, rec_limit);
        end_time = clock();  // ---------------------- stop
        cout << rec_limit << "\t"
        << (double)(end_time - start_time)/(double)CLOCKS_PER_SEC << endl;
    }
    
    return 0; 
}

/*

                                Array Size
Rec
Limit
        20000       100000      200000      1000000     2000000
 2      0.005342    0.030542    0.06998     0.376871    0.770266
 4      0.005302    0.030246    0.069341    0.398667    0.742602
 6      0.004879    0.030305    0.06831     0.347815    0.737736
 8      0.005023    0.029379    0.068467    0.366849    0.739086
 10     0.005061    0.03445     0.066797    0.364228    0.740885
 12     0.004951    0.029209    0.064366    0.359942    0.74551
 14     0.005088    0.031153    0.070176    0.359314    0.758801
 16     0.00507     0.033598    0.064818    0.351368    0.752733
 18     0.005203    0.031736    0.067157    0.357729    0.755905
 20     0.006184    0.030566    0.06882     0.370597    0.757912
 22     0.006121    0.033651    0.067591    0.363685    0.81348
 24     0.006236    0.032408    0.067936    0.367359    0.792525
 26     0.006053    0.032356    0.070885    0.378581    0.791772
 28     0.006149    0.032888    0.076098    0.386161    0.891183
 30     0.00622     0.034198    0.077315    0.397446    0.813272
 32     0.00632     0.041975    0.080602    0.398757    0.815294
 34     0.006374    0.038626    0.073441    0.40676     0.827197
 36     0.006594    0.035807    0.082843    0.412449    0.833391
 38     0.007303    0.036711    0.082806    0.432476    0.855181
 40     0.007717    0.036312    0.088812    0.412164    0.869244
 42     0.007495    0.037616    0.07846     0.418303    0.876295
 44     0.007357    0.037838    0.081085    0.430446    0.885598
 46     0.00683     0.040063    0.083746    0.435064    0.965186
 48     0.006751    0.040309    0.081794    0.43967     0.909221
 50     0.006987    0.041911    0.080741    0.470207    0.937335
 52     0.007323    0.03898     0.086933    0.448934    0.946425
 54     0.007505    0.041017    0.083823    0.452063    0.944252
 56     0.007772    0.04081     0.087925    0.471966    0.967111
 58     0.007746    0.045118    0.093339    0.493077    0.985732
 60     0.007785    0.041662    0.095986    0.499561    1.02785
 62     0.007804    0.042427    0.102586    0.484559    1.04608
 64     0.00908     0.042558    0.09861     0.547207    1.01168
 66     0.009201    0.049817    0.099791    0.48411     1.02367
 68     0.008722    0.043297    0.102724    0.514932    1.02131
 70     0.008451    0.048074    0.10484     0.509434    1.09489
 72     0.009917    0.052244    0.115657    0.515916    1.04589
 74     0.009629    0.051478    0.117042    0.530948    1.0591
 76     0.009788    0.046001    0.108277    0.540589    1.07075
 78     0.009672    0.049231    0.101071    0.522782    1.09675
 80     0.008517    0.05634     0.102882    0.551954    1.0961
 82     0.008997    0.058043    0.109804    0.550844    1.10321
 84     0.010325    0.055996    0.106176    0.564928    1.11499
 86     0.010872    0.05507     0.112763    0.574324    1.13051
 88     0.010744    0.057305    0.116203    0.574755    1.14476
 90     0.009525    0.053794    0.117523    0.57482     1.16608
 92     0.009612    0.058814    0.11389     0.589189    1.17137
 94     0.010421    0.059326    0.117845    0.592199    1.1847
 96     0.011333    0.055011    0.120443    0.573014    1.18608
 98     0.011953    0.057637    0.130057    0.600949    1.20601
 100    0.012017    0.058016    0.131436    0.614391    1.21042
 
 
 The floor on the minimal range seems to be around 4-6 (Results vary by array
 size). The ceiling on the optimal range seems to vary much more than the floor,
 ranging from 18-30, once again depending on Array size. I'd concur that
 recursion limits ranging from The overall optimal range seems to be 6-18.
 
*/