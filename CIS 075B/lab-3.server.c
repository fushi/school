//
//  lab-3.server.c
//  CIS 075B
//
//  Created by John Towler on 5/28/11.
//  Copyright 2011. All rights reserved.
//

#include "lab-2.shared.h"
#include "lab-2.server.h"
#include <time.h>
#include "cis75b.h"
#define NOT_USED -1

int readsock;
sigjmp_buf env;
fd_set saveset;

struct timetable{
    int socket;
    time_t requesttime;
};
struct timetable reqtimes[100];

int main(){
    void findUser(NODE *list, char *user, int socket);
    
    int readn(int readsock, char *string, int bufsize);
    int writen(int readsock, char *string, int bufsize);
    int makeNonBlocking(int socket);
    void set_up_SIGPIPE(void);
    fd_set readset;
    int socket, passive, active, i;
    char string[BIGBUF];
    int set_up_passive_socket(void);
    
    NODE *wholists[FD_SETSIZE];
    
    set_up_SIGPIPE();
    passive = set_up_passive_socket();
    
    FD_ZERO(&saveset);
    FD_SET(passive, &saveset);
    for (i = 0; i < 100; i++) reqtimes[i].socket  = NOT_USED;
    
    for(;;){
        FD_COPY(&saveset, &readset);
        
        select(FD_SETSIZE, &readset, NULL, NULL, NULL);
        
        for (socket = 0; socket < 100; socket++){
            if (reqtimes[socket].socket == NOT_USED) continue;
            if (time(NULL) - reqtimes[socket].requesttime > 10){
                Close(socket);
                FD_CLR(socket, &saveset);
                reqtimes[socket].socket = NOT_USED;
                freeList(wholists[socket]);
            }
        }
        
        if (FD_ISSET(passive, &readset)){
            active = accept(passive, NULL, NULL);
            active = makeNonBlocking(active);
            
            reqtimes[active].socket      = active;
            reqtimes[active].requesttime = time(NULL);
            
            wholists[active] = getWho();
            
            FD_SET(active, &saveset);
        }
        
        for(readsock = passive; readsock < FD_SETSIZE; readsock++){
            sigsetjmp(env, 1);
            if (readsock != passive && FD_ISSET(readsock, &readset)){
                memset(string, 0, BIGBUF);
                readn(readsock, string, BIGBUF);
                
                //strcmp(string, "9") == 0
                if (*string == '9'){
                    FD_CLR(readsock, &saveset);
                    Close(readsock);
                    reqtimes[readsock].socket = NOT_USED;
                    freeList(wholists[socket]);
                    continue;
                }
                
                reqtimes[readsock].requesttime = time(NULL);
                
                findUser(wholists[readsock], string, readsock);
            }
        }  
    }           
}

/*************** Find a match to *user, and send it to the client *************/
void findUser(NODE *list, char *user, int socket){
    
    NODE *mover;
    int seen;
    char *line;
    
    for(seen = 0, mover = list; *mover->line != DUMMY_TAIL;
        mover = mover->next){
        
        line = (char*) Malloc(sizeof(mover->line));
        
        strcpy(line, mover->line);
        strtok(line, " \t\n");
        
        if (strcmp(line, user) == 0){
            writen(socket, mover->line, BIGBUF);
            seen++;
        }
    }
    
    if(seen == 0)
        writen(socket, "User not found!\n", BIGBUF);
    
    writen(socket, PACKET_END, BIGBUF);
}

int set_up_passive_socket(void){
    struct sockaddr_in sin;
    int passive, makeNonBlocking(int passive);
    
    sin.sin_family = AF_INET;
    sin.sin_port   = htons(PORT_NUM);
    sin.sin_addr.s_addr = htonl(INADDR_ANY);

    passive = Socket(AF_INET,SOCK_STREAM,0);
    Bind(passive, (struct sockaddr *) &sin, sizeof(sin));
    Listen(passive, 5);
    
    passive = makeNonBlocking(passive);
    return passive;
}

int makeNonBlocking(int socket){
    long flags;
    
    if ((flags = fcntl(socket, F_GETFL, 0)) < 0){
        perror("Get flags");
        exit(1);
    }
    if (fcntl(socket, F_SETFL, flags | O_NONBLOCK) < 0) {
        perror("Set flags");
        exit(1);
    }
    
    return socket;
} 

void set_up_SIGPIPE(void){
    void handler(int signum);
    struct sigaction sa;
    
    sa.sa_handler = handler;
    sa.sa_flags   = 0;
    Sigfillset(&sa.sa_mask);
    Sigaction(SIGPIPE, &sa, NULL);
}

void handler(int signum){
    Close(readsock);
    FD_CLR(readsock, &saveset);
    reqtimes[readsock].socket = NOT_USED;
    readsock++;
    siglongjmp(env, 1);
}