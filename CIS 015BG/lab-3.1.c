/*
 *  lab-3.1.c
 *  CIS 015BG
 *
 *  Created by John Towler on 1/25/11.
 *  Copyright 2011. All rights reserved.
 *
 */
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "cis015bg.h"

#define LINESIZE	256

int getBetweenMagicChar(char* infile, char* outfile, char magicChar);
int fileCompare(char *infile1, char *infile2);

int main(){
	
	char infile[LINESIZE], outfile[LINESIZE], magicChar;

	printf("Enter input filename: ");
	scanf("%s", infile);
	
	printf("Enter output filename: ");
	scanf("%s", outfile);
	
	printf("Enter a character: ");
	while ((magicChar = getchar()) == '\n');
	
	if (!isalpha(magicChar)) {
		printf("%c is not a letter!", magicChar);
		exit(EXIT_FAILURE);
	}
	
	getBetweenMagicChar(infile, outfile, magicChar);
	fileCompare(infile, outfile);
	
	return 0;
}


int getBetweenMagicChar(char *infile, char *outfile, char magicChar){

	FILE *fin = Fopen(infile, "r");
	FILE *fout = Fopen(outfile, "w");
	
	char *start, *end, line[LINESIZE];
	
	while (fgets(line, LINESIZE, fin)){
		
		end = NULL;
	
		if((start = strchr(line, magicChar)))
			end = strchr(start+1, magicChar);
		
		if (end != NULL) {
			strncpy(end+1, "\n\0", 2);
			fputs(start, fout);
		}
		else fputs(line, fout);
	}
	
	Fclose(fin);
	Fclose(fout);
	
	return 0;
}

int fileCompare(char *infile1, char *infile2){
	
	FILE *f1 = Fopen(infile1, "r");
	FILE *f2 = Fopen(infile2, "r");
	
	char line1[LINESIZE], line2[LINESIZE];
	int lineNum = 0;
	
	while (fgets(line1, LINESIZE, f1) && fgets(line2, LINESIZE, f2)){
		
		lineNum++;
		
		if(strcmp(line1, line2) == 0)
			printf("%d: %s", lineNum, line1);
	}
	
	Fclose(f1);
	Fclose(f2);
	
	return 0;
}