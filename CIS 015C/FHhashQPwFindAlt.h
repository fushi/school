//
//  FHhashQPwFindAlt.h
//  CIS 015C
//
//  Created by John Towler on 5/16/11.
//  Copyright 2011. All rights reserved.
//

#ifndef FHHASHQPWFINDALT_H
#define FHHASHQPWFINDALT_H
#include "FHhashQP.h"

template <class Object>
class FHhashQPwFind: public FHhashQP<Object>{
public:
    const Object find(const Object & x);
    
public:
    class NotFoundException {};
};

template <class Object>
const Object FHhashQPwFind<Object>::find(const Object & x){
    
    //returns the found object, or throws a NotFoundException if it isn't there.
    //You will have to add a NotFoundException to the class.
    
    int position = this->findPos(x);
    
    if (this->m_array[position].state == this->ACTIVE)
        return this->m_array[position].data;
    
    throw NotFoundException();
}

#endif