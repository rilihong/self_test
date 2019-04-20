//
// Created by rilihong on 17-11-3.
//

#ifndef TEST_1_NUM_SET_H
#define TEST_1_NUM_SET_H
#include <vector>
#include <algorithm>
using namespace std;

struct num_set
{
    vector<int> int_list;

    // insert a set into current set
    void num_set_add_set(num_set & a);
    // add num to element of current set ,if set is empty ,add num into set
    void num_set_add_num(int add);
    //remove num (num >= limit_num ) in current set
    void rm_big_than_num(int limit_num);
    //count all num (num < limit_num) in current set ,return number of nums
    int count_less_than_num(int limit_num);

    int size();                 //int_list size
    void reset();               //clean int_list
    void print_set();           //print int_list for debug

    num_set(){}
};

#endif //TEST_1_NUM_SET_H
