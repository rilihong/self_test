//
// Created by rilihong on 17-11-2.
//
#include <vector>
#include <map>
#include "node_map.h"
#include "num_set.h"

typedef vector<int> v_list;

int min_num(int a,int b)
{
    if(a > b)
    {
        return b;
    }
    else
    {
        return a;
    }
}

void node_map::node_map_init(map<string,vector<dis_node>>& input_map)
{
    s_map = input_map;
    town_num = s_map.size();
    d_map = new int *[town_num];
    for(int i = 0;i<town_num;++i)
    {
        d_map[i]= new int [town_num];
    }
    for(int i = 0 ;i < town_num;++i)
    {
        for(int j = 0;j<town_num;++j)
        {
            d_map[i][j] = 0;
        }
    }
    //make string to number map
    int count_num = 0;
    for(map<string,vector<dis_node>>::iterator string_itr = input_map.begin()
            ; string_itr != input_map.end();++string_itr)
    {
        n_map[string_itr->first] = count_num++;
    }
    for(map<string,vector<dis_node>>::iterator string_itr = input_map.begin()
            ; string_itr != input_map.end();++string_itr)
    {
        vector<dis_node>& node_list = string_itr->second;
        string town_str = string_itr->first;
        int src_num = -1;
        change_to_number(town_str,src_num);
        for(vector<dis_node>::iterator node_itr = node_list.begin()
                ; node_itr != node_list.end();++node_itr)
        {
            int des_num = -1;
            change_to_number(node_itr->des_town,des_num);
            d_map[src_num][des_num] = node_itr->distance;
        }
    }
}

bool node_map::search_direct_router_by_node(vector <string> &town_list, int &distance)
{
    if(town_list.size() == 0 || town_list.size() == 1)
    {
        distance = 0;
        return true;
    }
    vector<int> num_list;
    if(!towns_change_to_list(town_list,num_list)
            || num_list.size() < 2)
    {
        return false;
    }
    vector<int>::iterator pre_itr = num_list.begin();
    vector<int>::iterator next_itr = pre_itr+1;
    int count = 0;
    while(next_itr != num_list.end())
    {
        if(d_map[*pre_itr][*next_itr] > 0)
        {
            count += d_map[*pre_itr][*next_itr];
            pre_itr = next_itr++;
        }
        else
        {
            break;
        }
    }
    if(next_itr != num_list.end())
    {
        return false;
    }
    distance = count;
    return true;
}


int node_map::search_shortest_router_distance(vector<string>& town_list)
{
    int count = 0;
    int* node_count_old = new int[town_num];
    int* node_count_new = new int[town_num];
    for(int i = 0;i < town_num;++i)
    {
        node_count_old[i] = -1;
        node_count_new[i] = -1;
    }
    vector<int> num_list;
    if(!towns_change_to_list(town_list,num_list)
       || num_list.size() != 2)
    {
        return 0;
    }
    int src = num_list.at(0);
    int des = num_list.at(1);
    node_count_old[src] = 0;
    bool dif = true;
    int step = 0;
    while(dif)
    {
        step++;
        for(int j = 0;j < town_num;++j)
        {
            if(node_count_old[j] > 0 || (step == 1 && node_count_old[j] == 0))
            {
                for(int k = 0;k < town_num;++k)
                {
                    if(d_map[j][k] > 0)
                    {
                        if(node_count_old[k] < 0)
                        {
                            int tmp_num = node_count_old[j] + d_map[j][k];
                            if(node_count_new[k] <= 0)
                            {
                                node_count_new[k] = tmp_num;
                            }
                            else
                            {
                                node_count_new[k] = min(node_count_new[k],tmp_num);
                            }
                        }
                        else
                        {
                            int tmp_num = min_num(node_count_old[k],node_count_old[j] + d_map[j][k]);
                            if(node_count_new[k] <= 0)
                            {
                                node_count_new[k] = tmp_num;
                            }
                            else
                            {
                                node_count_new[k] = min(node_count_new[k],tmp_num);
                            }

                        }
                    }
                    else
                    {
                        if(node_count_new[k] <= 0 && node_count_old[k] > 0)
                        {
                            node_count_new[k] = node_count_old[k];
                        }

                    }
                }
            }
        }
        dif = false;
        for(int i = 0;i < town_num;++i)
        {
            if(node_count_old[i] != node_count_new[i])
            {
                dif = true;
            }
            node_count_old[i] = node_count_new[i];
            node_count_new[i] = -1;
        }
    }
    count = node_count_old[des];
    delete []node_count_old;
    delete []node_count_new;
    return count;
}

bool node_map::change_to_number(string town,int &num)
{
    map<string,int>::iterator itr_name = n_map.find(town);
    if(itr_name == n_map.end())
    {
        return false;
    }
    num = itr_name->second;
    return true;
}

