//
//  lab-1.h
//  CIS 075B
//
//  Created by John Towler on 4/12/11.
//  Copyright 2011. All rights reserved.
//

#include "passwdNode.h"

NODE* createList();
void handlerAlarm(int signum);
void handlerUser(int signum);
void readFileToList(NODE *list, char* filename);
void userInputLoop(NODE *list);
void writeListToFile(NODE *list, char* filename);