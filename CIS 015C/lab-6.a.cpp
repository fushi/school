//
//  lab-6.a.cpp
//  CIS 015C
//
//  Created by John Towler on 5/16/11.
//  Copyright 2011. All rights reserved.
//

#include "FHhashQPwFind.h"
#include "EBookEntry.h"

#define RAND_NUM 25

// ----------- prototypes -------------

//int getKey( const EBookEntry & item);
string getKey( const EBookEntry & item);

int hash_func(const int & key);
int hash_func(const EBookEntry & book);
int hash_func(const string & key);

int main(){
    
    EBookEntryReader book_input("catalog-short4.txt");
    EBookEntry book, query;
//    FHhashQPwFind<EBookEntry, int> hash_table;
    FHhashQPwFind<EBookEntry, string> hash_table;
    int random_indices[RAND_NUM];

    // We want two books to be identical in different ways:  ID or author
//    EBookEntry::SetNSortType(EBookEntry::SORT_BY_ID);
    EBookEntry::SetNSortType(EBookEntry::SORT_BY_CREATOR);
    
    cout << book_input.getFileName() << endl << endl;
    cout << book_input.getNumBooks() << endl << endl;
    
    // Insert Books into HashTable
    for (int i = 0; i < book_input.getNumBooks(); i ++)
        hash_table.insert(book_input[i]);
    
    // Create 25 random indices
    for (int j = 0; j < RAND_NUM; j++)
        random_indices[j] = rand() % book_input.getNumBooks();
    
    // List the books that should be matched
    for (int k = 0; k < RAND_NUM; k++) {
        book = book_input[random_indices[k]];
        
        cout << book.GetSCreator() << ": " << book.GetSTitle() << endl;
    }
    
    cout << endl << endl << endl;
    
    // Try to match the books previously listed
    for (int l = 0; l < RAND_NUM; l++) {
        try{
            
//            book = hash_table.find(book_input[random_indices[l]].GetNEtextNum());
            book = hash_table.find(book_input[random_indices[l]].GetSCreator());
            
            cout << book.GetSCreator() << ": " << book.GetSTitle() << endl;
        }
        
        catch (...){
            cout << "no.  " << endl;
        }
    }
    
    cout << endl << endl << endl;

    // Test known failures exceptions:
    try{
//        book = hash_table.find(1);
        book = hash_table.find("Jack Kerouac");
        
        cout << book.GetSCreator() << ": " << book.GetSTitle() << endl;
    }
    catch (...){
        cout << "no.  " << endl;
    }
}    
    

// used for author equality
string getKey(const EBookEntry & item){
    return item.GetSCreator() ;
}

// used for ID equality
//int getKey(const EBookEntry & item){
//    return item.GetNEtextNum() ;
//}

// Hash functions
int hash_func(const EBookEntry & book){
    return hash_func(getKey(book));
}

int hash_func(const string & key){
    unsigned int k, ret_val = 0;
    
    for(k = 0; k < key.length(); k++)
        ret_val = 37 * ret_val + key[k];
    
    return ret_val;
}

int hash_func(const int & key){
    return key;
}


