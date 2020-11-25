#include<bits/stdc++.h>
using namespace std;
typedef vector<vector<string>>vvs;
typedef vector<string>vs;
typedef vector<vector<string>>::iterator vvs_itr;
typedef vector<string>::iterator vs_itr;

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
    //cout<<endl;
}
string compute(vvs G, vs test)
{
    double class_yes = 0, class_no = 0;
    for(int i=1;i<G.size();i++){
        if(G[i][0] == "yes")
        class_yes++;
        else
        {
            class_no++;
        }
    }
    double class_yes_prob = (double)class_yes/(class_yes + class_no);
    double class_no_prob = (double)class_no/(class_yes + class_no);
    double total_yes_prob = 1, total_no_prob = 1;
    for(int i=0;i<test.size();i++)
    {
        double attr_yes = 0, attr_no = 0;
        for(int j=1;j<G.size();j++)
        {
            if(G[j][i+1] == test[i])
            {
                if(G[j][0] == "yes")
                    attr_yes++;
                else
                    attr_no++;
            }
        }
        double attr_yes_prob = (double) attr_yes / (attr_no + attr_yes);
        double attr_no_prob = (double) attr_no / (attr_no + attr_yes);
        total_no_prob *= attr_no_prob;
        total_yes_prob *= attr_yes_prob;
    }
    if(class_no_prob * total_no_prob > class_yes_prob * total_yes_prob)
        return "No";
    else
        return "Yes";
}

int main()
{
    enterDataInFile();
    vvs G;
    readFromFile(G);
    // print2dvector(G);
    vs testData{"youth", "medium", "yes", "fair"};
    cout<<"The Classification for test data \" ";
    printvector(testData);
    cout<<"\" is "<<compute(G, testData);
    return 0;
}
