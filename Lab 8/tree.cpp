#include<bits/stdc++.h>
using namespace std;
typedef vector<vector<string>>vvs;
typedef vector<string>vs;
typedef vector<vector<string>>::iterator vvs_itr;
typedef vector<string>::iterator vs_itr;
typedef struct node* lptr;

struct node{
    string splitting_criteria;
    vector<lptr>child;
    vector<string> child_brances;
};
lptr new_node(string s){
    lptr t = new node;
    t->splitting_criteria = s;
    return t;
}
void enterDataInFile()
{
    ofstream fout("input.txt");
    fout<<"class"<<" "<<"age"<<" "<<"income"<<" "<<"student"<<" "<<"credit_rating"<<endl;

    fout<<"no"<<" "<<"youth"<<" "<<"high"<<" "<<"no"<<" "<<"fair"<<endl;
    fout<<"no"<<" "<<"youth"<<" "<<"high"<<" "<<"no"<<" "<<"excellent"<<endl;
    fout<<"yes"<<" "<<"middle"<<" "<<"high"<<" "<<"no"<<" "<<"fair"<<endl;
    fout<<"yes"<<" "<<"senior"<<" "<<"medium"<<" "<<"no"<<" "<<"fair"<<endl;
    fout<<"yes"<<" "<<"senior"<<" "<<"low"<<" "<<"yes"<<" "<<"fair"<<endl;
    fout<<"no"<<" "<<"senior"<<" "<<"low"<<" "<<"yes"<<" "<<"excellent"<<endl;
    fout<<"yes"<<" "<<"middle"<<" "<<"low"<<" "<<"yes"<<" "<<"excellent"<<endl;
    fout<<"no"<<" "<<"youth"<<" "<<"medium"<<" "<<"no"<<" "<<"fair"<<endl;

    fout<<"yes"<<" "<<"youth"<<" "<<"low"<<" "<<"yes"<<" "<<"fair"<<endl;
    fout<<"yes"<<" "<<"senior"<<" "<<"medium"<<" "<<"yes"<<" "<<"fair"<<endl;
    fout<<"yes"<<" "<<"youth"<<" "<<"medium"<<" "<<"yes"<<" "<<"excellent"<<endl;
    fout<<"yes"<<" "<<"middle"<<" "<<"medium"<<" "<<"no"<<" "<<"excellent"<<endl;
    fout<<"yes"<<" "<<"middle"<<" "<<"high"<<" "<<"yes"<<" "<<"fair"<<endl;
    fout<<"no"<<" "<<"senior"<<" "<<"medium"<<" "<<"no"<<" "<<"excellent"<<endl;

    fout.close();
}
void readFromFile(vvs &G)
{
    ifstream fin("input.txt");
    string temp;
    while(getline(fin, temp))
    {
        stringstream ss(temp);
        string t1;
        vs str;
        while(getline(ss, t1, ' '))
        {
            str.push_back(t1);
        }
        G.push_back(str);
    }
    fin.close();
}
void print2dvector(vvs G)
{
    for(auto i:G){
        for(auto j:i)
            cout<<j<<" ";
        cout<<endl;
    }
}
void printvector(vs s)
{
    for(auto i:s)
        cout<<i<<" ";
    cout<<endl;
}

