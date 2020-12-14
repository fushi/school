//
//  who2.h
//  CIS 075B
//
//  Created by John Towler on 6/7/11.
//  Copyright 2011. All rights reserved.
//

#include "cis75b.h"
#include "lab-4.shared.h"
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

/*************** Find a match to *user, and send it to the client *************/
void findUser(NODE *list, char *user, int active){
    
    NODE *mover;
    int seen;
    char *line;
    
    for(seen = 0, mover = list; *mover->line != DUMMY_TAIL;
        mover = mover->next){
        
        line = (char*) Malloc(sizeof(mover->line));
        
        strcpy(line, mover->line);
        
        strtok(line, " \t\n");
        
        if (strcmp(line, user) == 0){
            writen(active, mover->line, BIGBUF);
            seen++;
        }
    }
    
    if(seen == 0)
        writen(active, "User not found!\n", BIGBUF);
    
    writen(active, PACKET_END, BIGBUF);
}