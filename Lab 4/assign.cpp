#include <bits/stdc++.h>
using namespace std;
map <string, set<string> > trans; // for storing transactions
vector <string> item_list; //storing all items
map< string, int> counting;

const int MIN_SUP = 2;

void gen( vector< vector<string> > &freq_items,  vector< vector<string> > &infreq_items, vector<string> it){

    vector<vector<string> >all_items;

    for(int i=0;i< it.size()-1;i++){
        for(int j=i+1;j<it.size();j++){
            y
        }
    }
}

int main(){
    ifstream fin;
	ofstream fout;
    fin.open("kv.txt");
    string s, t;
    set <string> present;

    while (getline(fin, s)){ // Reading the input from the file
        stringstream x(s);
        x >> t;
        //cout<<t<<"->";
        string str;
        while (x >> str){
            //cout<<str<<" ";
            trans[t].insert(str);
            if (present.count(str) == 0){
                item_list.push_back(str);
                present.insert(str);
            }
        }
        //cout<<endl;
    }

    fin.close();

    sort(item_list.begin(), item_list.end());

    int n = item_list.size();
    vector< vector<string> > freq_items;
     vector< vector<string> > infreq_items;

    for(auto &i: item_list){
        for(auto &j : trans){
            if(trans[j.first].count(i) != 0){
                counting[i]++;
            }
        }
    }
    for(auto i: counting){
        int x = i.first.size();
        if(i.second >= MIN_SUP){
            freq_items[x - 1].push_back(i.first);
        } else{
             infreq_items[x - 1].push_back(i.first);
        }
    }
    counting.clear();
    gen(freq_items, infreq_items, freq_items[0]);



    fout.open("frequent_item_set.txt");
    for (auto &i : Count){
        if (i.second >= MIN_SUP){
            for (auto &j : i.first) fout << j << " ";
            fout << endl;
        }
    }
    fout.close();
    return 0;
}
