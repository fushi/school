/*
 *  lab-2.1.c
 *  CIS 015BG
 *
 *  Created by John Towler on 1/18/11.
 *  Copyright 2011. All rights reserved.
 *
 */

#include "cis015bg.h"

int main(){
	void GetValuesFromUser(char *infile1, int *prows1, int *pcols1,
						   char *infile2, int *prows2, int *pcols2,
						   char *outfile);
	
	int ** BuildMatrixFromFile(char *infile, int rows, int cols);
	int ** MultiplyMatrices(int **m1, int rows1, int cols1, int **m2, int cols2);
	void WriteMatrixToFile(char *outfile, int **result, int rows1, int cols2);
	
	char *infile1[256], *infile2[256], *outfile[256];
	int rows1, cols1, rows2, cols2;
	int **matrix1, **matrix2, **result;
	
	GetValuesFromUser(infile1, &rows1, &cols1, infile2, &rows2, &cols2, outfile);
	
	matrix1 = BuildMatrixFromFile(infile1, rows1, cols1);
	matrix2 = BuildMatrixFromFile(infile2, rows2, cols2);
	result  = MultiplyMatrices(matrix1, rows1, cols1, matrix2, cols2);
	
	WriteMatrixToFile(outfile, result, rows1, cols2);	
}


void GetValuesFromUser(char *infile1, int *prows1, int *pcols1,
					   char *infile2, int *prows2, int *pcols2,
					   char *outfile){
	
	printf("Enter name of first input file: ");
	scanf("%s", infile1);
	
	printf("Enter number of rows in first input file: ");
	scanf("%d", prows1);
	
	printf("Enter number of cols in first input file: ");
	scanf("%d", pcols1);
	
	printf("Enter name of second input file: ");
	scanf("%s", infile2);
	
	printf("Enter number of rows in second input file: ");
	scanf("%d", prows2);
	
	printf("Enter number of cols in second input file: ");
	scanf("%d", pcols2);

	printf("Enter name of output file: ");
	scanf("%s", outfile);

}

int ** BuildMatrixFromFile(char *infile, int rows, int cols){
	
	FILE *fin = Fopen(infile, "r");
	
	int **matrix;
	
	matrix = (int**) Malloc (sizeof (int*) * rows);
	
	for(int i = 0; i < rows; i++){
		
		matrix[i] = (int*) Malloc (sizeof(int) * (cols));
		
		for (int j = 0; j < cols; j++){
			fscanf(fin,"%d", &matrix[i][j]);
		}
		fscanf(fin, "\n");
	}
	
	Fclose(fin);

	return matrix;
}

int ** MultiplyMatrices(int **m1, int rows1, int cols1, int **m2, int cols2){

	int **result, sum = 0;
	
	result = (int**) Malloc (sizeof (int*) * rows1);
	
	for(int i = 0; i < rows1; i++){
		result[i] = (int*) Malloc (sizeof(int) * (cols2));
		for (int j = 0; j < cols2; j++){
			
			for (int k = 0; k < cols1; k++) {
				sum += m1[i][k] * m2[k][j];
			}
			result[i][j] = sum;
			
			sum = 0;
		}
	}
	return result;	
}

void WriteMatrixToFile(char *outfile, int **result, int rows, int cols){
	
	FILE *fout = Fopen(outfile, "w");
	
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			fprintf(fout, "%d ", result[i][j]);
		}
		fprintf(fout, "\n");
	}	
	Fclose(fout);
}