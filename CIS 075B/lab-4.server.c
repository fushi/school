//
//  lab-4.server.c
//  CIS 075B
//
//  Created by John Towler on 5/31/11.
//  Copyright 2011. All rights reserved.
//

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
#include "mysignal.h"

#define PASSIVE_MAX 1
#define FIRST_PORT 3071

sigjmp_buf env;

int main(){
    int passive[PASSIVE_MAX], curport = FIRST_PORT, i;
    fd_set rds, savefds;
    void reaper(int signum);
    int set_up_passive_socket(short port);
    void callexec(int *passive, fd_set ready);
    
    FD_ZERO(&savefds);
    for(i = 0; i < PASSIVE_MAX; i++, curport++){
        passive[i] = set_up_passive_socket((short) curport);
        FD_SET(passive[i], &savefds);
    }
    
    handleSignal(SIGCHLD, reaper);
    
    while(1){
        sigsetjmp(env, 1);
        FD_COPY(&savefds, &rds);
        select(FD_SETSIZE, &rds, NULL, NULL, NULL);
        callexec(passive, rds);
    }
}

int makeNonBlocking(int socket){
    long flags;
    
    if ((flags = fcntl(socket, F_GETFL, 0)) < 0)
        exit(1);
        
    if (fcntl(socket, F_SETFL, flags | O_NONBLOCK) < 0)
        exit(1);
    
    return socket;
} 

int set_up_passive_socket(short port){
    struct sockaddr_in sin;
    int passive, makeNonBlocking(int passive);
    
    sin.sin_family = AF_INET;
    sin.sin_port   = htons(port);
    sin.sin_addr.s_addr = htonl(INADDR_ANY);
    
    passive = Socket(AF_INET,SOCK_STREAM,0);
    Bind(passive, (struct sockaddr *) &sin, sizeof(sin));
    Listen(passive, 5);
    
    passive = makeNonBlocking(passive);
    return passive;
}

void reaper(int signum){
    int status;
    while(waitpid(-1, &status, WNOHANG) > 0);
    siglongjmp(env, 1);
}

void callexec(int *passive, fd_set ready){
    
    int active, sock;
    pid_t pid;
    char active_sock[10];
    
    for(int i = 0; i < PASSIVE_MAX; i++){
        if(FD_ISSET(passive[i], &ready)){
            sock = passive[i];
            active = accept(passive[i], NULL, NULL);
            
            pid = Fork();
            
            if(pid > 0){ // Parent
                close(active);
                continue;
            }
            else{ // Child
                for(int j = 0; j < PASSIVE_MAX; j++)
                    close(passive[j]);
                if (sock == passive[0])
                    sprintf(active_sock, "%d", active);
                    execl("./who2", "who2", active_sock, NULL);
                exit(0);
            }
        }
    }
}