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
    const Object default_val;
    int row_size, col_size;
public:
    SparseMat(int r, int c, const Object & default_v);
    const Object & get(int r, int c);
    bool set(int r, int c, const Object &x);
    void clear();
    void showSubSquare(int start, int size);
    
    // Exception classes
    class OutOfBoundsException { };
};

template<class Object>
SparseMat<Object>::SparseMat(int r, int c, const Object & default_v):
    default_val(default_v), row_size(r), col_size(c){
    
    //Create a FHvector that has row_size FHlists in it
    for (int i = 0; i < row_size; i++) {
        MatRow foo;
        rows.push_back(foo);
    }
}

template<class Object>
const Object& SparseMat<Object>::get(int r, int c){
    
    if(r >= row_size || c >= col_size || r < 0 || c < 0)
        throw OutOfBoundsException();
    
    
    typename MatRow::iterator iter; 
    
    for(iter = rows[r].begin(); iter != rows[r].end(); ++iter){
        if ((*iter).getCol() == c)
            return (*iter).data;
    }
    return default_val;
}

template<class Object>
bool SparseMat<Object>::set(int r, int c, Object const &x){
    
    typename MatRow::iterator iter;
    
    if(r >= row_size || c >= col_size || r < 0 || c < 0)
        return false;
    
    // Empty the column, if it exists
    for(iter = rows[r].begin(); (iter != rows[r].end()) && ((*iter).getCol() <= c); ++iter){
        if ((*iter).getCol() == c){
            rows[r].erase(iter);
        }
    }
    
    // Add the value to the FHlist, if it isn't equal to the default value
    if(x != default_val){
        for(iter = rows[r].begin(); (iter != rows[r].end()) && ((*iter).getCol() <= c); ++iter);
        MatNode<Object> *temp = new MatNode<Object>(c, x);
        
        rows[r].insert(iter, *temp);
    }
    return true;
}

template<class Object>
void SparseMat<Object>::clear(){
    
    typename MasterCol::iterator iter;
    
    for(iter = rows.begin(); iter != rows.end(); ++iter){
        (*iter).clear();
    }
}

template<class Object>
void SparseMat<Object>::showSubSquare(int start, int size){
    
    if(start < 0 || size < 0 || start > row_size || start + size > row_size)
        throw OutOfBoundsException();
    
    for(int i = start; (i-start) < size; i++){
        for(int j = start; (j-start) < size; j++){
            printf("%2.0f ", get(i, j));
        }
        printf("\n\n");
    }
}

