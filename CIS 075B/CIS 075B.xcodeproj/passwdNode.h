//
//  passwdNode.h
//  CIS 075B
//
//  Created by John Towler on 4/24/11.
//  Copyright 2011. All rights reserved.
//

#define DUMMY_HEAD '^'
#define DUMMY_TAIL '$'

typedef struct node {
    struct node *next, *prev;
    char *username, *password, *info, *homedir, *shell;
    int uid, gid;
} NODE;

NODE* createList(){
    NODE *head = (NODE*) Malloc(sizeof(NODE));
    NODE *tail = (NODE*) Malloc(sizeof(NODE));
    
    head->prev = tail;
    head->next = tail;
    
    tail->prev = head;
    tail->next = head;
    
    head->username = (char*) Malloc(sizeof(char));
    tail->username = (char*) Malloc(sizeof(char));
    
    *head->username = '^';
    *tail->username = '$';
    
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
    
    free(toDelete); //Whoops, forgot to dealloc the stuff inside!
}