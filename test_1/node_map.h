//
// Created by rilihong on 17-11-2.
//

#ifndef TEST_1_NODE_MAP_H
#define TEST_1_NODE_MAP_H
#include "node.h"
#include <map>
#include <vector>

using namespace std;

struct node_map
{
    map<string,vector<dis_node>> s_map;     //key(town) + value(dis_node) those nodes direct link with town
    int town_num;                       //total town number
    int ** d_map;                       //1("A") to 2("b") distance map in (town_num*town_num):just like d_map[1][2], d_map[1*town_num + 2]
    map<string,int> n_map;              //town replaced number,for example "A" replace by 1 and "B" replace by 2,

    node_map():town_num(0),d_map(NULL){}

    //init s_map n_map d_map by input
    void node_map_init(map<string,vector<dis_node>>& input_map);

    //search router by direct router list
    bool search_direct_router_by_node(vector<string>& town_list,int& distance);

    //search in the exact step, if the des can not reach ,return 0 ,else return reach router count
    int search_exactly_step_by_node(vector<string>& town_list,int step);

    //search in the max step, if the des can not reach ,return 0 ,else return reach router count
    int search_max_step_by_node(vector<string>& town_list,int step);

    //find the shortest router distance, return 0 if can not reach ,else return shortest distance
    //use the breadth traversal algorithm ,just like Dijkstra's Algorithm
    int search_shortest_router_distance(vector<string>& town_list);

    //search all possible router count, return 0 if can not reach ,else return router count
    //use the breadth traversal algorithm , just like Dijkstra's Algorithm b
    int search_possible_router_count(vector<string>& town_list,int distance_limit);

    //change town to town number
    bool change_to_number(string town,int &num);

    //change number  to town
    bool change_to_town(int num,string &town);

    //change number list to town string
    bool list_change_to_towns(vector<int>& num_list,vector<string>& town_list);

    //change towns string to number list
    bool towns_change_to_list(vector<string>& town_list,vector<int>& num_list);

    // print d_map
    void print_d_map();
    // print n_map
    void print_n_map();

    ~node_map()
    {
        s_map.clear();
        n_map.clear();
        for(int i = 0;i<town_num;++i)
        {
            delete [](d_map[i]);
        }
        delete []d_map;
    }

};


#endif //TEST_1_NODE_MAP_H
