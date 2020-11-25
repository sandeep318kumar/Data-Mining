#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <string>
#include <fstream>
#include <tuple>
// #include <bits/stdc++.h>
using namespace std;

//printing matrix
void print_matrix(vector<vector<string> > vec)
{
    for(int i=0;i<vec.size();i++)
    {
        for(int j=0;j<vec[i].size();j++)
            cout<<vec[i][j]<<" ";
        cout<<"\n";
    }
}
// printing set
void print_set(set<string> st)
{
    set<string>::iterator it;
    for(it=st.begin();it!=st.end();it++)
        cout<<*it<<" ";
    cout<<"\n";
}
// counting the frequency of an item set
int check(vector<vector<string>> vec, vector<string> pos, int n ){
    int ans = 0;
    set<string> ss(pos.begin(), pos.end());
    for(int i=0;i<n;++i){
        int size = vec[i].size();
        vector<string> a = vec[i];
        int c = 0;
        for(string val : a){
            if(ss.count(val)){
                ++c;
            }
        }
        if(c == pos.size())
            ans++;
    }
    return ans;
}

//joining operation
vector<vector<string> > join(vector<vector<string> > temp, int size)
{
    if(temp.size() <= 1)
        return {{}};

    set<vector<string> > st;
    int n = temp.size();
    
    for(int i=0;i<n;i++)
    {
        set<string> buffer;
        for(int j=i+1;j<n;j++)
        {
            for(string s:temp[i])
            {
                buffer.insert(s);
            }
            for(string s:temp[j])
            {
                buffer.insert(s);
            }
            
            if(buffer.size() > size)
                continue;
            else if(buffer.size() == size)
            {
                vector<string> one(buffer.begin(), buffer.end());
                sort(one.begin(), one.end());
                st.insert(one);
            }
            buffer.clear();
        }
    }

    vector<vector<string> > ans(st.begin(), st.end());
    return ans;
}

//building associations rules
void association_rules(vector<tuple<vector<string>, vector<string>, double, double> >& assigning_rules, 
    map<vector<string>, int> CountOfSets, vector<string> itemset, vector<string> a, vector<string> b, int idx)
{
    if(idx == itemset.size())
    {
        if(a.size() == 0 || b.size() == 0)
            return;
        double total_supp = CountOfSets[itemset];
        double a_supp = CountOfSets[a];

        if(a_supp == 0)
            return;
        double confidence = total_supp/a_supp*100;
        assigning_rules.push_back(make_tuple(a, b, total_supp, confidence));
        return;
    }

    a.push_back(itemset[idx]);
    association_rules(assigning_rules, CountOfSets, itemset, a, b, idx+1);
    a.pop_back();
    b.push_back(itemset[idx]);
    association_rules(assigning_rules, CountOfSets, itemset, a, b, idx+1);
}

int main()
{
    ifstream fin; //for opening files for reading
    ofstream fout; // for writing in fil
    fin.open("input.txt");
    fout.open("output.txt");
    vector<vector<string> > vec; // 2-d matrix for storing transactions
    map<vector<string>, int> CountOfSets; // map for counting the frequency of sets
    vector<tuple<vector<string>, vector<string>, double, double> > assigning_rules; // for association rules
    //This loop enters all the transactions and their items in a matrix from the file
    int i = -1;
    string word;
    while(fin >> word)
    {
        if(word.size() > 2)
        {
            i++;
            vec.push_back({});
            continue;
        }
        else
        {
            vec[i].push_back(word);
        }
    }
    int n = vec.size();
    fin.close();

    int min_cnt, mn;
    cout<<"Enter min_support: ";
    cin>>mn;

    min_cnt = (mn * n)/100;

    vector<vector<string> > ans;//This will store the final item sets
    vector<vector<string> > temp;//A temporary matrix to store item sets of a specific size at a time
    int size = 1;
    vector<string> all_pos;
    while(size == 1 || !temp.empty())
    {
        int k;
        if(size == 1)
        {
            // for 1st case
            //Calculates the frequency of each itemset
            map<string, int> freq;
            for(int i=0;i<n;i++)
            {
                for(string val : vec[i])
                {
                    freq[val]++;
                }
            }
            k = freq.size();
            
            //Only those items pushed that have freq more than min_cnt

            for(auto it : freq)
            {
                if(it.second >= min_cnt)
                {
                    all_pos.push_back(it.first);
                    temp.push_back({it.first});
                    ans.push_back({it.first});
                    CountOfSets[{it.first}] = it.second;
                }
            }
        }
        else
        {
            vector<vector<string> > temp2 = join(temp, size);
            temp.clear();
            for(int i=0;i<temp2.size();i++)
            {
                if(check(vec, temp2[i], n) >= min_cnt)
                {
                   
                    ans.push_back(temp2[i]);
                    temp.push_back(temp2[i]);
                    sort(temp2[i].begin(), temp2[i].end());
                    if(!temp2.empty())
                        CountOfSets[temp2[i]] = check(vec, temp2[i], n);
                }
            }
        }
        size++;
        if(size > k)
        {
            break;
        }
    }
    fout<<"The following are the most frequent item sets at "<<mn<<"% support:\n";
    for(int i=0;i<ans.size();i++)
    {
        for(int j=0;j<ans[i].size();j++)
            fout<<ans[i][j]<<" ";
        fout<<"\n";
    }
    auto k = CountOfSets.find({});
    CountOfSets.erase(k);

    for(int i=0;i<ans.size();i++)
    {
        if(ans[i].size() != 1)
            association_rules(assigning_rules, CountOfSets, ans[i], {}, {}, 0);
    }

    fout<<"Here is the list of association rules for the most frequent item sets:\n";
    for(auto tp:assigning_rules)
    {
        fout<<"[ ";
        vector<string> first = get<0>(tp);
        vector<string> second = get<1>(tp);
        for(int i=0;i<first.size();i++)
            fout<<first[i]<<", ";
        fout<<"] --> [ ";
        for(int i=0;i<second.size();i++)
            fout<<second[i]<<", ";
        fout<<"] : Support = "<<get<2>(tp)<<", Confidence = "<<get<3>(tp)<<"\n";
    }
    fout.close();
    return 0;
}
