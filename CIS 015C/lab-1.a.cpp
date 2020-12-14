//
//  lab-1.a.cpp
//  CIS 015C
//
//  Created by John Towler on 4/4/11.
//  Copyright 2011. All rights reserved.
//

#include "sublist.h"
#include <iostream>
#include <vector>

int main(){
    const int TARGET = 8;
    std::vector<int> data_set;
    Sublist<int> result;
    
    data_set.push_back(2); data_set.push_back(12); data_set.push_back(22);
    data_set.push_back(5); data_set.push_back(15); data_set.push_back(25);
    data_set.push_back(9); data_set.push_back(19); data_set.push_back(29);
    
    // State the target time
    std::cout << "Target time: " << TARGET << std::endl;
    
    // Find and display a maximal sublist
    knapsack(&data_set, TARGET).showSublist();
    
    return 0; 
}


