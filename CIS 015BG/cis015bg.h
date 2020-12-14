/*
 *  cis015bg.h
 *  CIS 015BG
 *
 *  Wrappers for potentially unsafe memory/file operations.
 *
 *  Created by John Towler on 1/12/11.
 *  Copyright 2011. All rights reserved.
 */

#include <stdio.h>

void *Malloc(size_t size){
    void *ptr;
	
    if ((ptr = (void *) malloc(size)) == NULL){
        perror("malloc");
        exit(1);
    }
    return ptr;
}

void *Realloc(void *ptr, size_t numMembers){
	void *newptr;
	
	if ((newptr = (void *) realloc(ptr, numMembers)) == NULL){
		perror("Realloc");
		exit(1);
	}
	return newptr;
}

void *Calloc(size_t numMembers, size_t size){
    void *ptr;
	
    if ((ptr = (void *) calloc(numMembers, size)) == NULL){
        perror("malloc");
        exit(1);
    }
    return ptr;
}

FILE *Fopen(char *file, char *mode){
    FILE *fp;
	
    if ((fp = fopen(file, mode)) == NULL){
		printf("Fopen error on %s!\n", file);
		exit(1);
    }
    return fp;
}

void Fclose(FILE *fp){
    if (fclose(fp) != 0){
        printf("Fclose failed!\n");
        exit(1);
    }
}
