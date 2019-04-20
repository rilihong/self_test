//
// Created by rilihong on 17-11-2.
//

#ifndef TEST_1_NODE_H
#define TEST_1_NODE_H
#include <iostream>

using namespace std;
//distance node ,use to hold a distance input unit
struct dis_node{
    string src_town;        //source town
    string des_town;        //destination town
    int distance;

    dis_node():src_town(""),des_town(""),distance(0){}
    dis_node(string src,string des,int dis)
            :src_town(src),des_town(des),distance(dis){}
};


#endif //TEST_1_NODE_H
