#include<bits/stdc++.h>
using namespace std;
int main()
{
	ifstream f;
	f.open("db.txt");
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
    f.close();

	map<char, vector<string> >::iterator i;
	int mi = -1;
	string STR;
	for(i = m.begin();i!=m.end();i++){
	//	cout<<i->first<<" ";
	//	cout<<i->second.size()<<endl;

		if(int(i->second.size()) > mi){
            mi = i->second.size();
            STR = i->first;
		}
	}
	//cout<<STR<<" "<<mi;

    f.open("db.txt");
	ofstream fout;
	fout.open("replace_with_mode_output.txt");
	while(getline(f, s)){
		string t = s.substr(0, 2);
		fout<<t;
		for(int i=2;i<s.size();i++){
			if(s[i] == '*'){
				fout<<STR;
			}
			else
                fout<<s[i];
		}
		fout<<endl;
	}
	f.close();
	fout.close();
    return 0;
}
