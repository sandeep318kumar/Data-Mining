#include<bits/stdc++.h>
using namespace std;
typedef struct node* LPTR;

struct node
{
    vector<LPTR> child;
    int cnt;
    string items;
};
LPTR T;
map<string, int> mp;

bool compare(string x, string y)
{
    return (mp[x] > mp[y]);
}

// function for returning new node
LPTR new_node(string k)
{
    LPTR temp = new (struct node);
    temp->items = k;
    temp->cnt = 1;
    return temp;
}

void insert(vector<string> trans, LPTR &p, int i)
{
    if(i == trans.size())
        return ;
    int flag = 0;
    int j = 0;
    while(j < p->child.size()){
        if(p->child[j]->items == trans[i])
        {
            flag = 1;
            p->child[j]->cnt++;
            insert(trans, p->child[j], i+1);
            break;
        }
        j++;
    }
    if(flag == 0)
    {
       LPTR temp = new_node(trans[i]);
        p->child.push_back(temp);
        insert(trans, p->child[p->child.size() - 1], i + 1);
    }
}
// function for printing tree
void print_tree(LPTR p, vector<pair<string, int> > path)
{
    path.push_back({p->items, p->cnt});

    for(int i=0; i<p->child.size(); i++)
    {
        print_tree(p->child[i], path);
    }

    if(p->child.size() == 0)
    {
        for(int i=0; i<path.size(); i++)
        {
            cout<<path[i].first<<", "<<path[i].second<<"  ";
        }
        cout<<endl;
    }
    path.pop_back();
}

int main()
{
    //taking input from input file
    vector<vector<string>> G;
    int record_cnt = 0;
    ifstream fin("input.txt");
    string temp;
    while(getline(fin, temp))
    {
        stringstream ss(temp);
        string temp1;
        vector<string> items;
        while(getline(ss, temp1, ' '))
        {
            if(temp1[0] != 'T')
            items.push_back(temp1);
        }
        record_cnt++;
        G.push_back(items);
    }
    fin.close();

    //Finding  C1
    for(int i = 0;i < G.size(); i++)
    {
        for(int j = 0;j < G[i].size(); j++)
        {
            mp[G[i][j]]++;
        }
    }

    T = new_node("{}");
    for(int i=0; i<G.size(); i++)
    {
        sort(G[i].begin(), G[i].end(), compare);
        insert(G[i], T, 0);
    }

    vector<pair<string, int>> path;
    print_tree(T, path);
}
