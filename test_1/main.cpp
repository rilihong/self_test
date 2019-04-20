#include <iostream>
#include <vector>
#include <fstream>
#include "node.h"
#include "node_map.h"

using namespace std;

void error_info(string err_info)
{
    cout << err_info << endl;
}

bool get_distance_pair(std::vector<string>& pair)
{
    char buf[1024] = {0};
    ifstream in_f("input.txt",ifstream::in);
    if (!in_f.is_open())
    {
        error_info("read file error!");
        return false;
    }
    if (in_f.eof())
    {
        error_info("less than one line!");
    }
    in_f.getline (buf,1024);

    //cut chars into string
    char * head = buf;
    while(*head == ' ')
    {
        head++;
    }
    string input_str = head;

    string head_str = input_str.substr(0,6);
    if(head_str != "Graph:")
    {
        error_info("Error Head!");
        return false;
    }
    char* begin = head + 6;
    char* end = begin;
    while(*end != '\n' && *end != '\0')
    {
        if(*end == ',')
        {
            if(begin != end)
            {
                string unit_str = input_str.substr(begin-head,(end - begin));
                pair.push_back(unit_str);
            }
            begin = ++end;
        }
        else
        {
            end++;
        }
    }
    if(begin != end)
    {
        string unit_str = input_str.substr(begin-head,(end - begin));
        pair.push_back(unit_str);
    }
    return true;
}

bool get_node_data(std::vector<string>& pair,std::vector<dis_node>& output)
{
    for(std::vector<string>::iterator itr = pair.begin()
            ;itr != pair.end();++itr)
    {
        const char * c_head = itr->c_str();
        const char * c_begin = c_head;
        while(*c_begin == ' ')
        {
            c_begin++;
        }
        if(*c_begin < 'A' || *c_begin > 'Z')
        {
            return false;
        }
        string src = itr->substr(c_begin - c_head,1);
        c_begin++;
        if(*c_begin < 'A' || *c_begin > 'Z')
        {
            return false;
        }
        string des = itr->substr(c_begin - c_head,1);
        c_begin++;
        string num_str = itr->substr(c_begin - c_head);
        int value = std::stoi(num_str);
        dis_node node(src,des,value);
        output.push_back(node);
    }
    return true;
}

void create_town_node_struct(std::vector<dis_node>& input,map<string,vector<dis_node>>& input_map)
{
    for(std::vector<dis_node>::iterator itr = input.begin()
            ; itr != input.end();++itr)
    {
        map<string,vector<dis_node>>::iterator map_itr = input_map.find(itr->src_town);
        if(map_itr == input_map.end())
        {
            vector<dis_node> dis_list;
            dis_list.push_back(*itr);
            input_map[itr->src_town] = dis_list;
        }
        else
        {
            map_itr->second.push_back(*itr);
        }
        map<string,vector<dis_node>>::iterator des_itr = input_map.find(itr->des_town);
        if(des_itr == input_map.end())
        {
            vector<dis_node> dis_list;
            input_map[itr->des_town] = dis_list;
        }
    }
}

int main() {

    std::vector<string> distance_pair;
    if(!get_distance_pair(distance_pair))
    {
        error_info("error input data!");
        return -1;
    }
    std::vector<dis_node> input;
    if(!get_node_data(distance_pair,input))
    {
        error_info("error node data!");
        return -1;
    }
    map<string,vector<dis_node>> input_map;
    create_town_node_struct(input,input_map);

    node_map load_map;
    load_map.node_map_init(input_map);
    vector<string> question[5];
    question[0].push_back("A");question[0].push_back("B");question[0].push_back("C");
    question[1].push_back("A");question[1].push_back("D");
    question[2].push_back("A");question[2].push_back("D");question[2].push_back("C");
    question[3].push_back("A");question[3].push_back("E");question[3].push_back("B");question[3].push_back("C");question[3].push_back("D");
    question[4].push_back("A");question[4].push_back("E");question[4].push_back("D");

    for(int i = 0;i < 5;++i)
    {
        int q_result = 0;
        if(load_map.search_direct_router_by_node(question[i],q_result))
        {
            cout << "Output #" <<(i+1) <<":"  << q_result << endl;
        }
        else
        {
            cout << "Output #" <<(i+1) <<":"  << "NO SUCH ROUTE" << endl;
        }
    }

    vector<string> question_6;
    question_6.push_back("C");question_6.push_back("C");
    int result = load_map.search_max_step_by_node(question_6,3);
    cout << "Output #6:"  << result << endl;

    vector<string> question_7;
    question_7.push_back("A");question_7.push_back("C");
    result = load_map.search_exactly_step_by_node(question_7,4);
    cout << "Output #7:"  << result << endl;

    vector<string> question_8;
    question_8.push_back("A");question_8.push_back("C");
    result = load_map.search_shortest_router_distance(question_8);
    cout << "Output #8:"  << result << endl;

    vector<string> question_9;
    question_9.push_back("B");question_9.push_back("B");
    result = load_map.search_shortest_router_distance(question_9);
    cout << "Output #9:"  << result << endl;

    vector<string> question_10;
    question_10.push_back("C");question_10.push_back("C");
    result = load_map.search_possible_router_count(question_10,30);
    cout << "Output #10:"  << result << endl;
    return 0;
}