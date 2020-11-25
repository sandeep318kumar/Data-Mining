#include<bits/stdc++.h>
using namespace std;
typedef vector<vector<string>> vvs;
typedef vector<string> vs;
typedef struct node* lptr;
map<string, int>m;

struct node{
    int cnt;
    string item;
    vector<lptr>children;
};

lptr newNode(string s)
{
    lptr t = new node;
    t->cnt = 1;
    t->item = s;
    return t;
}
void print2dvector(vvs G)
{
    for(auto i:G){
        for(auto j : i)
        {
            cout<<j<<" ";
        }
        cout<<endl;
    }
}
void printvector(vs v){
    for(auto j : v)
    {
        cout<<j<<" ";
    }
    cout<<endl;
}
bool compare(string a, string b)
{
    return m[a] > m[b];
}
void create(lptr &T, vs tr, int i)
{
    if(i == tr.size())
        return ;

    int ff = 0;
    for(int j = 0;j<T->children.size();j++)
    {
        if(T->children[j]->item == tr[i]){
            ff = 1;
            T->children[j]->cnt++;
            create(T->children[j], tr, i+1);
            break;
        }
    }
    if(ff == 0)
    {
        lptr temp = newNode(tr[i]);
        T->children.push_back(temp);
        create(T->children[T->children.size()-1], tr, i+1);
    }
}
void printTree(lptr T, vector<pair<string, int>> paths)
{
    paths.push_back({T->item, T->cnt});

    for(int i=0;i<T->children.size();i++)
        printTree(T->children[i], paths);
    if(T->children.size() == 0){
        for(auto j:paths)
            cout<<j.first<<", "<<j.second<<" ";
        cout<<endl;
    }
    paths.pop_back();
}
int main()
{
    vvs G;
    ifstream fin("input.txt");
    string temp;
    while(getline(fin, temp))
    {
        stringstream ss(temp);
        string s1;
        vs tr;
        while(getline(ss, s1, ' ')){
            if(s1[0] != 'T')
                tr.push_back(s1);
        }
        G.push_back(tr);
    }
    fin.close();

    for(auto i:G){
        for(auto j : i)
        {
            m[j]++;
        }
    }


    lptr T = newNode("{}");
    for(int i=0;i<G.size();i++)
    {
        sort(G[i].begin(), G[i].end(), compare);
        create(T, G[i], 0);
    }
    print2dvector(G);
    vector<pair<string, int>> paths;
    printTree(T, paths);
    return 0;
}
