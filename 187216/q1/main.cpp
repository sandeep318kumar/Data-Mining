#include <iostream>
#include <map>
#include <vector>
#define k 3
using namespace std;
typedef vector<int> vi;
typedef vector<vector<int>> vvi;
vector<pair<int,int>> G;
vector<pair<float,float>> centroids;
vector<vector<pair<float,float>>>buckets;
vector<vector<pair<float,float>>>global_buckets;
float global_sum=1000000;
float dist(float ax,float ay, float bx, float by  )
{
    float p=(ax-bx)*(ax-bx)+(ay-by)*(ay-by);
    return p;
}
void print_buckets()
{
    for(int i=0; i<buckets.size(); i++)
    {
        cout<<"bucket "<<i+1<<endl;
        for(int j=0; j<buckets[i].size(); j++)
        {
            cout<<"("<<buckets[i][j].first<<" , "<<buckets[i][j].second<<")"<<endl;
        }
    }
}
void print_global_buckets()
{
    for(int i=0; i<global_buckets.size(); i++)
    {
        cout<<"bucket "<<i+1<<endl;
        for(int j=0; j<global_buckets[i].size(); j++)
        {
            cout<<"("<<global_buckets[i][j].first<<" , "<<global_buckets[i][j].second<<")"<<endl;
        }
    }
}
void recompute_centroid(int j)
{
    int x=0, y=0;
    for(int i=0; i<buckets[j].size(); i++)
    {
        x+=buckets[j][i].first;
        y+=buckets[j][i].second;
    }
    float x1=x/buckets[j].size(); 
    float y1=y/buckets[j].size();
    centroids[j].first=x1;
    centroids[j].second=y1;
}
void variance()
{
    float sum=0;
    for(int i=0; i<centroids.size(); i++)
    {
        float sum1=0;
        for(int j=0; j<buckets[i].size(); j++)
        {
            sum1+=dist(centroids[i].first, centroids[i].second, buckets[i][j].first, buckets[i][j].second);
        }
        sum+=sum1/buckets[i].size();
    }
    if(sum < global_sum)
    {
        global_sum=sum;
        //global_buckets=buckets;
        global_buckets.clear();
        for(int i=0; i<buckets.size(); i++)
        {
            vector<pair<float,float>> v;
            global_buckets.push_back(v);
            for(int j=0; j<buckets[i].size(); j++)
            {
                global_buckets[i].push_back(make_pair(buckets[i][j].first,buckets[i][j].second));
            }
        }
    }
}
void clear_bucket()
{
    for(int i=0; i<k; i++)
    {
        buckets[i].clear();
    }
}
void k_means()
{
    for(int c=0; c<10; c++)
    {
        centroids.clear();
        for(int i=0; i<k;i++)
        {
            centroids.push_back(G[rand()%G.size()]);
        }

        for(int i=0; i<G.size(); i++)
        {
            float min_d=100;int l=-1;
            for(int j=0; j<k; j++)
            {
                float dis=dist(centroids[j].first, centroids[j].second, G[i].first, G[i].second);
                if(min_d > dis)
                {
                    min_d=dis;
                    l=j;
                }
                
            }
            buckets[l].push_back(make_pair(G[i].first,G[i].second));
            recompute_centroid(l);
        }
        //print_buckets();
        variance();
        clear_bucket();
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
int main()
{
    insert_values();
    
    for(int i=0; i<k; i++)
    {
        vector<pair<float,float>> v;
        buckets.push_back(v);
    }
    k_means();
    cout<<"The final answer is"<<endl;
    print_global_buckets();
    
}
