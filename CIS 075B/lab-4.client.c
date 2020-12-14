//
//  lab-4.client.c
//  CIS 075B
//
//  Created by John Towler on 6/7/11.
//  Copyright 2011. All rights reserved.
//

#include "lab-4.shared.h"
#include "mysignal.h"

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
#include <stdlib.h>
#include <termios.h>

#define SIGPIPE_ERROR 1
#define CONNECT_ERROR 2
#define INTERRUPT     3
#define READ_ERROR    4

int active;

int main(){
    char buf[BIGBUF], *token;
    void set_up_signals(void);
    void readserver(int active, char *buf, int bufsize);
    void connect_to_server(void);
    void authToClient(void);
    
    
    authToClient();
    set_up_signals(); 
    connect_to_server();
    
    while(printf("Enter a username ('9' to quit): "), memset(buf, 0, BIGBUF),
          fgets(buf, BIGBUF, stdin), token = strtok(buf, " \t\n"),
          strcmp(token,"9")){
        
        if(!token)
            continue;
        
        // Check for single token
        if (strtok(NULL, " \t")){
            printf("Only one username per line!\n");
            continue;
        }
        
        writen(active, buf, 1);
        writen(active, buf + 1, BIGBUF - 1);  /* Two writes so ignite SIGPIPE */
        memset(buf, 0, BIGBUF);
        
        while(readn(active,buf,BIGBUF), strcmp(buf, PACKET_END) != 0){
            printf("%s", buf);
        }
    }
    memset(buf, 0, BIGBUF);
    strcpy(buf,"quit");
    writen(active, buf, 1);
    writen(active, buf + 1, BIGBUF - 1);
    close(active);
}

void set_up_signals(void){
    void pipe_handler(int signum), term_handler(int signum);
    
    handleSignal(SIGPIPE, pipe_handler);
    handleSignal(SIGQUIT, term_handler);
    handleSignal(SIGINT, term_handler);
}
void connect_to_server(){
    struct sockaddr_in sin;
    
    active = Socket(AF_INET, SOCK_STREAM, 0);
    memset(&sin, 0, sizeof(struct sockaddr_in));
    sin.sin_port = htons(PORT_NUM); 
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    if (connect(active, (struct sockaddr *)&sin, sizeof(sin)) == -1){
        perror("Bad connection.");
        exit(CONNECT_ERROR);
    }
}

void authToClient(void){
    struct termios term;
    char passwd[] = "foobarbaz", userpass[80], *mover;
    int c, i;
    
    tcgetattr(STDOUT_FILENO, &term);
    
    while(strcmp(userpass, passwd) != 0){
        
        if(i > 2){
            printf("Sorry, too many failures. Exiting now.\n");
            exit(1);
        }
        
        term.c_lflag &= ~(ECHO | ICANON);
        tcsetattr(STDOUT_FILENO, TCSANOW, &term);
        
        printf("Enter Password: ");
        mover = userpass;
        
        while((c = getchar()) != '\n'){
            *mover++ = c;
            putchar('*');
        }
        
        *mover = '\0';
        putchar('\n');
        
        term.c_lflag |= (ECHO | ICANON);
        tcsetattr(STDOUT_FILENO, TCSANOW, &term);
        
        i++;
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