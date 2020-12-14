//
//  who2.c
//  CIS 075B
//
//  Created by John Towler on 6/7/11.
//  Copyright 2011. All rights reserved.
//

#include "who2.h"

#define BUF_SIZE 256

int main(int argc, char **argv){
    
    int active;
    NODE *who;
    char buf[BUF_SIZE];
    char *token;
    
    active = atoi(argv[1]);
    
    who = getWho();
    
    while(alarm(10), memset(buf, 0, BUF_SIZE), readn(active, buf, BUF_SIZE),
          token = strtok(buf, " \t\n"), strcmp(token, "9")){
        alarm(0);
        findUser(who, token, active);
    }
    
    freeList(who);
}