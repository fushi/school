//
//  lab-2.server.c
//  CIS 075B
//
//  Created by John Towler on 5/2/11.
//  Copyright 2011. All rights reserved.
//

#include "lab-2.server.h"
#include "lab-2.shared.h"
#include "mysignal.h"

/**********  This is the server.  *********/
#include <unistd.h>    
#include <errno.h>
#include <signal.h>
#include <setjmp.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>

#define BIND_ERROR   1
#define LISTEN_ERROR 2
#define ACCEPT_ERROR 3
#define FORK_ERROR   4
#define READ_ERROR   5
#define CLIENT_GONE  6
#define TIMED_OUT    7

int active, passive;

int main(){
    pid_t pid;
    unsigned int addr_len;
    char buf[256], *token;
    struct sockaddr_in client;
    void set_up_signals(void);
    void create_passive_socket(void);
    void findUser(NODE *list, char *user);
    
    NODE *who;
    
    set_up_signals();
    create_passive_socket();
    
    addr_len = sizeof(struct sockaddr_in);
    while (1){  /*****  Server stays alive for ever!!!  *****/
        active = accept(passive, (struct sockaddr *)&client, &addr_len);
        if (active < 0){
            if (errno == EINTR){
                errno = 0;
                continue;
            }
            else{
                perror("Accept error!");
                exit(ACCEPT_ERROR);
            }
        }
        
        if ((pid = fork()) < 0){
            perror("Fork error!");
            exit(FORK_ERROR);
        }
        
        if (pid != 0){  /******  Parent  ******/
            close(active);
            continue;
        }
        else{    /******  Child  ******/
            close(passive);
            
            handleSignal(SIGCHLD, SIG_DFL);
            
            who = getWho();
            
            while(alarm(10), memset(buf, 0, 256), readn(active, buf, BIGBUF),
                  token = strtok(buf, " \t\n"), strcmp(token, "9")){
                alarm(0);
                
                findUser(who, token);
            }
            
            freeList(who);
            
            exit(0);   /*****  Don't forget this!!!!!  *****/
        }
    }   /***  end while(1)  ***/
}

/**************  Handle timeout/disappearance of client  **************/
void set_up_signals(void){
    void alarm_handler(int signum), no_client(int signum),
    sigchld_handler(int signum);

    handleSignal(SIGALRM, alarm_handler);
    handleSignal(SIGPIPE, no_client);
    handleSignal(SIGCHLD, sigchld_handler);
}

void create_passive_socket(void){
    struct sockaddr_in sin;
    
    passive = socket(AF_INET, SOCK_STREAM, 0);
    memset(&sin, 0, sizeof(sin));
    sin.sin_port = htons(PORT_NUM); 
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(passive, (struct sockaddr *)&sin, (socklen_t) sizeof(sin)) == -1){
        perror("Binding error!");
        exit(BIND_ERROR);
    }
    if (listen(passive, 1) < 0){
        perror("Listen error!");
        exit(LISTEN_ERROR);
    }
}
/*******************  Clear zombie when child finishes.  *********************/
void sigchld_handler(int signum){
    int status;
    while (waitpid(-1, &status, WNOHANG) > 0);
}

/***************  Close active socket when client disappears  ***************/
void no_client(int signum){
    close(active);
    exit(CLIENT_GONE);
}

/**************** Close active socket when client is timed out *************/
void alarm_handler(int signum){
    close(active);
    exit(TIMED_OUT);
}

/*************** Find a match to *user, and send it to the client *************/
void findUser(NODE *list, char *user){
    
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