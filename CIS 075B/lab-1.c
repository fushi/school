//
//  lab-1.c
//  CIS 075B
//
//  Created by John Towler on 4/12/11.
//  Copyright 2011. All rights reserved.
//

#include "cis75b.h"
#include "mysignal.h"
#include "lab-1.h"
#include <signal.h>

#define FILENAME "passwd"
#define LINESIZE 100

NODE *LIST;

int main(){
    struct sigaction sa;
    sigfillset(&sa.sa_mask);
    
    sa.sa_handler = handlerAlarm;
    sa.sa_flags = 0;
    sigaction(SIGALRM, &sa, NULL);
    
    sa.sa_handler = handlerUser;
    sa.sa_flags = 0;
    sigaction(SIGUSR1, &sa, NULL);
    
    LIST = createList();
    
    readFileToList(LIST, FILENAME);
    
    userInputLoop(LIST);
    
    writeListToFile(LIST, FILENAME);
}

void readFileToList(NODE *list, char* filename){
    FILE *file = Fopen(filename, "r");
    char line[LINESIZE], *username, *password, *uid,
        *gid, *info, *homedir, *shell;
    NODE *temp_node, *tail;
    
    while(fgets(line, LINESIZE, file)){
        if(*line == '#'){
            continue;
        }
        // Create a new node for each line
        temp_node = (NODE*) Malloc(sizeof(NODE));
        
        // Read data into temp variables
        username = strtok(line, ":");
        password = strtok(NULL, ":");
        uid = strtok(NULL, ":");
        gid = strtok(NULL, ":");
        info = strtok(NULL, ":");
        homedir = strtok(NULL, ":");
        shell = strtok(NULL, ":");
    
        // Malloc room for the strings!
        temp_node->username = (char*) Malloc(strlen(username) + 1);
        temp_node->password = (char*) Malloc(strlen(password) + 1);
        temp_node->info     = (char*) Malloc(strlen(info) + 1);
        temp_node->homedir  = (char*) Malloc(strlen(homedir) + 1);
        temp_node->shell    = (char*) Malloc(strlen(shell) + 1);

        // Copy data into struct
        strcpy(temp_node->username, username);
        strcpy(temp_node->password, password);
        temp_node->uid = (int) strtol(uid, NULL, 0);
        temp_node->gid = (int) strtol(gid, NULL, 0);
        strcpy(temp_node->info, info);
        strcpy(temp_node->homedir, homedir);
        strcpy(temp_node->shell, shell);
        
        // Set reference nodes
        tail = list->prev;
    
        insertNode(tail->prev, tail, temp_node);
    }
}

void writeListToFile(NODE *list, char* filename){
    
    // Start blocking *ALL* signals
    blockAllSignals();
    
    FILE *file =Fopen(filename, "w");
    NODE *mover = list->next;
    
    for(mover = list->next; *mover->username != '$'; mover = mover->next){
        fprintf(file, "%s:%s:%d:%d:%s:%s:%s",mover->username, mover->password,
                mover->uid, mover->gid, mover->info, mover->homedir,
                mover->shell);
    }
}

void userInputLoop(NODE *list){
    char line[LINESIZE], *token;
    NODE *mover;
    
    // Start ignoring keyboard interrupts
    handleKeyboardInterrupts(SIG_IGN);
    
    while(alarm(30), printf("Enter username to delete: "),
          fgets(line, LINESIZE, stdin), strcmp(line, "quit\n") != 0){
        
        // Turn off alarm!
        alarm(0);
        
        // Tokenize line
        token = strtok(line, " \t\n");
        
        // Check for single token
        if (strtok(NULL, " \t")){
            printf("Only one username per line!\n");
            continue;
        }
        
        if (strcmp(token, "exit") == 0)
            raise(SIGUSR1);
        
        // Reprompt if blank line
        if (token == NULL)
            continue;
        
        // Search for the user, and delete if found. Otherwise, print error!
        for(mover = list; (strcmp(token, mover->username) != 0) &&
            (*mover->username != DUMMY_TAIL); mover = mover->next);
        
        if(strcmp(token, mover->username) == 0)
            deleteNode(mover);
        else
            printf("Username '%s' not found!\n", token);

    }
    // Loop done, stop ignoring keyboard interrupts
    handleKeyboardInterrupts(SIG_DFL);
}

void handlerAlarm(int signum){
    writeListToFile(LIST, "passwd.tmp");
    printf("\n\nCurrent progress saved to ./passwd.tmp\n");
    exit(signum);
}

void handlerUser(int signum){
    printf("Exiting without saving!\n");
    exit(0);
}