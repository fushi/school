//
//  lab-5.a.cpp
//  CIS 015C
//
//  Created by John Towler on 5/12/11.
//  Copyright 2011. All rights reserved.
//
#include "FHsplayTree.h"
#include <stdlib.h>
#include <iostream.h>

// CIS_15C Assignment 5 Client / Splay Tree
#include <iostream>
#include "FHsplayTree.h"
using namespace std;

template <typename Object>
class PrintObject{
public:
    void operator()(Object obj){
        cout << obj << " ";
    }
};

int main(){
    int k;
    FHsplayTree<int> search_tree;
    //FHsearch_tree<int> search_tree;
    PrintObject<int> int_printer;
    
    search_tree.traverse(int_printer);
    //cout << search_tree.showRoot() << endl;
    
    cout << "Initial size: " << search_tree.size() << endl;
    for (k = 1; k <= 32; k++)
        search_tree.insert(k);
    cout << "New size: " << search_tree.size() << endl;
    
    cout << "\nTraversal: \n";
    search_tree.traverse(int_printer);
    cout << endl << endl;
    
    for (k = -1; k < 10; k++){
        // search_tree.contains(k);
        try{
            search_tree.find(k);
        }
        catch( ... ){
            cout << " oops ";
        }
        cout << "splay " << k << " --> root: " << search_tree.showRoot() 
        << " height: " << search_tree.showHeight()<< endl;
    }
    return 0;
}