bool sameClass(vvs G)
{
    int yes = 0, no = 0;
    for(int i=1;i<G.size();i++)
    {
        if(G[i][0] == "yes")    yes++;
        else    no++;
    }
    if(no == 0 || yes == 0){
        return true;
    }
    return false;
}
double findEntropy(vvs G)
{
    double yes = 0, no = 0, total = 0, ans = 0.0;
    for(int i=1;i<G.size();i++)
    {
        if(G[i][0] == "yes")   yes++;
        else    no++;
    }
    total = yes + no;
    ans = - (no/total)*log2(no/total) - (yes/total)*log2(yes/total);
    return ans;
}
double findGain(vvs G, double entropy, string s)
{
    int k = 0;
    for(int i=1;i<G[0].size();i++)
    {
        if(G[0][i] == s){
            k = i;
            break;
        }
    }

    map<string, int>mp;
    for(int i=1;i<G.size();i++)
    {
        mp[G[i][k]]++;
    }
    double totalEntropy = 0;
    for(auto i:mp)
    {
        double yes = 0, no = 0, total;
        double ent = 0.0;
        for(int j = 1;j<G.size();j++)
        {
            if(G[j][k] == i.first)
            {
                if(G[j][0] == "yes")
                    yes++;
                else
                    no++;
            }
        }
        total = yes + no;
        if(yes == 0 || no == 0)
            ent = 0;
        else
            ent = - (no/total)*log2(no/total) - (yes/total)*log2(yes/total);

        int si = G.size() - 1;
        double weightAverage = (((double)i.second)/((double)si));
        totalEntropy += ent * weightAverage;
    }
    double gain = entropy - totalEntropy;
    return gain;
}
int findBestAttribute(vvs G, vs attribute_list)
{
   // cout<<"****in best attribute****\n"<<endl;
   // print2dvector(G);
    double entropy = findEntropy(G);
    double maxGain = 0;
    int index = -1;
    for(int i=0;i<attribute_list.size();i++)
    {
        double gain = findGain(G, entropy, attribute_list[i]);
        if(gain > maxGain){
            //cout<<"hi";
            maxGain = gain;
            index = i;
        }
    }
    return index;
}
vs findDistinctValues(vvs G, int index)
{
   // cout<<"****in distinct****\n"<<endl;
   // print2dvector(G);
    map<string, int>mp;
    for(int i=1;i<G.size();i++)
    {
        mp[G[i][index]]++;
    }
    vs distinct;
    for(auto i:mp){
        distinct.push_back(i.first);
    }
    return distinct;
}
vvs filter(vvs G, int index, string attribute)
{
   // cout<<"****in filter****\n"<<endl;
   // print2dvector(G);

    vvs temp;
    temp.push_back(G[0]);
    for(int i=1; i<G.size(); i++)
    {
        if(G[i][index] == attribute)
        {
            temp.push_back(G[i]);
        }
    }
    vector<string>::iterator itr;
    for(int i=0; i<temp.size(); i++)
    {
        itr = temp[i].begin();
        temp[i].erase(itr+index);
    }
    return temp;
}
void splitting(lptr &T, vvs &G, vs &attribute_list)
{
    if(sameClass(G)){
        T = new_node(G[1][0]);
       // cout<<"hi\n";
        return ;
    }
    if(attribute_list.size() == 0)
    {
      return ;
    }

    //cout<<"****in splitting****\n"<<endl;
    //print2dvector(G);
    int index = findBestAttribute(G, attribute_list);
    T = new_node(attribute_list[index]);
    //cout<<attribute_list[index]<<endl;
    vector<string>::iterator it;
    it = attribute_list.begin();
    attribute_list.erase(it + index);

    vs distinctValues = findDistinctValues(G, index+1);
    //printvector(distinctValues);
  //  cout<<"\n\n";
    for(int i=0;i<distinctValues.size();i++)
    {
        T->child_brances.push_back(distinctValues[i]);
        T->child.push_back(NULL);
        vvs filteredTable = filter(G, index+1, distinctValues[i]);
       // print2dvector(G);
      //  cout<<"next\n";
        splitting(T->child[i], filteredTable, attribute_list);
    }
}

void printTree(lptr T)
{
    if(T->splitting_criteria != "yes" && T->splitting_criteria != "no")
    {
        cout<<T->splitting_criteria<<" ?"<<endl;
        for(int i=0;i<T->child_brances.size();i++){
            cout<<i+1<<" "<<T->child_brances[i]<<endl;
        }
        int n;
        cin>>n;
        printTree(T->child[n-1]);
    }
    else{
        cout<<"The answer is "<<T->splitting_criteria<<endl;
    }
}

int main()
{
    enterDataInFile();
    vvs G;
    readFromFile(G);
    //print2dvector(G);
    lptr T = NULL;
    vs attribute_list;
    for(int i=1;i<G[0].size();i++)
        attribute_list.push_back(G[0][i]);
    //printvector(attribute_list);
    splitting(T, G, attribute_list);

    printTree(T);
    return 0;
}
