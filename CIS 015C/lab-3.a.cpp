//
//  lab-3.a.cpp
//  CIS 015C
//
//  Created by John Towler on 4/26/11.
//  Copyright 2011. All rights reserved.
//

#include <time.h>
#include <stdlib.h>
#include <iostream.h>

#define MAT_SIZE 800

typedef float* DynMat[MAT_SIZE];

void MatShow_Dyn(const DynMat & mat, int start, int size);
void MatMult_Dyn(const DynMat & mat_a, const DynMat & mat_b, const DynMat & mat_ans, int size);

int main()
{
    int r, c;
    clock_t start_time, end_time;
    double rand_frac;
    int rand_row, rand_col, small_percent;
    
    // non-sparse dynamic matrix
    DynMat mat_dyn, mat_dyn_ans;
    
    // allocate rows and initialize to 0
    for (r = 0; r < MAT_SIZE; r++)
    {
        mat_dyn[r] = new float[MAT_SIZE];
        mat_dyn_ans[r] = new float[MAT_SIZE];
        
        for (c = 0; c < MAT_SIZE; c++)
        {
            mat_dyn[r][c] = 0;
            mat_dyn_ans[r][c] = 0;
        }
    }
    
    srand((unsigned) time(NULL));
    
    // generated 0.2% non-default values bet 0 and 1
    small_percent = MAT_SIZE * MAT_SIZE * .05;
    for (r = 0; r < small_percent; r++)
    {
        rand_row = rand() % MAT_SIZE;
        rand_col = rand() % MAT_SIZE;
        rand_frac = (rand() % 100) / (double) 99;
        mat_dyn[rand_row][rand_col] = rand_frac;
    }
    
    // 15x15 submatrix anchored at (60, 60)
    MatShow_Dyn(mat_dyn, 0, 15);
    
    start_time = clock();  // ------------------ start
    MatMult_Dyn(mat_dyn, mat_dyn, mat_dyn_ans, MAT_SIZE);
    end_time = clock();  // ---------------------- stop
    cout << "\nDyn Array Mult Elapsed Time: " 
    << (double)(end_time - start_time)/(double)CLOCKS_PER_SEC 
    << " seconds." << endl << endl;
    
    // show product
    MatShow_Dyn(mat_dyn_ans, 0, 15);
    
    // clean up
    for (r = 0; r < MAT_SIZE; r++){
        delete[] mat_dyn_ans[r]; 
        delete[] mat_dyn[r];
    }    
    
    cout << endl;
}

void MatShow_Dyn(const DynMat & mat, int start, int size){
    int r, c;
    
    for (r = start; r < start + size; r++)
    {        
        for (c = start; c < start + size; c++)
        {
            printf("%1.2f  ", mat[r][c]);
        }
        printf("\n");
    }
}

void MatMult_Dyn(const DynMat & mat_a, const DynMat & mat_b, const DynMat & mat_ans, int size){
    
    float sum;
    
	for(int i = 0; i < MAT_SIZE; i++){
		for (int j= 0; j < MAT_SIZE; j++){
			for (int k = 0; k < MAT_SIZE; k++) {
				sum += mat_a[i][k] * mat_b[k][j];
			}
			mat_ans[i][j] = sum;
			sum = 0;
		}
	}
}