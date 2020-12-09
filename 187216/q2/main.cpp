#include <iostream>
#include <map>
#include <vector>
#include<math.h>
#define e 3
#define MinPts 3
using namespace std;
vector<pair<int, int>> G;
vector<vector<float>> F;
//core -> 0
//boundary -> 1
//outlier -> 2
vector<int> label;
vector<int> InCluster(vector<int>(G.size(),0));
vector<int> visit(vector<int>(G.size(),0));
int visit_count=0;
//0 -> not in cluster
//1 -> in cluster
vector<vector<pair<int,int>>> clusters;
void make_cluster(int i, vector<pair<int,int>> &clus)
{
    if(visit[i]==1)
        return;
    if(visit[i]==0)
    {
        visit[i]=1;
        visit_count++;
    }
    if(label[i]==2)
    {
        return;
    }
    if(InCluster[i]==1)
    {
        return ;
    }
    clus.push_back(make_pair(G[i].first,G[i].second));
    for(int j=0; j<F.size(); j++)
    {
        if(F[j][i] <= e && visit[j]==0)
        {
            make_cluster(j, clus);
        }
    }
}
float dist(int ax, int ay, int bx, int by )
{
    float sum = ((ax-bx)*(ax-bx) + (ay-by)*(ay-by));
    sum = sqrt(sum);
    return sum;
}
void fill_F()
{
    for(int i=0; i<G.size(); i++)
    {
        vector<float> v(G.size());
        F.push_back(v);
        for(int j=0; j<G.size(); j++)
        {
            F[i][j] = dist(G[i].first, G[i].second, G[j].first, G[j].second);
        }
    }
}
void label_pts()
{
    for(int i=0; i<F.size(); i++)
    {
        label.push_back(-1);
        int cnt=0;
        for(int j=0; j<F.size(); j++)
        {
            if(F[j][i] <=e)
                cnt++;
        }
        if(cnt >= MinPts )
            label[i]=0;
    }
    for(int i=0; i<F.size() ; i++)
    {
        int cnt=0;
        for(int j=0; j<F.size(); j++)
        {
            if(F[j][i]==0 || (label[j]==0 && F[j][i] <=e))
                cnt++;
        }
        if(label[i]==0)
            continue;
        if(cnt>1 )
            label[i]=1;
        else
            label[i]=2;
    }
}
void insert_values()
{
    G.push_back(make_pair(2,10));
    G.push_back(make_pair(2,5));
    G.push_back(make_pair(8,4));
    G.push_back(make_pair(5,8));
    G.push_back(make_pair(7,5));
    G.push_back(make_pair(6,4));
    G.push_back(make_pair(1,2));
    G.push_back(make_pair(4,9));
}
void print_1d(vector<int> A)
{
    for(int i=00; i<A.size(); i++ )
    {
        cout<<A[i]<<" ";
    }
}
int main()
{
    insert_values();
    fill_F();
    label_pts();
    //print_1d(label);
    for(int i=0; i<F.size(); i++)
    {
        InCluster.push_back(0);
        visit.push_back(0);
    }
    while(visit_count != F.size())
    {
        vector<pair<int,int>> v;
        make_cluster(rand()%F.size(), v);
        if(v.size()!=0)
        {
            clusters.push_back(v);
            v.clear();
        }
    }
    cout<<endl;
    for(int i=0; i<clusters.size(); i++)
    {
        cout<<"cluster "<<i<<endl;
        for(int j=0; j<clusters[i].size(); j++)
        {
            cout<<"("<<clusters[i][j].first<<" , "<<clusters[i][j].second<<")"<<endl;
        }
    }
}
