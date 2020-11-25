#include<bits/stdc++.h>
using namespace std;
int main()
{
	ifstream f;
	f.open("output.txt");
	string s;
	map<char, vector<string> >m;
	while(getline(f, s)){
		string t = s.substr(0, 2);
		for(int i=2;i<s.size();i++){
			if(isalpha(s[i])){
				m[s[i]].push_back(t);
			}
		}
	}

	map<char, vector<string> >::iterator i;
	for(i = m.begin();i!=m.end();i++){
		cout<<i->first<<" -> ";
		for(int j=0;j<i->second.size();j++){
			cout<<i->second[j]<<" ";
		}
		cout<<endl;
	}
    return 0;
}
