#include<bits/stdc++.h>
using namespace std;
typedef pair<double, double> pp;
typedef vector<pp> vp;

void print_clusters(vector<vp > clusters, vector<pp > centroid)
{
    ofstream fout;
    fout.open("k_means_out.txt");
    for(int i=0;i<clusters.size();i++)
    {
        fout<<"CLUSTER NUMBER: "<<i+1<<"\n";
        fout<<"CENTROID: ( "<<centroid[i].first<<", "<<centroid[i].second<<" )\n";
        fout<<"[\n";
        for(int j=0;j<clusters[i].size();j++)
        {
            fout<<"\t("<<clusters[i][j].first<<", "<<clusters[i][j].second<<"),\n";
        }
        fout<<"]\n";
    }
    
}

double eucleadian_distance(pp p1, pp p2)
{
    return sqrt((p1.first - p2.first) * (p1.first - p2.first) + (p1.second - p2.second) * (p1.second - p2.second));
}
void printvp(vp a){
    cout<<"Vector of points\n";
    for(auto i:a){
        cout<<i.first<<", "<<i.second<<endl;
    }
}
int main()
{
    ifstream inp;
    inp.open("k_means_inp.txt");

    int num_of_clusters;
    vp num; // storing points
    int i = 0;
    //In the file, the first number is the number of clusters and the rest of them are the data tuples
    while(!inp.eof())
    {
        if(i == 0)
        {
            inp>>num_of_clusters;
            i++;
        }
        else
        {
            double x, y;
            pp p;
            inp>>x>>y;
            p.first = x;
            p.second = y;
            num.push_back(p);
        }
    }
    //printvp(num);
    //num.pop_back(); //eof condition for the last iteration makes the last tuple enter the array twice, so poped
    //printvp(num);
    vector<vector<pp>> clusters(num_of_clusters);
    vector<pp> centroid;
    for(int i=0;i<num_of_clusters;i++)
    {
        clusters[i].push_back(num[i]);
        centroid.push_back(num[i]);
    }
    // print_clusters(clusters, centroid);
    
    for(int i=num_of_clusters;i<num.size();i++)
    {
        int min = -1, min_dist = INT_MAX;
        for(int j=0;j<num_of_clusters;j++)
        {
            if(eucleadian_distance(num[i], centroid[j]) < min_dist)
            {
                min_dist = eucleadian_distance(num[i], centroid[j]);
                min = j;
            }
        }
        clusters[min].push_back(num[i]);
        centroid[min].first = (centroid[min].first + num[i].first)/2;
        centroid[min].second = (centroid[min].second + num[i].second)/2;
    }
    print_clusters(clusters, centroid);
    return 0;
}