#include<bits/stdc++.h>
using namespace std;
int main()
{
	ifstream f;
	f.open("db.txt");
	string s;
	// for each item
	map<char, vector<string> >m;
	// for each transaction
	map<string, vector<char> >trans;
	while(getline(f, s)){
		string t = s.substr(0, 2);
		for(int i=2;i<s.size();i++){
			if(isalpha(s[i])){
				m[s[i]].push_back(t);
				trans[t].push_back(s[i]);
			}
		}
	}
	// iterator for one item
	map<char, vector<string> >::iterator item;
	for(item = m.begin();item!=m.end();item++){
		cout<<item->first<<" -> ";
		for(int j=0;j<i->second.size();j++){
			cout<<item->second[j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
	// iterator for transactions
	map<string, vector<char> >::iterator t;
	for(t = trans.begin();t!=trans.end();t++){
		cout<<t->first<<" -> ";
		for(int j=0;j < t->second.size();j++){
			cout<<t->second[j]<<" ";
		}
		cout<<endl;
	}
	
	int total_items = m.size();
	int total_trans = trans.size();
	
	// for storing frequent item sets
	map<int, vector<char> >mp;
	
	const int SUP = 5;
	
	// for storing counts of each item set
	map<vector<char>, int>cc;
	
	
	bool flag = true;
	for(int i=1;i<=n;i++){
		
		if(i == 1){
			for(item = m.begin();item != m.end();item++){
				if(item->second.size() >= SUP){
					mp[i].push_back(item->first);
				}
			}
		}
		else{
			for(int j=0;j<mp[i-1]->second.size();j++){
				for(int k=j+1;j<mp[i-1]->second.size();k++){
					vector<char>v;
					
				}
			}
		}
	}	
	
    return 0;
}
