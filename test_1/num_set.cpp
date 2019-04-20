//
// Created by rilihong on 17-11-3.
//

#include "num_set.h"
#include <iostream>

bool compare_num(int a,int b)
{
    if(a < b)
    {
        return true;
    }
    return false;
}

void num_set::num_set_add_set(num_set & a)
{
    for(vector<int>::iterator itr_a = a.int_list.begin()
        ; itr_a != a.int_list.end();++itr_a)
    {
        int_list.push_back(*itr_a);
    }
    sort(int_list.begin(),int_list.end(),compare_num);
}

void num_set::num_set_add_num(int add)
{
    if(int_list.size() == 0)
    {
        int_list.push_back(add);
    }
    else
    {
        for(vector<int>::iterator itr = int_list.begin()
                ; itr != int_list.end();++itr)
        {
            *itr += add;
        }
    }

    std::sort(int_list.begin(),int_list.end(),compare_num);
}

void num_set::rm_big_than_num(int limit_num)
{
    for(vector<int>::iterator itr = int_list.begin()
            ; itr != int_list.end();)
    {
        if(*itr >= limit_num)
        {
            itr = int_list.erase(itr);
        }
        else
        {
            ++itr;
        }
    }
}
int num_set::count_less_than_num(int limit_num)
{
    int count = 0;
    for(vector<int>::iterator itr = int_list.begin()
            ; itr != int_list.end();++itr)
    {
        if(*itr < limit_num && *itr > 0)
        {
            count++;
        }
    }
    return count;
}

int num_set::size()
{
    return int_list.size();
}

void num_set::reset()
{
    int_list.clear();
}

void num_set::print_set()
{
    if(int_list.size() == 0)
    {
        cout << "NULL";
    }
    for(vector<int>::iterator itr = int_list.begin()
            ;itr != int_list.end();++itr)
    {
        cout << *itr << " ";
    }
    cout << "\n";
}