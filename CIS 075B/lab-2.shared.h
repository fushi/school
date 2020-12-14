//
//  lab-2.shared.h
//  CIS 075B
//
//  Created by John Towler on 5/2/11.
//  Copyright 2011. All rights reserved.
//

#include <unistd.h>
#include <stdio.h>

#define PACKET_END "!@#$\n"
#define PORT_NUM    3071
#define BIGBUF 256

int readn(int fd, char *buf, int bytes){
    int nleft;
    int nread;
    char *mover = buf;
    
    nleft = bytes;
    while (nleft > 0){
        if ((nread = (int) read(fd,mover,nleft)) < 0){
            perror("Read Error");
            return -1;  /**** Error!! ****/
        }
        else if (nread == 0)
            break;      /****  EOF!   ****/
        nleft -= nread;
        mover += nread;
    }
    return (bytes - nleft);
}

int writen(int fd, char *buf, int bytes){
    int nleft;
    int nwritten;
    char *mover = buf;
    
    nleft = bytes;
    while (nleft > 0){
        if ((nwritten = (int) write(fd,mover,nleft)) < 0){
            perror("Write Error");
            return -1;  /**** Error!! ****/
        }
        nleft -= nwritten;
        mover += nwritten;
    }
    return bytes;
}