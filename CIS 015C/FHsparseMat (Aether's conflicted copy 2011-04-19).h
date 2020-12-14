//
//  FHsparseMat.h
//  CIS 015C
//
//  Created by John Towler on 4/12/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "FHlist.h"
#include "FHvector.h"
#include <stdio.h>

using namespace std;

template<class Object>
class MatNode{
private:    
    int col;
    
public:
    Object data;
    // We need a default constructor for lists
    MatNode(int cl = 0, Object dt = Object());
    int getCol() const;
    const Object & operator=(const Object &x);
};

template<class Object>
MatNode<Object>::MatNode(int cl, Object dt) : col(cl), data(dt){
    
}

template<class Object>
int MatNode<Object>::getCol() const{
    return col;
}

template<class Object>
const Object & MatNode<Object>::operator=(const Object &x){
    return (data = x);
}


template<class Object>
class SparseMat{

typedef FHlist<MatNode<Object> > MatRow;
typedef FHvector<MatRow> MasterCol;
    
private:
    MasterCol rows;
    Object default_val;
    int row_size, col_size;
public:
    SparseMat(int r, int c, const Object & default_val);
    Object & get(int r, int c);
    bool set(int r, int c, const Object &x);
    void clear();
    void showSubSquare(int start, int size);
};

template<class Object>
SparseMat<Object>::SparseMat(int r, int c, const Object & default_val){
    //Create a FHvector that has r FHlists in it
    for (int i = 0; i < r; i++) {
        MatRow foo;
        rows.push_back(foo);
    }
}

template<class Object>
Object& SparseMat<Object>::get(int r, int c){
    
    typename MatRow::iterator iter; 
    
    for(iter = rows[r].begin(); iter != rows[r].end(); ++iter){
        if ((*iter).getCol() == c)
            return (*iter).data;
    }
    return default_val;
}

template<class Object>
bool SparseMat<Object>::set(int r, int c, Object const &x){
    
    
    printf("Foo\n\n");
    printf("\n\nx is: %x\n\n", x);
    if(r >= row_size || c >= col_size)
        return false;
    
    typename MatRow::iterator iter;
    
//    for(iter = rows[r].begin(); (iter != rows[r].end()) && ((*iter).getCol() <= c); ++iter){
//        if ((*iter).getCol() == c){
//            rows[r].erase(iter);
//        }
//    }
    

    
    if(x != default_val){
        for(iter = rows[r].begin(); (iter != rows[r].end()) && ((*iter).getCol() <= c); ++iter);
        rows[r].insert(iter, x);
    }
    return true;
}
  



