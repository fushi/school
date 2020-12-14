//
//  lab-2.server.h
//  CIS 075B
//
//  Created by John Towler on 5/2/11.
//  Copyright 2011. All rights reserved.
//

#include "cis75b.h"
#include <stdio.h>
#include <string.h>

#define DUMMY_HEAD '^'
#define DUMMY_TAIL '$'

typedef struct node {
    struct node *next, *prev;
    char *line;
} NODE;

NODE* createList(){
    NODE *head = (NODE*) Malloc(sizeof(NODE));
    NODE *tail = (NODE*) Malloc(sizeof(NODE));
    
    head->prev = tail;
    head->next = tail;
    
    tail->prev = head;
    tail->next = head;
    
    head->line = (char*) Malloc(sizeof(char));
    tail->line = (char*) Malloc(sizeof(char));
    
    *head->line = DUMMY_HEAD;
    *tail->line = DUMMY_TAIL;
    
    return head;
}

void insertNode(NODE *before, NODE *after, NODE *toInsert){
    before->next = toInsert;
    
    toInsert->prev = before;
    toInsert->next = after;
    
    after->prev = toInsert;
}

void deleteNode(NODE *toDelete){
    
    NODE *before = toDelete->prev;
    NODE *after = toDelete->next;
    
    before->next = after;
    after->prev = before;
    
    free(toDelete->line);
    
    free(toDelete);
}

void freeList(NODE *list){
    
    NODE *next;
    
    while (list) {
        
        if (list->next == list) {
            deleteNode(list);
            return;
        }
        
        next = list->next;
        deleteNode(list);
        list = next;
    }
}

NODE* getWho(){
    char wholine[100];
    NODE *list, *temp;
    FILE *who;
    
    list = createList();
    
    who = Popen("who", "r");
    
    while (fgets(wholine, 100, who)){
        
        temp = (NODE*) Malloc(sizeof(NODE));
        
        temp->line = (char*) Malloc(strlen(wholine) + 1);

        strcpy(temp->line, wholine);
        
        insertNode(list->prev->prev, list->prev, temp);
    }
    Pclose(who);
    
    return list;
}