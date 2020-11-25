#include<bits/stdc++.h> 
using namespace std;

#define min_support 20
#define min_conf 0.5
int min_size;

typedef vector<vector<string>> vvs;
typedef vector<string> vs;

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

void subsetsUtil(vs &A, vvs & res, vs & subset, int index)
{
    res.push_back(subset);
    for (int i = index; i < A.size(); i++) {
        subset.push_back(A[i]);
        subsetsUtil(A, res, subset, i + 1);
        subset.pop_back();
    }
    return;
}

int check(vvs G, vs temp)
{
    int cnt = 0;
    for(int i=0; i<G.size(); i++)
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

vs find_missing(vs &A, vs &B)
{
    vs temp;
    for(int i=0; i<A.size(); i++)
    {
        if(find(B.begin(), B.end(), A[i]) == B.end())
        {
            temp.push_back(A[i]);
        }
    }
    return temp;
}

// k = 1


vvs join(int k, vvs M, vvs G,vector<int> &next_int )
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
                    flag = 1;
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
                next.push_back(temp);
                next_int.push_back(check(G, temp));
            }
        }
    }
    return next;
}

vvs hash_step(vvs M, vector<int> next_int)
{
    vector<int> bucket_number(M.size(), 0);
    vector<int> bucket(7, 0);
    for(int i=0; i<M.size(); i++)
    {
        int num = 0;
        for(int j=0; j<M[i].size(); j++)
        {
            string temp = M[i][j].substr(1, M[i][j].size());
            int t = stoi(temp);
            num += t * pow(10.0,j);
        }
        bucket_number[i] = num % 7;
        bucket[num % 7] += next_int[i];
    }
    vvs next;
    for(int i=0; i<M.size(); i++)
    {
        if(bucket[bucket_number[i]] >= min_size)
        {
            next.push_back(M[i]);
        }
    }
    return next;
}

int main()
{
    //Taking input from input_file to G
    ifstream fin("AprioriInput.txt");
    vector<vector<string> > G;
    string temp;
    int record_cnt = 0;
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
    
    //The min_size aka min_support
    // min_size = floor((record_cnt*min_support)/100);
    min_size = 2;
    //Finding frequency of the each Itemset
    map<string, int> L1;
    for(int i=0; i<G.size(); i++)
    {
        for(int j=0; j<G[i].size(); j++)
        {
            L1[G[i][j]]++;
        }
    }
    //Putting this Itemset into output file
    ofstream fout("AprioriOutput.txt");
    ofstream fout1("prev.txt");
    map<string,int> :: iterator itr;
    fout<<"L1"<<" "<<endl;
    for(itr = L1.begin(); itr != L1.end(); itr++)
    {
        fout<<itr->first<<" "<<itr->second<<" "<<endl;
        fout1<<itr->first<<" "<<itr->second<<" "<<endl;
    }
    fout1.close();

    //Now for the other files
    int k = 1;
    while(1)
    {
        //reading previous Item sets and storing it in M
        vvs M = read_prev_file("prev.txt");
       // Generating The new Itemset
        vector<int> next_int;
        M = join(k, M, G, next_int);
        vvs next = hash_step(M, next_int);
        if(next.size() == 0)
            break;
    
        fout<<"L"<<k + 1<<" "<<endl;
        //Output the new Itemset into the file
        k++;
        ofstream fout2;
        int flag = 0;
        for(int e=0; e<next.size(); e++)
        {
            for(int s=0; s<next[e].size(); s++)
            {
                if(flag == 0)
                {
                    flag = 1;
                    fout2.open("prev.txt");
                }
                fout<<next[e][s]<<" ";
                fout2<<next[e][s]<<" ";
               
            }
            fout<<next_int[e]<<" "<<endl;
            fout2<<endl;  
        }   
    }
    //Reading values from prev.txt and storing them in
    //vector<vector<string>> last_itr
    //teking each vector from last_itr
    //generating subsets of that vector
    
    vvs last_itr = read_prev_file("prev.txt");
    for(int i=0; i<last_itr.size(); i++)
    {
        vvs res;
        vs subset;
        subsetsUtil(last_itr[i], res, subset, 0);
        int y = check(G,last_itr[i]);
        if(y < min_size)
            continue;
        for(int j=0; j<res.size(); j++)
        {
            //we have to find S-> (L-S)  
            if(!(res[j].size() == 0 || res[j].size() == last_itr[i].size()))
            {
                vs right = find_missing(last_itr[i], res[j]);
                int x = check(G, res[j]);
                float ans = (float)y/(float)x;
                if(ans >= min_conf)
                {
                    for(int k=0; k<res[j].size(); k++)
                    {
                        cout<<res[j][k]<<" ";
                    }
                    cout<<" "<<"=> ";
                    for(int k=0; k<right.size(); k++)
                    {
                        cout<<right[k]<<" ";
                    }
                    cout<<" "<<"confidence = "<<ans<<endl;
                }
            }
        }
    }    
    return 0; 
}
