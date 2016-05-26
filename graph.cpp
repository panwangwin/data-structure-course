//
//  main.cpp
//  graph
//
//  Created by PAN on 16-5-24.
//  Copyright (c) 2016年 prowind. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <algorithm>
using namespace std;

class percolate
{
private:
    int length;
    int *root;
    int *size;
    
public:
    
    percolate(int n);
    int find_root(int identity);
    void connect(int p, int q);
    bool is_connect(int i, int j);
    void open(int p);
    void root_to_root();
    int branches();
    
    bool in_it(int vertex,vector<int> group);
    vector<vector<int>> connected_branches;
    ~percolate();
    
};

int percolate::find_root(int identity)
{
    while (identity!=root[identity])
        identity=root[identity];
    return identity;
}

percolate::percolate(int n)
{
    length=n;
    root= new int [n];
    size= new int [n];
    for (int i=0; i<n;i++)
    {
        root[i]=i;
    }
    for (int i=1; i<n;i++)
    {
        size[i]=0;
    }
    size[0]=1;
    size[n-1]=1;
}

void percolate::connect(int p, int q)
{
    int i = find_root(p);
    int j = find_root(q);
    if (i != j)
    {
        if  (size[i] < size[j]) { root[i] = j; size[j] += size[i]; }
        else                { root[j] = i; size[i] += size[j]; }
    }
}

bool percolate::is_connect(int i, int j)
{
    if (find_root(i)==find_root(j))
        return 1;
    else return 0;
}

void percolate::root_to_root()
{
    for (int i=0;i<length;i++)
    {
        root[i]=find_root(i);
    }
}


bool percolate::in_it(int vertex,vector<int> group)//判断一个数是否在group里
{
    for(int i=0;i<group.size();i++)
    {
        if(vertex==group[i])
            return 1;
    }
    return 0;
}


int percolate::branches()
{
    vector<int> branch_roots;
    vector<int> dummy_r;
    int dummy;
    int max=0;
    int j=0;
    for (int i=0;i<length;i++)
    {
        dummy=find_root(i);
        if (!in_it(dummy,branch_roots))
            branch_roots.push_back(dummy);
    }
    for (int i=0;i<branch_roots.size();i++)
    {
        for (int j=0;j<length;j++)
            if(root[j]==branch_roots[i])
                dummy_r.push_back(j);
        connected_branches.push_back(dummy_r);
        dummy_r.clear();
    }
    for (int i=0; i<connected_branches.size(); i++)
    {
        if(max<connected_branches[i].size())
        {
            max=connected_branches[i].size();
            j=i;
        }
    }
    return j;
}



percolate::~percolate()
{
    delete size;
    delete root;
}




struct edge
{
    string protein_A;
    string protein_B;
    double weight;
};

struct hashed_edge
{
    int protein_A;
    int protein_B;
    double weight;
};

struct hash_table
{
    string vertex;
    int key;
};


int cmp( const void *a , const void *b )
{
    struct edge *c = (edge *)a;
    struct edge *d = (edge *)b;
    if(c->protein_A != d->protein_A) return strcmp((char *)c->protein_A.data(),(char*)d->protein_A.data());
    else return strcmp((char *)c->protein_B.data(),(char*)d->protein_B.data());
}


bool compare_weight(hashed_edge a, hashed_edge b)
{
    return a.weight<b.weight;
}



vector<edge> read(string filename) // 读入所有数据 返回all_edges为所有边的信息
{
    fstream in(filename);
    string dummy_protein_A,dummy_protein_B,dummy_taxon_A,dummy_taxon_B,dummy_str;
    double dummy_weight=0;
    edge dummy;
    vector<edge> all_edges;
    for (int i=0;i<498153;i++)
    {
        for (int j=0;j<8;j++)
            if (j<7)
            {
                getline(in,dummy_str,';');
                if (j==0)
                    dummy_protein_A=dummy_str;
                if (j==3)
                    dummy_protein_B=dummy_str;
                if (j==2)
                    dummy_taxon_A=dummy_str;
                if (j==5)
                    dummy_taxon_B=dummy_str;
                if (j==6)
                {
                    char *p=(char *)dummy_str.data();
                    dummy_weight=1/atof(p);
                }
            }
            else
            {
            getline(in,dummy_str,'\n');
            }
        if(dummy_taxon_A==dummy_taxon_B && dummy_taxon_A=="3702")
        {
            dummy.protein_A=dummy_protein_A;
            dummy.protein_B=dummy_protein_B;
            dummy.weight=dummy_weight;
            all_edges.push_back(dummy);
        }
    }
    return all_edges;
}

