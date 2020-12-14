//
//  FHhashQPwFind.h
//  CIS 015C
//
//  Created by John Towler on 5/16/11.
//  Copyright 2011. All rights reserved.
//

#ifndef FHHASHQPWFIND_H
#define FHHASHQPWFIND_H
#include "FHhashQP.h"
#include <string>
using namespace std;

extern int hash_func(const int & key);
extern int hash_func(const string & key);

template <class Object, typename KeyType>
class FHhashQPwFind: public FHhashQP<Object>{
public:
    const Object find(const KeyType & key);
    
private:
    int test(int foo);
    int myhashKey(const KeyType & key) const;
    int findPosKey(const KeyType & key) const;
    
public:
    class NotFoundException {};
};

template <class Object, typename KeyType>
const Object FHhashQPwFind<Object, KeyType>::find(const KeyType & key){
    
    int position = findPosKey(key);
    
    if (this->m_array[position].state == this->ACTIVE)
        return this->m_array[position].data;
    
    throw NotFoundException();
}

template <class Object, typename KeyType>
int FHhashQPwFind<Object, KeyType>::findPosKey( const KeyType & key ) const{
    
    int kth_odd_num = 1;
    int index = myhashKey(key);
    
    while ( this->m_array[index].state != this->EMPTY
           && getKey(this->m_array[index].data) != key ){
        index += kth_odd_num;  // k squared = (k-1) squared + kth odd #
        kth_odd_num += 2;   // compute next odd #
        if ( index >= this->m_table_size )
            index -= this->m_table_size;
    }
    
    return index;
}

template <class Object, typename KeyType>
int FHhashQPwFind<Object, KeyType>::myhashKey(const KeyType & key) const{
    
    int hash_val;
    
    hash_val = hash_func(key) % this->m_table_size;
    if(hash_val < 0)
        hash_val += this->m_table_size;
    
    return hash_val;
}

#endif