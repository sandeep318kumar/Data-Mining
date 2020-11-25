#include <bits/stdc++.h>
using namespace std;
map <string, set<string> > trans; // for storing transactions
vector <string> item_list; //storing all items
set < set<string> > all_subsets; //storing all subsets possible
map < set<string>, int> Count; // map for counting
const int MIN_SUP = 2;

void generate_all_subsets(int i, int n, set <string> &temp){
    if (i == n) {
        if (temp.size() > 0)
            all_subsets.insert(temp); return;
    }
    generate_all_subsets(i+1, n, temp);
    temp.insert(item_list[i]);
    generate_all_subsets(i+1, n, temp);
    temp.erase(item_list[i]);
}

int main(){
    ifstream fin;
	ofstream fout;
    fin.open("db.txt");
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
    set <string> temp;

    sort(item_list.begin(), item_list.end());
    for(auto i: item_list){
       // cout<<i<<" ";
    }
   // cout<<"\nhare krishna\n";
    generate_all_subsets(0, item_list.size(), temp); // generates all possible subsets of all possible lengths

   // for(auto i: all_subsets){
     //   for(auto j: i)
       //     cout<<j<<" ";
       // cout<<endl;
   // }
    int flg = 0;

    for (auto &i : all_subsets){    // counting the frequency of all sets in all transactions
        for (auto &j : trans){
            flg = 0;
            for (auto &items : i){
                if (trans[j.first].count(items) == 0){
                    flg = 1;
                    break;
                }
            }
            if (flg == 0) Count[i]++;
        }
    }

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