bool in_it(string vertex,vector<hash_table> group)//判断一个节点是否在group里
{
    for(int i=0;i<group.size();i++)
    {
        if(vertex==group[i].vertex)
            return 1;
    }
    return 0;
}




int find_it(string vertex,vector<hash_table> group)//判断一个节点是否在group里
{
    for(int i=0;i<group.size();i++)
    {
        if(vertex==group[i].vertex)
            return group[i].key;
    }
    return -1;
}

vector<hash_table> initiate_hash_table(vector<edge> all_edges)
{
    vector<hash_table> uf;
    hash_table dummy_uf;
    string dummy;
    for (int i=0; i<all_edges.size();i++)
    {
        dummy=all_edges[i].protein_A;
        if (!in_it(dummy, uf))
        {
            dummy_uf.vertex=all_edges[i].protein_A;
            dummy_uf.key=uf.size()+1;
            uf.push_back(dummy_uf);
        }
        dummy=all_edges[i].protein_B;
        if (!in_it(dummy, uf))
        {
            dummy_uf.vertex=all_edges[i].protein_B;
            dummy_uf.key=uf.size()+1;
            uf.push_back(dummy_uf);
        }
    }
    return uf;
}

vector<hashed_edge> translate(vector<edge> all_edges,vector<hash_table> all_keys)
{
    hashed_edge dummy;
    vector<hashed_edge> translated;
    for (int i=0; i<all_edges.size(); i++)
    {
        dummy.protein_A=find_it(all_edges[i].protein_A, all_keys);
        dummy.protein_B=find_it(all_edges[i].protein_B, all_keys);
        dummy.weight=all_edges[i].weight;
        translated.push_back(dummy);
    }
    return translated;
}

void gather(percolate &discrete,vector<hashed_edge> all_edges)
{
    for (int i=0; i<all_edges.size();i++)
    {
        discrete.connect(all_edges[i].protein_A, all_edges[i].protein_B);
    }
}


int Root(int i,vector<int> element)
{
    while (i != element[i])
        i = element[i];
    return i;
}



vector<int> Kruscal(vector<int> element,vector<hashed_edge> &e)
{
    //vector<int> element;
    for (int j = 0; j < element.size(); j++)
        element[j]=j;
    int ConnectedNum = element.size();
    vector<int> SaveEdge;
    int index = 0;
    int index_ = 0;
    while (ConnectedNum != 1)
    {
        if (Root(e[index_].protein_A,element) != Root(e[index_].protein_B,element))
        {
            element[Root(e[index_].protein_A, element)] = element[Root(e[index_].protein_B, element)];
            SaveEdge.push_back(index_);
            index++;
            index_++;
            ConnectedNum--;
        }
        else index_++;
    }
    return SaveEdge;
}

vector<hashed_edge> pick_up(vector<hashed_edge> full,vector<int> need_to_be_pick_up)
{
    vector<hashed_edge> picked_up;
    for (int i=0;i<need_to_be_pick_up.size();i++)
    {
        for (int j=0; j<full.size(); j++)
        {
            if(need_to_be_pick_up[i]==full[j].protein_A)
            {
                picked_up.push_back(full[j]);
                continue;
            }
            else if(need_to_be_pick_up[i]==full[j].protein_B)
            {
                picked_up.push_back(full[j]);
            }
        }
    }
    return picked_up;
}

void HashPlus(vector<int> &hash,vector<hashed_edge> &e)
{
    for (int index = 0; index < e.size(); index++)
    {
        for (int i = 0; i < hash.size(); i++)
        {
            if (e[index].protein_A != hash[i])
                continue;
            else e[index].protein_A = i;
        }
        for (int i = 0; i < hash.size(); i++)
        {
            if (e[index].protein_B != hash[i])
                continue;
            else e[index].protein_B = i;
        }
    }
}



vector<hash_table> all_keys_here;
vector<edge> all_edges_here;

int main()
{
    vector<int> a,final_tree_index;
    vector<hashed_edge> dict,picked_up;
    all_edges_here=read("/users/panou/desktop/ppi.txt");
    all_keys_here=initiate_hash_table(all_edges_here);
    percolate vertices(all_keys_here.size());
    dict=translate(all_edges_here,all_keys_here);
    gather(vertices,dict);
    vertices.root_to_root();
    a=vertices.connected_branches[vertices.branches()];
    picked_up=pick_up(dict, a);
    sort(picked_up.begin(),picked_up.begin()+picked_up.size(),compare_weight);
    HashPlus(a, picked_up);
    final_tree_index=Kruscal(a,picked_up);
    return 0;
}
