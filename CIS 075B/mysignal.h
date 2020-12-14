//
//  mysignal.h
//  CIS 075B
//
//  Created by John Towler on 4/23/11.
//  Updated on 5/10/11.
//  Copyright 2011. All rights reserved.
//

#ifndef MYSIGNAL_H
#define MYSIGNAL_H

#include <signal.h>
#include "cis75b.h"

void blockAllSignals(){
    sigset_t all_sigs;
    sigfillset(&all_sigs);
    Sigprocmask(SIG_BLOCK, &all_sigs, NULL);
}

void handleKeyboardInterrupts(sig_t how){
    struct sigaction sa;
    sigfillset(&sa.sa_mask);
    
    sa.sa_handler = how;
    sa.sa_flags = 0;
    
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGTSTP, &sa, NULL);
    sigaction(SIGQUIT, &sa, NULL);
}

void handleSignal(int signal, sig_t how){
    struct sigaction sa;
    sigfillset(&sa.sa_mask);
    
    sa.sa_handler = how;
    sa.sa_flags = 0;
    
    sigaction(SIGCHLD, &sa, NULL);
}

#endif