vector<int> finding_path(int source,int target,vector<int> size_teller,vector<hashed_edge> edges)
{
    vector<int> dummy;
    vector<int> dummy_path;
    vector<bool> mark;
    vector<bool> duplicate;
    vector<vector<int>> path;
    vector<double> temp_min_dis;
    dummy_path.push_back(source);
    for (int i=0;i<size_teller.size();i++)
    {
        temp_min_dis.push_back(99999999);
        mark.push_back(0);
        duplicate.push_back(0);
        path.push_back(dummy_path);
    }
    temp_min_dis[source]=0;
    dummy.push_back(source);
    while (exam_mark(mark))
    {
        mark[dummy[0]]=1;
        for (int i=0;i<size_teller.size();i++)
            duplicate[i]=0;
        vector<hashed_edge> picked_up=pick_up(edges, dummy);
        for (int i=0; i<picked_up.size(); i++)              //对于u更新temp_min_dis向量 即D向量
        {
            int identity;
            if (picked_up[i].protein_A==dummy[0])
                identity=picked_up[i].protein_B;
            else
                identity=picked_up[i].protein_A;
            if (duplicate[identity]==0)
            {
                if (temp_min_dis[identity]>temp_min_dis[dummy[0]]+picked_up[i].weight) // 如果大即更新
                {
                    temp_min_dis[identity]=temp_min_dis[dummy[0]]+picked_up[i].weight;
                    dummy_path=path[dummy[0]];
                    dummy_path.push_back(identity);
                    path[identity]=dummy_path;
                }
                duplicate[identity]=1;
            }
        }
        int min=99999999;
        int min_pos=-1;
        for (int i=0; i<size_teller.size(); i++)
            if (temp_min_dis[i]<min && mark[i]==0)
            {
                min_pos=i;
                min=temp_min_dis[i];
            }
        dummy[0]=min_pos;
    }
    cout<<temp_min_dis[target]<<endl;
    return path[target];
}
