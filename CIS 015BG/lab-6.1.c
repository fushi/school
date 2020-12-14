/*
 *  lab-5.1.c
 *  CIS 015BG
 *
 *  Created by John Towler on 3/4/11.
 *  Copyright 2011. All rights reserved.
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "cis015bg.h"

#define MAXLINE			100
#define STATELEN		2
#define DUMMY_HEADER	'\0'
#define DUMMY_TRAILER	'\177'

typedef struct person {
	char	*name;
	char	ss[12];
	int		age;
	char	*city;
	char	state[3];
	struct person *next;
} PERSON;

void checkArgs(int argc, char **argv, FILE **fin, FILE **fout);
PERSON* initList(void);
void readIntoSortedLinkedList(FILE *fin, PERSON *list);
void userSearchForRecordsByState(PERSON *list);
void putRecords(FILE *fout, PERSON *list);
void stringToUpper(char *input);

int main(int argc, char *argv[]){
	
	PERSON *list;
	FILE *fin, *fout;

	checkArgs(argc, argv, &fin, &fout);
	list = initList();
	readIntoSortedLinkedList(fin, list);
	userSearchForRecordsByState(list);
    putRecords(fout, list);

	return 0;
}

void checkArgs(int argc, char **argv, FILE **fin, FILE **fout){
	if (argc != 3) {
		printf("Usage: %s <infile> <outfile>", argv[0]);
		exit(EXIT_FAILURE);
	}
	
	*fin  = Fopen(argv[1], "r");
	*fout = Fopen(argv[2], "w");
}

PERSON* initList(void){
	PERSON *header, *trailer;
	
	header = (PERSON*) Malloc(sizeof(PERSON));
	trailer = (PERSON*) Malloc(sizeof(PERSON));
	
	header->next = trailer;
	
	header->state[0] = header->ss[0] = DUMMY_HEADER;
	trailer->state[0] = trailer->ss[0] =DUMMY_TRAILER;
	
	return header;
}

void readIntoSortedLinkedList(FILE *fin, PERSON *list){
	
	char line[MAXLINE+1], *name, *ss, *age, *city, *state;
	int years;
	PERSON *new, *mover;
	
	while (fgets(line, MAXLINE, fin)) {
		
		new = (PERSON*) Malloc(sizeof(PERSON));
		
		name	= strtok(line, ":");
		ss		= strtok(NULL, ":");
		age		= strtok(NULL, ":");
		city	= strtok(NULL, ":");
		state	= strtok(NULL, "\n");
		sscanf(age, "%d", &years);
		
		new->name = (char*) Calloc(strlen(name) + 1, sizeof(char));
		new->city = (char*) Calloc(strlen(city) + 1, sizeof(char));
		
		strcpy(new->name, name);
		strcpy(new->ss, ss);
		strcpy(new->city, city);
		strcpy(new->state, state);
		new->age = years;
		
		mover = list;
		
		while (strcmp(mover->next->state, new->state) < 0) mover = mover->next;
		while (strcmp(mover->next->state, new->state) == 0 && strcmp(mover->next->ss, new->ss) < 0) mover = mover->next;
		
		(new->next = mover->next) && (mover->next = new);
	}
}

void userSearchForRecordsByState(PERSON *list){
	
	char line[MAXLINE+1], state[STATELEN+1];
	PERSON *mover;
	
	while (printf("\nEnter State Abbreviation: "), stringToUpper(fgets(line, MAXLINE, stdin)), strcmp(line, "QUIT\n") !=0) {
		sscanf(line, "%s", state);
		
		if (strlen(state) > STATELEN) {
			printf("State code must be two letters!\n");
			continue;
		}
		
		mover = list;
		
		while (strcmp(state, mover->state) > 0) mover = mover->next;
		
		printf("\n%-20s %-15s %-5s %-20s %-20s\n", "Name", "Social", "Age", "City", "State");
		
		while (strcmp(state, mover->state) == 0){
			printf("%-20s %-15s %-5d %-20s %-20s\n", mover->name, mover->ss, mover->age, mover->city, mover->state);
			mover = mover->next;
		}
	}
}

void putRecords(FILE *fout, PERSON *list){
    PERSON *mover;
    
    mover = list->next;
    
    while(mover->state[0] != DUMMY_TRAILER){
        fprintf(fout, "%s:%s:%d:%s:%s\n", mover->name, mover->ss, mover->age, mover->city, mover->state);
        mover = mover->next;
    }
}

void stringToUpper(char *input){
	for (char* mover = input; *mover != '\0'; mover++) {
		*mover = toupper(*mover);
	}
}