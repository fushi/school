//
//  lab-4.a.cpp
//  CIS 015C
//
//  Created by John Towler on 4/28/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

//#include "lab-4.a.h"
// --------------- main ---------------
#include <iostream>
#include <string>
#include <stack>
#include "FHlazySearchTree.h"
using namespace std;

template <typename Object>
class PrintObject
{
public:
    void operator()(Object obj)
    {
        cout << obj << " ";
    }
};

int main()
{
    int k;
    FHsearch_tree<int> search_tree;
    PrintObject<int> int_printer;
    
    search_tree.traverse(int_printer);
    
    cout << "\ninitial size: " << search_tree.size() << endl;
    search_tree.insert(50);
    search_tree.insert(20);
    search_tree.insert(30);
    search_tree.insert(70);
    search_tree.insert(10);
    search_tree.insert(60);
    
    cout << "After populating -- traversal and sizes: \n";
    search_tree.traverse(int_printer);
    cout << "\ntree 1 size: " << search_tree.size() 
    << "  Hard size: " << search_tree.sizeHard() << endl;
    
    cout << "Collecting garbage on new tree - should be no garbage." << endl;
    search_tree.collectGarbage();
    cout << "tree 1 size: " << search_tree.size() 
    << "  Hard size: " << search_tree.sizeHard() << endl;
    
    // test assignment operator
    FHsearch_tree<int> search_tree2 = search_tree;
    
    cout << "\n\nAttempting 1 removal: \n";
    if (search_tree.remove(20))
        cout << "removed " << 20 << endl;
    cout << "tree 1 size: " << search_tree.size() 
    << "  Hard size: " << search_tree.sizeHard() << endl;
    
    cout << "Collecting Garbage - should clean 1 item. " << endl;
    search_tree.collectGarbage();
    cout << "tree 1 size: " << search_tree.size() 
    << "  Hard size: " << search_tree.sizeHard() << endl;
    
    cout << "Collecting Garbage again - no change expected. " << endl;
    search_tree.collectGarbage();
    cout << "tree 1 size: " << search_tree.size() 
    << "  Hard size: " << search_tree.sizeHard() << endl;
    
    // test soft insertion and deletion:
    
    
    cout << "Adding 'hard' 22 - should see new sizes. " << endl;
    search_tree.insert(22);
    search_tree.traverse(int_printer);
    cout << "\ntree 1 size: " << search_tree.size() 
    << "  Hard size: " << search_tree.sizeHard() << endl;
    
    cout << "\nAfter soft removal. " << endl;
    search_tree.remove(22);
    search_tree.traverse(int_printer);
    cout << "\ntree 1 size: " << search_tree.size() 
    << "  Hard size: " << search_tree.sizeHard() << endl;
    
    cout << "Repeating soft removal. Should see no change. " << endl;
    search_tree.remove(22);
    search_tree.traverse(int_printer);
    cout << "\ntree 1 size: " << search_tree.size() 
    << "  Hard size: " << search_tree.sizeHard() << endl;
    
    cout << "Soft insertion. Hard size should not change. " << endl;
    search_tree.insert(22);
    search_tree.traverse(int_printer);
    cout << "\ntree 1 size: " << search_tree.size() 
    << "  Hard size: " << search_tree.sizeHard() << endl;
    
    cout << "\n\nAttempting 100 removals: \n";
    for (k = 100; k > 0; k--)
    {
        if (search_tree.remove(k))
            cout << "removed " << k << endl;
    }
    search_tree.collectGarbage();
    
    cout << "\nsearch_tree now:\n";
    search_tree.traverse(int_printer);
    cout << "\ntree 1 size: " << search_tree.size() 
    << "  Hard size: " << search_tree.sizeHard() << endl;
    
    search_tree2.insert(500);
    search_tree2.insert(200);
    search_tree2.insert(300);
    search_tree2.insert(700);
    search_tree2.insert(100);
    search_tree2.insert(600);
    cout << "\nsearch_tree2:\n";
    search_tree2.traverse(int_printer);
    cout << "\ntree 2 size: " << search_tree2.size() 
    << "  Hard size: " << search_tree2.sizeHard() << endl;
    
    return 0;
}