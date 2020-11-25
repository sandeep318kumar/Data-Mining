#include<bits/stdc++.h>
using namespace std;

#define M 2
#define supp_percent 25
int min_supp;
int height_tree;
int transaction_size;

vector<vector<string>> G;
typedef struct node* LPTR;
struct node
{
    vector<string> val;
    vector<LPTR> comb;
    vector<LPTR> perm;
    int cnt;
};
map<vector<string>,int> shape_map;
map<vector<string>,LPTR> map_tree;
map<vector<string>,LPTR>::iterator itr1, itr2;

map<vector<string>,pair<int,int>> dashed_circle;
map<vector<string>,pair<int,int>>:: iterator d;
//first value is its count in the database
//second value no. of times it was in the dashed_circle
vector<vector<string>> dashed_square;
vector<vector<string>> to_be_deleted;

void take_input()
{
    int record_cnt = 0;
    ifstream fin("DICInput.txt");
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
    transaction_size = record_cnt;
    min_supp = (float)(supp_percent / 100) * record_cnt;
}

void print_arr(vector<string> A)
{
    for(int i=0; i<A.size(); i++)
    {
        cout<<A[i]<<" ";
    }
    cout<<endl;
}

void print_tree()
{
    for(itr1 = map_tree.begin(); itr1 != map_tree.end(); itr1++)
    {

        print_arr(itr1->first);
        cout<<"parents:"<<endl;
        for(int i=0; i<itr1->second->comb.size(); i++)
        {
            print_arr(itr1->second->comb[i]->val);
        }
        cout<<"children:"<<endl;
        for(int i=0; i<itr1->second->perm.size(); i++)
        {
            print_arr(itr1->second->perm[i]->val);
        }
        cout<<"---------"<<endl;
    }
}

vector<string> form_string()
{
    vector<string>  temp;
    for(int i=0; i<G.size(); i++)
    {
        for(int j=0; j<G[i].size(); j++)
        {
            if(find(temp.begin(), temp.end(), G[i][j]) == temp.end())
            {
                temp.push_back(G[i][j]);
            }
        }
    }
    height_tree = temp.size();
    return temp;
}

void generate_subsets()
{
    vector<string> sample = form_string();
    unsigned int pow_set_size = pow(2, sample.size());
    int counter, j;

    /*Run from counter 000..0 to 111..1*/
    for(counter = 0; counter < pow_set_size; counter++)
    {
        vector<string> temp;
        for(j = 0; j < sample.size(); j++)
        {
            if(counter & (1 << j))
                temp.push_back(sample[j]);
        }
        LPTR temp_node = new (node);
        temp_node->val = temp;
        temp_node->cnt = 0;
        map_tree.insert({temp, temp_node});
        shape_map.insert({temp, 0});
    }
}

bool AisSubsetB(vector<string> A, vector<string> B)
{
    for(int i=0; i<A.size(); i++)
    {
        if(find(B.begin(), B.end(), A[i]) == B.end())
            return false;
    }
    return true;
}

void create_tree()
{
    for(int i=0; i<height_tree; i++)
    {
        for(itr1=map_tree.begin(); itr1!=map_tree.end(); itr1++)
        {
            if(itr1->first.size() == i)
            {
                for(itr2 = map_tree.begin(); itr2 != map_tree.end(); itr2++)
                {
                    if(itr2->first.size() == i + 1 && AisSubsetB(itr1->first, itr2->first))
                    {
                        itr1->second->comb.push_back(itr2->second);
                        itr2->second->perm.push_back(itr1->second);
                    }
                }
            }
        }
    }
}

int main()
{
    take_input();
    generate_subsets();
    create_tree();
    //print_tree();
    itr1 = map_tree.begin();
    shape_map[itr1->first] = 4;
    for(int i=0; i<itr1->second->comb.size(); i++)
    {
        shape_map[itr1->second->comb[i]->val] = 1;
        dashed_circle.insert({itr1->second->comb[i]->val, {0, 0}});
    }
    cout<<"The Frequent Itemsets are"<<endl;
    int k = height_tree;
    while(k--)
    {
        for(int i=0; i<transaction_size; i=i+M)
        {
            for(int j=i; j<i+M; j++)
            {

                //count the freq of each string in dashed_circle
                for(d=dashed_circle.begin(); d!=dashed_circle.end(); d++)
                {
                    if(AisSubsetB(d->first, G[j]) == true)
                    {
                        d->second.first++;
                    }
                }
            }
            //scan the dashed_circle
            //  increase counter by 1
            //  if(cnt > min_supp)
            //      push it into dashed_square
            //      change value in shape_map from 1 to 2
            //      delete it from dashed_circle
            //      increase the cnt of its comb by 1
            //      if(the cnt of comb == val.size())
            //          add that to dashed_circle
            //          change its value in shape_map
            //del all values which are common in dashed_circle and to_be_deleted
            //to_be_deleted.clear()

            for(d=dashed_circle.begin(); d!=dashed_circle.end(); d++)
            {
                d->second.second = d->second.second+1;
                if(d->second.first > min_supp)
                {
                    dashed_square.push_back(d->first);
                    shape_map[d->first] = 2;
                    to_be_deleted.push_back(d->first);

                    itr1 = map_tree.find(d->first);
                    for(int i=0; i<itr1->second->comb.size(); i++)
                    {
                        itr1->second->comb[i]->cnt++;
                        if(itr1->second->comb[i]->cnt == itr1->second->comb[i]->val.size())
                        {
                            dashed_circle.insert({itr1->second->comb[i]->val, {0, 0}});
                            shape_map[itr1->second->comb[i]->val] = 1;
                        }
                    }
                }
            }
            for(int i=0; i<to_be_deleted.size(); i++)
            {
                dashed_circle.erase(to_be_deleted[i]);
            }
            to_be_deleted.clear();
        }

        //dashed_sqaure.clear()
        //del all values which are common in dashed_circle and to_be_deleted
        //to_be_deleted.clear()
       for(int i=0; i<dashed_square.size(); i++)
        {
            shape_map[dashed_square[i]] = 4;
            print_arr(dashed_square[i]);
        }
        for(d=dashed_circle.begin(); d!=dashed_circle.end(); d++)
        {
            if(d->second.second * M == transaction_size)
            {
                shape_map[d->first] = 3;
                to_be_deleted.push_back(d->first);
            }
        }
        dashed_square.clear();
        for(int i=0; i<to_be_deleted.size(); i++)
        {
            dashed_circle.erase(to_be_deleted[i]);
        }
        to_be_deleted.clear();
    }
    return 0;
}
