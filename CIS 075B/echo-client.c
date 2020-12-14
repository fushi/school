//
//  echo-client.c
//  CIS 075B
//
//  Created by John Towler on 5/28/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "echo-client.h"
#include "mysignal.h"

#include "lab-2.shared.h"


/*****************************  Multi-Client TCP  ***************************/
#include <sys/types.h>   /*******  Demo of multi-client application.  *******/
#include <sys/socket.h>  /*******  This is the client.                *******/
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>

#define SIGPIPE_ERROR 1
#define CONNECT_ERROR 2
#define INTERRUPT     3
#define READ_ERROR    4

int active;

int main(){
    char buf[256];
    void set_up_signals(void);
    void readserver(int active, char *buf, int bufsize);
    void connect_to_server(void);
    
    set_up_signals(); 
    connect_to_server();
    
    while(printf("Enter string: "), memset(buf, 0, BIGBUF),
          fgets(buf, BIGBUF, stdin), strncmp(buf,"quit", 4)){
        writen(active,buf, 1);
        writen(active, buf + 1, BIGBUF - 1);  /* Two writes so ignite SIGPIPE */
        memset(buf, 0, BIGBUF);
        readn(active,buf,BIGBUF);
        printf("From server: %s\n", buf);
    }
    memset(buf, 0, BIGBUF);
    strcpy(buf,"quit");
    writen(active, buf, 1);
    writen(active, buf + 1, BIGBUF - 1);
    close(active);
}


void set_up_signals(void){
    struct sigaction sa;
    void pipe_handler(int signum), term_handler(int signum);
    
    sigfillset(&sa.sa_mask);
    sa.sa_handler = pipe_handler;
    sa.sa_flags   = 0;
    sigaction(SIGPIPE, &sa, NULL);
    sa.sa_handler = term_handler;
    sigaction(SIGQUIT, &sa, NULL);
    sigaction(SIGINT,  &sa, NULL);
}
void connect_to_server(){
    struct sockaddr_in sin;
    
    active = socket(AF_INET, SOCK_STREAM, 0);
    memset(&sin, 0, sizeof(struct sockaddr_in));
    sin.sin_port = htons(PORT_NUM); 
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    if (connect(active, (struct sockaddr *)&sin, sizeof(sin)) == -1){
        perror("Bad connection.");
        exit(CONNECT_ERROR);
    }
}



/****************************  SIGPIPE handler  *****************************/
void pipe_handler(int signum){
    printf("Server disconnected\n");
    exit(SIGPIPE_ERROR);
}


/*************************  Terminal signal handler  ************************/
void term_handler(int signum){
    char buf[BIGBUF] = {'\0'};
    
    memset(buf, 0, BIGBUF);
    strcpy(buf, "quit");
    writen(active, buf, BIGBUF);
    close(active);
    exit(INTERRUPT);
}