bool node_map::change_to_town(int num,string &town)
{
    for(map<string,int>::iterator itr_name = n_map.begin()
            ;itr_name != n_map.end();++itr_name)
    {
        if(itr_name->second == num)
        {
            town = itr_name->first;
            return true;
        }
    }
    return false;
}

bool node_map::list_change_to_towns(vector<int>& num_list,vector<string>& town_list)
{
    for(vector<int>::iterator itr = num_list.begin()
            ; itr != num_list.end();++itr)
    {
        string town = "";
        if(!change_to_town(*itr,town)
           || town == "")
        {
            return false;
        }
        town_list.push_back(town);
    }
    return true;
}

bool node_map::towns_change_to_list(vector<string>& town_list,vector<int>& num_list)
{
    for(vector<string>::iterator itr = town_list.begin()
            ; itr != town_list.end();++itr)
    {
        int num = -1;
        if(!change_to_number(*itr,num)
            || num == -1)
        {
            return false;
        }
        num_list.push_back(num);
    }
    return true;
}

void node_map::print_d_map()
{
    for(int i = 0 ; i < town_num;++i)
    {
        for(int j = 0 ; j < town_num;++j)
        {
            cout << d_map[i][j] << " ";
        }
        cout << "\n";
    }
}

void node_map::print_n_map()
{
    for(map<string,int>::iterator itr_name = n_map.begin()
            ;itr_name != n_map.end();++itr_name)
    {
        cout << itr_name->second << ":" << itr_name->first << endl;
    }
}

int node_map::search_exactly_step_by_node(vector<string>& town_list,int step)
{
    int count = 0;
    int* node_count_old = new int[town_num];
    int* node_count_new = new int[town_num];
    for(int i = 0;i < town_num;++i)
    {
        node_count_old[i] = 0;
        node_count_new[i] = 0;
    }
    vector<int> num_list;
    if(!towns_change_to_list(town_list,num_list)
       || num_list.size() != 2)
    {
        return 0;
    }
    int src = num_list.at(0);
    int des = num_list.at(1);
    node_count_old[src] = 1;
    for(int i = 1;i <= step;++i)
    {
        for(int j = 0;j < town_num;++j)
        {
            if(node_count_old[j] > 0)
            {
                for(int k = 0;k < town_num;++k)
                {
                    if(d_map[j][k] > 0)
                    {
                        node_count_new[k] += node_count_old[j];
                    }
                }
            }
        }

        for(int i = 0;i < town_num;++i)
        {
            node_count_old[i] = node_count_new[i];
            node_count_new[i] = 0;
        }
    }
    count = node_count_old[des];
    delete []node_count_old;
    delete []node_count_new;
    return count;
}

int node_map::search_max_step_by_node(vector<string>& town_list,int step)
{
    int count = 0;
    for(int i = 1;i <= step;++i)
    {
        int result = search_exactly_step_by_node(town_list,i);
        if(result == 0)
        {
            continue;
        }
        count += result;
    }
    return count;
}

int node_map::search_possible_router_count(vector<string>& town_list,int distance_limit)
{
    int count = 0;
    num_set* node_count_old = new num_set[town_num];
    num_set* node_count_new = new num_set[town_num];
    for(int i = 0;i < town_num;++i)
    {
        node_count_old[i] = num_set();
        node_count_new[i] = num_set();
    }
    vector<int> num_list;
    if(!towns_change_to_list(town_list,num_list)
       || num_list.size() != 2)
    {
        return 0;
    }
    int src = num_list.at(0);
    int des = num_list.at(1);
    node_count_old[src].int_list.push_back(0);
    int step = 0;
    while(step++ < distance_limit)
    {
        for(int j = 0;j < town_num;++j)
        {
            if(node_count_old[j].size() > 0)
            {
                if(step == 1)
                {
                    node_count_old[j].reset();
                }
                for(int k = 0;k < town_num;++k)
                {
                    if(d_map[j][k] > 0)
                    {
                        if(node_count_old[k].size() == 0)
                        {
                            num_set tmp_num = node_count_old[j];
                            tmp_num.num_set_add_num(d_map[j][k]);
                            node_count_new[k].num_set_add_set(tmp_num);
                        }
                        else
                        {
                            num_set tmp_num = node_count_old[j];
                            tmp_num.num_set_add_num(d_map[j][k]);
                            num_set tmp_num_1;
                            tmp_num_1.num_set_add_set(tmp_num);
                            node_count_new[k].num_set_add_set(tmp_num_1);
                        }
                    }
                }
            }
        }
        count += node_count_new[des].count_less_than_num(distance_limit);
        for(int i = 0;i < town_num;++i)
        {
            node_count_new[i].rm_big_than_num(distance_limit);
            node_count_old[i] = node_count_new[i];
            node_count_new[i].reset();
        }
    }
    delete []node_count_old;
    delete []node_count_new;
    return count;
}