//
//  sublist.h
//  CIS 015C
//
//  Created by John Towler on 4/4/11.
//  Copyright 2011. All rights reserved.
//

#include <vector>
#include <iostream>

template<class T>
class Sublist{
public:
    Sublist(){}
    Sublist(const std::vector<T> *inc_list);
    Sublist(const std::vector<T> *inc_list, std::vector<int> *inc_indices, int old_sum);
    Sublist addItem(int index_to_add);
    void showSublist() const;
    int getSum() const;

private:
    const std::vector<T> *list;
    std::vector<int> indices;
    short sum;
};

#pragma once
template<class T>
Sublist<T>::Sublist(const std::vector<T> *inc_list)
    :sum(0), list(inc_list){
}

template<class T>
Sublist<T>::Sublist(const std::vector<T> *inc_list, std::vector<int> *inc_indices, int old_sum)
    :sum(old_sum), list(inc_list), indices(*inc_indices){
        
    sum = sum + (*list)[indices.back()];
}

template<class T>
Sublist<T> Sublist<T>::addItem(int index_to_add){
    std::vector<int> new_indices = indices;
    
    new_indices.push_back(index_to_add);
    
    return Sublist(list, &new_indices, sum);
}

template<class T>
void Sublist<T>::showSublist() const{
    printf("The sum was: %d\n", sum);
    
    std::vector<int>::const_iterator iter;
    
    for (iter = indices.begin(); iter != indices.end(); iter++){        
        printf("array[%d] = ", *iter);
        std::cout << (*list)[*iter] << std::endl;
    }
}

template<class T>
int Sublist<T>::getSum() const{
    return sum;
}

template<typename K>
Sublist<K> knapsack(const std::vector<K> *data_set, int target){
    
    std::vector<Sublist<K> > choices, choices_temp;
    typename std::vector<K>::const_iterator data_iter;
    typename std::vector<Sublist<K> >::iterator choices_iter;
    int new_sum, current_high = 0;
    Sublist<K> result, temp;
    
    //Initialize choices with an empty sublist
    choices.push_back(Sublist<K>(data_set));
    
    for(data_iter = data_set->begin(); data_iter != data_set->end(); data_iter++){
        
        for(choices_iter = choices.begin(); choices_iter != choices.end(); choices_iter++){
            
            new_sum = choices_iter->getSum() + *data_iter;
            
            if (new_sum == target){
                //Found a perfect match. End loops!
                result = choices_iter->addItem((int) std::distance(data_set->begin(), data_iter));
                choices_iter = choices.end() - 1;
                data_iter = data_set->end() - 1;
            }
            else if (new_sum < target){
                //Found a match. Add it to to a temp vector.
                temp = choices_iter->addItem((int) std::distance(data_set->begin(), data_iter));
                
                if (new_sum > current_high) {
                    //Found the best match thus far!
                    current_high = new_sum;
                    result = temp;
                }
                choices_temp.push_back(temp);
            }
        }
        choices.insert(choices.end(), choices_temp.begin(), choices_temp.end());
        choices_temp.clear();
    }
    return result;
}