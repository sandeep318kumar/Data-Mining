#include<bits/stdc++.h>
using namespace std;
int main()
{
	ifstream f;
	f.open("db.txt");
	string s;

	while(getline(f, s)){
		string t = s.substr(0, 2);
		cout<<t<<" ";
		for(int i=2;i<s.size();i++){
			if(isalpha(s[i])){
				cout<<s[i]<<" ";
			}
		}
		cout<<endl;
	}

    return 0;
}
