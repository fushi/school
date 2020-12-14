/*
 *  lab4-1.c
 *  CIS 015BG
 *
 *  Created by John Towler on 2/7/11.
 *  Copyright 2011. All rights reserved.
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "cis015bg.h"

#define LINESIZE	256

char** getLines(FILE *fin, char *searchStr, int startCol, int endCol);

void stringToUpper(char* input);

void sortLines(char **lines);

int compareLines(char *l1, char *l2);

void printLines(FILE *fout, char **lines);

void checkAndGetArgs(int argc, char **argv, int *startcol, int *endcol,
					 char *searchstr, FILE **fin, FILE **fout);

int main(int argc, char *argv[]){
	int startCol, endCol;
	FILE *fin, *fout;
	char searchStr[LINESIZE], **lines;
	
	checkAndGetArgs(argc, argv, &startCol, &endCol,
					searchStr, &fin, &fout);
	
	lines = getLines(fin, searchStr, startCol, endCol);
	
	sortLines(lines);
	
	printLines(fout, lines);

	return 0;
}

char** getLines(FILE *fin, char *searchStr, int startCol, int endCol){

	char line[LINESIZE], **lines, **mover, *compare;
	long diff;
	
	compare = (char*) Malloc((endCol - startCol) * sizeof(char));
	lines = (char**) Malloc(sizeof(char*) * 2);
	
	stringToUpper(searchStr);
	
	for(mover = lines; fgets(line, LINESIZE, fin); ) {
		stringToUpper(line);
		
		strncpy(compare, line + startCol, (endCol - startCol) * sizeof(char));
		
		if (strstr(compare, searchStr) != NULL){
			diff = mover - lines;
			lines = (char**) Realloc(lines, ((mover - lines) + 2) * sizeof(char*));
			mover = lines + diff;
			*mover = (char*) Malloc((strlen(line) + 1) * sizeof(char));
			strcpy(*mover, line);
			mover++;
		}
	}
	*mover = NULL; 
	return lines;
}

void sortLines(char **lines){
	char **mover, **smallest, **last, **looker, *temp;
	
	for (last = lines; *last != NULL; last++);
	
	for (mover = lines; mover < last; mover++) {
		for (smallest = mover, looker = mover + 1; looker < last ; looker++) {
			smallest = compareLines(*looker, *smallest) ? looker : smallest;
		}
		temp = *mover;
		*mover = *smallest;
		*smallest = temp;
	}
}

int compareLines(char *string1, char *string2){
	char *temp1, *temp2;
	
	temp1 = (char*) Calloc(strcspn(string1, "'") + 1, sizeof(char));
	temp2 = (char*) Calloc(strcspn(string2, "'") + 1, sizeof(char));
	
	strncpy(temp1, string1, strcspn(string1, "'"));
	strncpy(temp2, string2, strcspn(string2, "'"));
	
	if (strcmp(temp1, temp2) == -1) {
		return 1;
	}
	
	return 0;
}

void printLines(FILE *fout, char **lines){
	char **mover;
	
	for(mover = lines; *mover != NULL; mover++){
		fputs(*mover, fout);
	}
}

void stringToUpper(char *input){
	for (char* mover = input; *mover != '\0'; mover++) {
		*mover = toupper(*mover);
	}
}

void checkAndGetArgs(int argc, char **argv, int *startcol, int *endcol,
					 char *searchstr, FILE **fin, FILE **fout){
    if (argc != 6){
		printf("Wrong number of command line arguments!\n");
		exit(EXIT_FAILURE);
    }
	
    *fin  = Fopen(argv[1], "r");
    *fout = Fopen(argv[2], "w");
    strcpy(searchstr, argv[3]);
	*startcol = (int) (strtol(argv[4], NULL, 10));
	*endcol = (int) (strtol(argv[5], NULL, 10));
	
    if (*endcol < *startcol){
        printf("End column must be >= start column!\n");
        exit(EXIT_FAILURE);
    }
	
    if (strlen(searchstr) > *endcol - *startcol + 1){
        printf("Column range too small to contain %s!\n", searchstr);
        exit(EXIT_FAILURE);
    }
	
    if (*startcol <= 0){
        printf("Starting column must be a positive value!\n");
        exit(EXIT_FAILURE);
    }
	
    (*startcol)--;
    (*endcol)--;
} 