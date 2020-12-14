//
//  FHsplayTree.h
//  CIS 015C
//
//  Created by John Towler on 5/12/11.
//  Copyright 2011. All rights reserved.
//

#ifndef FHSPLAYTREE_H
#define FHSPLAYTREE_H
#include "FHsearch_tree.h"

// FHsplayTree Class Definition
template <class Comparable>
class FHsplayTree : public FHsearch_tree<Comparable>{
public:
    // Overridden
    bool insert(const Comparable &x);
    bool remove(const Comparable &x);
    bool contains (const Comparable &x);
    const Comparable & find(const Comparable &x);
    
    // Class
    const Comparable & showRoot();
    
protected:
    // Class
    void splay(FHs_treeNode<Comparable> * &root, const Comparable &x);
    void rotateWithLeftChild(FHs_treeNode<Comparable> * &k2);
    void rotateWithRightChild(FHs_treeNode<Comparable> * &k2);
};

// FHsplayTree Public Method Definitions
template <class Comparable>
bool FHsplayTree<Comparable>::insert(const Comparable &x){
    
    FHs_treeNode<Comparable> *new_node;
    
    if (this->m_root == NULL) {
        this->m_root = new FHs_treeNode<Comparable>(x, NULL, NULL);
        return true;
    }
    
    splay(this->m_root, x);
    
    if (x < this->m_root->data) {
        new_node = new FHs_treeNode<Comparable>(x, NULL, NULL);
        
        new_node->l_child = this->m_root->l_child;
        new_node->r_child = this->m_root;
        this->m_root = new_node;
        
        this->m_size++;
        return true;
    }
    
    if (this->m_root->data < x){
        new_node = new FHs_treeNode<Comparable>(x, NULL, NULL);
        
        new_node->r_child = this->m_root->r_child;
        new_node->l_child = this->m_root;
        this->m_root = new_node;
        
        this->m_size++;
        return true;
    }
    
    return false;
}

template <class Comparable>
bool FHsplayTree<Comparable>::remove(const Comparable &x){
    
    FHs_treeNode<Comparable> *new_root;
    
    if (this->m_root == NULL)
        return false;

    splay(this->m_root, x);
    
    if (this->m_root->data != x)
        return false;
    
    if (this->m_root->l_child == NULL)
        new_root = this->m_root->r_child;

    else{
        new_root = this->m_root->l_child;
        
        splay(new_root, x);
        
        new_root->r_child = this->m_root->r_child;
    }
    
    delete this->m_root;
    
    this->m_root = new_root;
    
    return true;
}

template <class Comparable>
bool FHsplayTree<Comparable>::contains(const Comparable &x){
    splay(this->m_root, x);
    if (this->m_root->data == x)
        return true;
    return false;
}

template <class Comparable>
const Comparable & FHsplayTree<Comparable>::find(const Comparable &x){
    splay(this->m_root, x);
    if (this->m_root->data == x)
        return showRoot();
    return NULL;
}

template <class Comparable>
const Comparable & FHsplayTree<Comparable>::showRoot(){
    return this->m_root->data;
}

// FHsplayTree Protected Method Definitions
template <class Comparable>
void FHsplayTree<Comparable>::splay(FHs_treeNode<Comparable> * &root,
                                    const Comparable &x){
    FHs_treeNode<Comparable> *r_tree = NULL, *l_tree = NULL, 
                            *r_min = NULL, *l_max = NULL;
    
    while(root != NULL){
        //Left
        if (x < root->data) {
        
            if(root->l_child == NULL)
                break;
            
            if(x < root->l_child->data){
                rotateWithLeftChild(root);
                
                if(root->l_child == NULL)
                    break; 
            }
            
            if (r_tree == NULL) {
                r_tree = root;
                r_min = r_tree;
            }
            else{
                r_min->l_child = root;
                r_min = r_min->l_child;
            }
            
            root = root->l_child;
        }
        
        // Right
        else if (root->data < x) {
            
            if(root->r_child == NULL)
                break;
            
            if(root->r_child->data < x){
                rotateWithRightChild(root);
                
                if(root->r_child == NULL)
                    break; 
            }
            
            if (l_tree == NULL) {
                l_tree = root;
                l_max = l_tree;
            }
            else{
                l_max->r_child = root;
                l_max = l_max->r_child;
            }
            
            root = root->r_child;
        }
        
        else
            break;
    }
        
    if (l_tree != NULL) {
        
        l_max->r_child = root->l_child;
        root->l_child = l_tree;
    }
    
    if (r_tree != NULL) {
        r_min->l_child = root->r_child;
        root->r_child = r_tree;
    }
    
}

template <class Comparable>
void FHsplayTree<Comparable>::rotateWithLeftChild(
    FHs_treeNode<Comparable> *&k2){
    
    FHs_treeNode<Comparable> *k1 = k2->l_child;
    k2->l_child = k1->r_child;
    k1->r_child = k2;
    k2 = k1;
}

template <class Comparable>
void FHsplayTree<Comparable>::rotateWithRightChild(
    FHs_treeNode<Comparable> *&k2){
    
    FHs_treeNode<Comparable> *k1 = k2->r_child;
    k2->r_child = k1->l_child;
    k1->l_child = k2;
    k2 = k1;    
}
#endif