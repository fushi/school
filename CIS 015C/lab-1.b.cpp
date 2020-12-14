//
//  lab-1.b.cpp
//  CIS 015C
//
//  Created by John Towler on 4/8/11.
//  Copyright 2011. All rights reserved.
//

#include "iTunes.h"
#include "sublist.h"
#include <iostream>
#include <vector>

int operator+(int n, const iTunesEntry & tune);
ostream& operator<<(ostream &out, const iTunesEntry &tune);

int main(){
    const int TARGET = 259;
    int array_size;
    std::vector<iTunesEntry> data_set;
    Sublist<iTunesEntry> result;
    
    // Read the Data
    iTunesEntryReader tunes_input("itunes_file.txt");
    
    if (tunes_input.readError()){
        cout << "couldn't open " << tunes_input.getFileName() << " for input.\n";
        exit(1);
    }
    
    array_size = tunes_input.getNumTunes();
    for (int k = 0; k < array_size; k++)
        data_set.push_back(tunes_input[k]);
    
    // State the target time
    std::cout << "Target time: " << TARGET << std::endl;
    
    // Find and display a maximal sublist
    knapsack(&data_set, TARGET).showSublist();
    
    return 0; 
}

int operator+(int n, const iTunesEntry &tune){
    return n + tune.GetNTime();
}

ostream& operator<<(ostream &out, const iTunesEntry &tune){
    return out << tune.GetNTime();
}

