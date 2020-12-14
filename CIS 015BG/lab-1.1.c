/*
 *  lab-1.1.c
 *  CIS 015BG
 *
 *  Created by John Towler on 1/12/11.
 *  Copyright 2011. All rights reserved.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "cis015bg.h"

int ComputeAverages(char *infile, float *average, float *averages){
	
	int score1, score2, score3, score4, numScores = 0;
	FILE *fin = Fopen(infile, "r");
	float *mover;
	
	
	for (mover = averages; fscanf(fin, "%d\n%d\n%d\n%d\n", &score1, &score2, &score3, &score4) != EOF; mover++, numScores += 4) {
		*mover = (score1 + score2 + score3 + score4) / 4;
		*average += score1 + score2 + score3 + score4;
	}
	
	*mover = -1;
	
	*average /= (numScores);	
	return numScores / 4;
	
}

float StdDeviation(float *averages, int numPeople, float mean){
	
	int sums = 0;
	for (float *mover = averages; *mover != -1; mover++) {
		sums += powf(fabs(*mover - mean), 2);
	}
	
	return sqrtf(sums / numPeople);
}

void MakeZScores(char *outfile, float *averages, float mean, int numPeople, float stdDev){
	
	FILE *fout = Fopen(outfile, "w");
	
	for (float *mover = averages + numPeople - 1; mover >= averages; mover--) {
		fprintf(fout, "%.2f\n", (*mover - mean)/stdDev);
	}
	
}

int main(){
	float averages[1000], mean, stdDev;
	int numPeople;
	char infile[80], outfile[80];

	printf("Enter the input filename: ");
	scanf("%s", infile);
	printf("Enter the ouput filename: ");
	scanf("%s", outfile);
	
	
	numPeople = ComputeAverages(infile, &mean, averages);
	stdDev = StdDeviation(averages, numPeople, mean);
	MakeZScores(outfile, averages, mean, numPeople, stdDev);

	return 0;
}


