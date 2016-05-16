//
//  huffman_tree.h
//  zip_file
//
//  Created by PAN on 16-5-11.
//  Copyright (c) 2016年 prowind. All rights reserved.
//

#ifndef __zip_file__huffman_tree__
#define __zip_file__huffman_tree__

#include <stdio.h>

#endif /* defined(__zip_file__huffman_tree__) */
#ifndef vector_staff
#define vector_staff

#include <iostream>
#include <vector>
#include <string>

#endif

using namespace std;

template<typename T>
class tree_nodes//树类
{
    /*friend void left_traversal(tree_nodes<T> * father, vector<tree_nodes<T> *> & l_t );//先序遍历
    friend void middle_traversal(tree_nodes<T> * father, vector<tree_nodes<T> *> & m_t);//中序遍历
    friend tree_nodes<T> * huffman_tree(vector<T> weight,vector<tree_nodes<T> *> node);//根据权重建立huffman树
    friend vector<tree_nodes<T> *> build_sons(vector<T> in_weight);//弄一列node
    friend void left_traversal_data(vector<T> &data , tree_nodes<T> * father );//先序遍历 最后的数组是存data
    friend void middle_traversal_data(vector<T>  &data, tree_nodes<T> * father);//中序遍历 最后的数组是存data
    friend tree_nodes<T> * recover_tree(T *left, T *mid, int dist);// 输入先序遍历 中序遍历 和 串长度 建立二叉树
    friend string get_the_code(T target, string &code,tree_nodes<T>* start);*/

public:
    tree_nodes();
    tree_nodes(T in_data);
    tree_nodes(T in_data,tree_nodes<T> * in_left_son,tree_nodes<T> * in_right_son);
    tree_nodes(double in_weight);
    

    T data;
    double weight;
    tree_nodes<T> * left_son;
    tree_nodes<T> * right_son;

};



tree_nodes<char> * huffman_tree(vector<tree_nodes<char> *> node);//根据权重建立huffman树

string get_the_code(char target, string &code,tree_nodes<char>* start);

vector<tree_nodes<char> *> build_sons(vector<int> in_weight);//弄一列node


