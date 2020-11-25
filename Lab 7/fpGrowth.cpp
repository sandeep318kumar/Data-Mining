#include<bits/stdc++.h>
using namespace std;

#define min_sup 2
typedef struct node* LPTR;
map<string, int> L1;
vector<pair<string, LPTR>> map_nodes;

struct node{
    vector<LPTR> child;
    string item;
    int count;
    LPTR next;
};

bool compare1(string x, string y){
    return (L1[x] > L1[y]);
}

LPTR new_node(string k){
    LPTR temp = new (struct node);
    temp->item = k;
    temp->count = 1;
    temp->next = NULL;
    return temp;
}

LPTR new_node(string k, int count){
    LPTR temp = new (struct node);
    temp->item = k;
    temp->count = count;
    temp->next = NULL;
    return temp;
}

int search_map_nodes(string k){
    for(int i=0; i<map_nodes.size(); i++)
    {
        if(map_nodes[i].first == k)
            return i;
    }
    return -1;
}

void insert(vector<string> trans, LPTR &p, int i){
    if(i == trans.size())
        return ;
    int flag = 0;
    for(int j=0; j<p->child.size(); j++)
    {
        if(p->child[j]->item == trans[i])
        {
            flag = 1;
            p->child[j]->count++;
            insert(trans, p->child[j], i + 1);
            break;
        }
    }
    if(flag == 0)
    {
        LPTR temp = new_node(trans[i]);
        int f = search_map_nodes(trans[i]);
        if(map_nodes[f].second != NULL)
        {
            LPTR ptr = map_nodes[f].second;
            while(ptr->next != NULL)
            {
                ptr = ptr->next;
            }
            ptr->next = temp;
        }
        else{
            map_nodes[f].second = temp;
        }
        p->child.push_back(temp);
        insert(trans, p->child[p->child.size() - 1], i + 1);
    }
}

void insert2(vector<string> trans, LPTR &p, int i, int count){
    if(i == trans.size())
        return ;
    int flag = 0;
    for(int j=0; j<p->child.size(); j++)
    {
        if(p->child[j]->item == trans[i])
        {
            flag = 1;
            p->child[j]->count += count;
            insert2(trans, p->child[j], i + 1, count);
            break;
        }
    }
    if(flag == 0)
    {
       LPTR temp = new_node(trans[i], count);
        p->child.push_back(temp);
        insert2(trans, p->child[p->child.size() - 1], i + 1, count);
    }
}

void printTree(LPTR p, vector<pair<string, int>> path){
    path.push_back({p->item, p->count});
    for(int i=0; i<p->child.size(); i++)
    {
        printTree(p->child[i], path);
    }
    if(p->child.size() == 0)
    {
        for(int i=1; i<path.size(); i++)
        {
            cout<<path[i].first<<":"<<path[i].second<<"  ";
        }
        cout<<endl;
    }
    path.pop_back();
}

void traverseTree(LPTR p, LPTR target, vector<string> path, vector<string> &target_path)
{
    if(p == target)
    {
        target_path = path;
        return;
    }
    path.push_back(p->item);
    for(int i=0; i<p->child.size(); i++)
    {
        traverseTree(p->child[i], target, path, target_path);
    }
}

void findFrequentItemsets(LPTR p,vector<string> path, string turn , int count)
{
    if(p == NULL)
        return ;
    if(p->count < min_sup && p->item != "{}")
    {
        return;
    }
    if(p->count >= min_sup)
    {
        cout<<p->item<<" "<<turn<<" : "<<p->count<<endl;
        path.push_back(p->item);
        count = p->count;
        if(path.size() >= 2)
        {
            for(int i=0; i<path.size(); i++)
            {
                cout<<path[i]<<" ";
            }
            cout<<turn<<" : "<<count<<endl;
        }
    }
    for(int i=0; i<p->child.size(); i++)
    {
        findFrequentItemsets(p->child[i], path, turn, count);
    }
    if(path.size() > 0)
        path.pop_back();
}

void cleanTree(LPTR &root){
    for(int i=0; i<root->child.size(); i++)
    {
        cleanTree(root->child[i]);
    }
    delete root;
}

int main()
{
    //Taking input from AprioriInput.txt to vvs G
    vector<vector<string>> G;
    int record_cnt = 0;
    ifstream ifs("AprioriInput.txt");
    string temp;
    while(getline(ifs, temp))
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
    ifs.close();

    //Finding  C1
    for(int i=0; i<G.size(); i++)
    {
        for(int j=0; j<G[i].size(); j++)
        {
            L1[G[i][j]]++;
        }
    }

    vector<string> temp_arr;
    for(map<string, int>::iterator itr = L1.begin(); itr != L1.end(); itr++)
    {
        temp_arr.push_back(itr->first);
    }
    sort(temp_arr.begin(), temp_arr.end(), compare1);

    for(int i=0; i<temp_arr.size(); i++)
    {
        map_nodes.push_back({temp_arr[i], NULL});
    }

    LPTR T;
    T = new_node("{}");
    for(int i=0; i<G.size(); i++)
    {
        sort(G[i].begin(), G[i].end(), compare1);
        insert(G[i], T, 0);
    }

    vector<pair<string, int>> path;
    printTree(T, path);
    cout<<"\n***Main Tree is Created***\n"<<endl;

    for(int i=map_nodes.size()-1; i>0; i--)
    {
        LPTR f = map_nodes[i].second;
        cout<<"The Frequent Itemsets of "<<" ";
        cout<<map_nodes[i].first<<endl;
        LPTR head = new_node("{}");
        while(f != NULL)
        {
            vector<string> temp;
            vector<string> path;
            traverseTree(T, f, path, temp);
            insert2(temp, head, 1, f->count);
            f = f->next;
        }
        vector<pair<string, int>> temp_path;
        vector<string> path;
        findFrequentItemsets(head, path, map_nodes[i].first, 0);
        cleanTree(head);
        cout<<endl;
    }
    return 0;
}
