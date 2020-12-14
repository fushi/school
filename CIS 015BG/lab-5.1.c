/*
 *  lab-5.1.c
 *  CIS 015BG
 *
 *  Created by John Towler on 2/16/11.
 *  Copyright 2011. All rights reserved.
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "cis015bg.h"


#define BUCKET		5
#define MAXLINE		100
#define STATELEN	2

typedef struct person {
	char	*name;
	char	ss[12];
	int		age;
	char	*city;
	char	state[3];
} PERSON;

PERSON* getRecords(FILE *fin, int *count);

void sortRecordsByStateAndSSNum(PERSON *people, int count);

void userSearchForRecordsByState(PERSON *people, int count);

void putRecords(FILE *fout, PERSON *people, int count);

char* stringMod(char *input);

int main(int argc, char *argv[]){
	
	PERSON *people;
	FILE *fin, *fout;
	int count;
	
	if (argc != 3) {
		printf("Usage: %s <infile> <outfile>", argv[0]);
		exit(EXIT_FAILURE);
	}
	
	fin  = Fopen(argv[1], "r");
	fout = Fopen(argv[2], "w");
	
	people = getRecords(fin, &count);
	sortRecordsByStateAndSSNum(people, count);
	userSearchForRecordsByState(people, count);
	putRecords(fout, people, count);
	return 0;
}

PERSON* getRecords(FILE *fin, int *count){
	char line[MAXLINE+1], *name, *ss, *age, *city, *state;
	int years, position;
	PERSON *people = NULL, *mover;
	
	*count = 0;
	mover = people;
	
	while (fgets(line, MAXLINE, fin)) {
		
		if ((mover - people) % BUCKET == 0) {
			position = mover - people;
			people = (PERSON *) Realloc(people, (mover-people + BUCKET) * sizeof(PERSON));
			mover = people + position;
		}
		
		name	= strtok(line, ":");
		ss		= strtok(NULL, ":");
		age		= strtok(NULL, ":");
		city	= strtok(NULL, ":");
		state	= strtok(NULL, "\n");
		sscanf(age, "%d", &years);
		
		mover->name = (char*) Calloc(strlen(name) + 1, sizeof(char));
		strcpy(mover->name, name);
		
		strcpy(mover->ss, ss);
		
		mover->age = years;
		
		mover->city = (char*) Calloc(strlen(city) + 1, sizeof(char));
		strcpy(mover->city, city);
		
		strcpy(mover->state, state);
		
		(*count)++;
		mover++;
	}
	
	people = (PERSON *) Realloc(people, (*count) * sizeof(PERSON));
	return people;
}

void sortRecordsByStateAndSSNum(PERSON *people, int count){

	PERSON *omover, *imover, temp;
	
	
	for (omover = people; omover - people < count; omover++) {
		
		temp = *omover;
		
		for (imover = omover - 1; (imover - people) >= 0; imover--) {
			if (strcmp(imover->state,temp.state) > 0){
				*(imover+1) = *imover;
			}
			else if((strcmp(imover->state,temp.state) == 0) && (strcmp(imover->ss,temp.ss) > 0)){
				*(imover+1) = *imover;
			}
			else
				break;
		}
		*(imover+1) = temp;
	}
}

void userSearchForRecordsByState(PERSON *people, int count){
	
	PERSON *first, *last, *mid, *mover;
	
	char searchstr[MAXLINE];
	
	while (printf("Enter a State Abbreviation to search for: ") && strcmp(stringMod(fgets(searchstr, MAXLINE, stdin)), "QUIT") != 0) {
		

		first = people;
		last = people + count - 1;
	
		while (first <= last) {
			mid = first + (last - first) / 2;
			
			if(strncmp(searchstr, mid->state, 2) < 0) {
				//Search First Half
				last = mid - 1;
				mid = NULL;
			}
			else if (strncmp(searchstr, mid->state, 2) > 0) {
				//Search Second Half
				first = mid + 1;
				mid = NULL;
			}

			else{
				//Found a Hit
				if (mid == first || strncmp(searchstr, (mid-1)->state, 2) > 0) {
					//This is the first!
					first = last + 1;
				}
				else {
					//It's not the first!
					last = mid - 1;
				}
			}
		}
		
		printf("\n%-20s %-15s %-5s %-20s %-20s\n", "Name", "Social", "Age", "City", "State");
		
		for (mover = mid; mover != NULL && strncmp(mover->state, searchstr, 2) == 0; mover++) {
			printf("%-20s %-15s %-5d %-20s %-20s\n", mover->name, mover->ss, mover->age, mover->city, mover->state);
		}
		
		if (mid == NULL) {
			printf("No Records Found for %s\n", searchstr);
		}
		printf("\n");
	}
}

void putRecords(FILE *fout, PERSON *people, int count){
	PERSON *mover;
	
	for (mover = people; mover - people < count; mover++) {
		
		fprintf(fout, "%s:%s:%d:%s:%s\n", mover->name, mover->ss, mover->age, mover->city, mover->state);
	}
}

char* stringMod(char *input){
	char *mover;
	
	for (mover = input; *mover != '\n'; mover++);
	*mover = '\0';
	for (mover = input; *mover != '\0'; mover++) {
		*mover = toupper(*mover);
	}
	return input;
}