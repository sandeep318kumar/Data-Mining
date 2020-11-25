#include<bits/stdc++.h>
using namespace std;

#define min_support_percentage 20
#define min_conf 0.5
int min_supp_global;

typedef vector<vector<string>> vvs;
typedef vector<string> vs;

vvs global_freq_itemset;
vector<int> global_freq_itemset_cnt;

int count_freq_of_string(vvs G, vs temp, int r, int partition_size)
{
    int cnt = 0;
    for(int i=r; i<r + partition_size; i++)
    {
        int sm = 0;
        for(int j=0; j<temp.size(); j++)
        {
            if(find(G[i].begin(), G[i].end(), temp[j]) != G[i].end())
                sm++;
        }
        if(sm == temp.size())
           cnt++;
    }
    return cnt;
}
int find_partition_size(int record_cnt)
{
    int i = 2;
    while(i <= record_cnt)
    {
        if(record_cnt % i == 0)
            return i;
        i++;
    }
    return record_cnt;
}
bool prune(vvs M, vs temp, int k)
{
    vs p;
    for(int i=1; i<temp.size(); i++)
    {
        p.push_back(temp[i]);
    }
    int ans = count_freq_of_string(M, p, 0, M.size());
    if(ans >= 1)
        return true;
    else
        return false;
}

vvs join(int k, vvs M, vvs G, vector<int> &next_int, int z, int partition_size)
{
    vvs next;
    for(int i=0; i<M.size()-1; i++)
    {
        for(int j=i+1; j<M.size(); j++)
        {
            int flag = 0;
            for(int r=0; r<k-1; r++)
            {
                if(M[i][r] != M[j][r])
                {
                    flag=1;
                    break;
                }
            }
            if(flag == 0)
            {
                vector<string> temp;
                int r = 0;
                for(;r<k-1; r++)
                {
                    temp.push_back(M[i][r]);
                }
                int p = r;
                for(;p<M[i].size(); p++)
                {
                    temp.push_back(M[i][p]);
                }
                for(;r<M[j].size(); r++)
                {
                    temp.push_back(M[j][r]);
                }
                if(prune(M, temp, k) == true)
                {
                    next.push_back(temp);
                    next_int.push_back(count_freq_of_string(G, temp, z, partition_size));
                }
            }
        }
    }
    return next;
}

vvs read_prev_file(string filename)
{
    ifstream fin(filename);
    vector<vector<string>> last_itr;
    string temp;
    while(getline(fin,temp))
    {
        stringstream ss(temp);
        string temp1;
        vector<string> S;
        while(getline(ss, temp1, ' '))
        {
            if(temp1[0] == 'I')
            S.push_back(temp1);
        }
        last_itr.push_back(S);
    }
    fin.close();
    return last_itr;
}

int main()
{
    //Taking input from AprioriInput.txt to vvs G
    vector<vector<string> > G;
    int record_cnt = 0;
    ifstream fin("input.txt");
    string temp;
    while(getline(fin, temp))
    {
        stringstream ss(temp);
        string temp1;
        vector<string> S;
        while(getline(ss, temp1, ' '))
        {
            if(temp1[0] != 'T')
                S.push_back(temp1);
        }
        record_cnt++;
        G.push_back(S);
    }
    fin.close();

    //The min_supp_global
    float a = ceil((record_cnt * min_support_percentage) / 100.0);
    (a >= 0.5) ? min_supp_global = floor(a) + 1 : min_supp_global = floor(a);

    int partition_size = find_partition_size(record_cnt);
    for(int r = 0; r < record_cnt; r += partition_size)
    {
        float b = ((partition_size * min_support_percentage) / 100.0);
        int min_supp_local;
        (b >= 0.5) ? min_supp_local = floor(b) + 1 : min_supp_local = floor(b);
        //Finding  C1
        map<string, int> L1;
        for(int i = r; i < r + partition_size; i++)
        {
            for(int j = 0; j < G[i].size(); j++)
            {
                L1[G[i][j]]++;
            }
        }
        //Putting C1 to AprioriOutput.txt and prev.txt
        ofstream fout1("Output.txt");
        ofstream fout2("prev.txt");
        map<string, int> :: iterator itr;
        fout1<<"L1"<<" "<<endl;
        for(itr=L1.begin(); itr!=L1.end(); itr++)
        {
            fout1<<itr->first<<" "<<itr->second<<" "<<endl;
            fout2<<itr->first<<" "<<itr->second<<" "<<endl;
            if(itr->second > min_supp_local)
            {
                global_freq_itemset.push_back({itr->first});
                global_freq_itemset_cnt.push_back(itr->second);
            }
        }
        fout2.close();

        //Now we will generate itemsets of size >= 2
        int k = 2;
        while(1)
        {
            //reading previous Itemsets and storing it in M
            vvs M = read_prev_file("prev.txt");
            //Generating the next Itemset using the prev one
            //by join step
            //the new itemset generated is stored in vvs next
            //and the count of that itemset is stored in next_int
            vector<int> next_int;
            vvs next = join(k - 1, M, G, next_int, r, partition_size);

            if(next.size() == 0)
                break;

            fout1<<"L"<<k<<" "<<endl;
            //Output the new Itemset from vvs next to AprioriOutput.txt and prev.txt
            ofstream fout3;
            int flag = 0;
            for(int e=0; e<next_int.size(); e++)
            {
                for(int s=0; s<next[e].size(); s++)
                {
                    if(next_int[e] >= min_supp_local)
                    {
                        if(flag == 0)
                        {
                            flag = 1;
                            fout3.open("prev.txt");
                        }
                        fout1<<next[e][s]<<" ";
                        fout3<<next[e][s]<<" ";
                    }
                }
                if(next_int[e] >= min_supp_local)
                {
                    fout1<<next_int[e]<<" "<<endl;
                    fout3<<endl;
                    global_freq_itemset.push_back(next[e]);
                    global_freq_itemset_cnt.push_back(next_int[e]);
                }
            }
            k++;
        }
    }

    cout<<"The Shortlisted frequent itemsets are "<<endl;
    vector<int> mark(global_freq_itemset.size(), 0);
    for(int i=0; i<global_freq_itemset.size(); i++)
    {
        if(mark[i] == 1)
            continue;
        int cnt = 0;
        cnt += global_freq_itemset_cnt[i];
        mark[i] = 1;
        for(int j=i+1; j<global_freq_itemset.size(); j++)
        {
            if(global_freq_itemset[i] == global_freq_itemset[j] && mark[j] == 0)
            {
                mark[j] = 1;
                cnt += global_freq_itemset_cnt[j];
            }
        }
        if(cnt >= min_supp_global)
        {
            for(int k=0; k<global_freq_itemset[i].size(); k++)
            {
                cout<<global_freq_itemset[i][k]<<" ";
            }
            cout<<"->"<<" "<<cnt<<endl;
        }
    }
    return 0;
}
