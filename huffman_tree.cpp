//
//  huffman_tree.cpp
//  zip_file
//
//  Created by PAN on 16-5-11.
//  Copyright (c) 2016年 prowind. All rights reserved.
//

#include "huffman_tree.h"

int identity=0;
template<typename T>
tree_nodes<T>::tree_nodes()
{
    left_son=NULL;
    right_son=NULL;
};

template<typename T>
tree_nodes<T>::tree_nodes(T in_data)
{
    data=in_data;
    left_son=NULL;
    right_son=NULL;
};

template<typename T>
tree_nodes<T>::tree_nodes(double in_weight)
{
    weight=in_weight;
    left_son=NULL;
    right_son=NULL;
};

template<typename T>
tree_nodes<T>::tree_nodes(T in_data,tree_nodes<T> * in_left_son,tree_nodes<T> * in_right_son)
{
    data=in_data;
    left_son=in_left_son;
    right_son=in_right_son;
};



tree_nodes<char> * huffman_tree(vector<tree_nodes<char> *> node)  //根据权重建立huffman树;
{
    if (node.size()>2)
    {
        double min_1=10000000,min_2=10000000;
        int min_pos_1=0,min_pos_2=0;
        for (int i=0; i<node.size(); i++)
        {
            if (min_1>node[i]->weight)
            {
                min_1=node[i]->weight;
                min_pos_1=i;
            }
        }
        for (int i=0; i<node.size(); i++)
        {
            if (min_2>node[i]->weight && i!=min_pos_1)
            {
                min_2=node[i]->weight;
                min_pos_2=i;
            }                                                        //找出两个最小的
        }
        tree_nodes<char> * temp;
        temp=new tree_nodes<char>;
        temp->left_son=node[min_pos_1];
        temp->right_son=node[min_pos_2];
        temp->weight=node[min_pos_1]->weight+node[min_pos_2]->weight;
        node.push_back(temp);
        if (min_pos_1<min_pos_2)
        {
            node.erase(node.begin()+min_pos_1);
            node.erase(node.begin()+min_pos_2-1);
        }
        else
        {
            node.erase(node.begin()+min_pos_2);
            node.erase(node.begin()+min_pos_1-1);
        };                                  //把他俩权重弄一块搁后边
        
        return huffman_tree(node);//把这俩指针弄成一个节点搁后边 其实那个权重也放在树里的data位置
    }
    else
    {
        tree_nodes<char> * temp;
        temp=new tree_nodes<char>;
        temp->left_son=node[0];
        temp->right_son=node[1];
        temp->weight=node[0]->weight+node[1]->weight;
        return temp;
    }
};


vector<tree_nodes<char> *> build_sons(vector<int> in_weight)
{
    vector<tree_nodes<char> *> node;
    for (int i=0 ;i<in_weight.size() ;i++)
    {
        if (in_weight[i]!=0)
        {
        tree_nodes<char> * temp;
        temp=new tree_nodes<char>;
        temp->weight=in_weight[i];
        temp->data=(char) i;
        node.push_back(temp);
        }                                               //当权重不为零时 弄一列node
    }
    return node;
};


string get_the_code(char target, string &code,tree_nodes<char>* start )
{
    if (start==NULL)
        return "END";
    if (start->left_son!=NULL && get_the_code(target,code,start->left_son)!="END")
    {
        code="1"+code;
        return code;
    }
    else if (start->right_son!=NULL && get_the_code(target,code,start->right_son)!="END")
    {
        code="0"+code;
        return code;
    }
    else if ((char)start->data==target)
        return code;
    else return "END";
};
