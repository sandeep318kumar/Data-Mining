#include<bits/stdc++.h>
using namespace std;
int main()
{
	ifstream f;
	f.open("db.txt");
	string s;

	ofstream fout;
	fout.open("ignoring_tuple_output.txt");
	while(getline(f, s)){
		string t = s.substr(0, 2);
		fout<<t<<" ";
		for(int i=2;i<s.size();i++){
			if(isalpha(s[i]) ){
				fout<<s[i]<<" ";
			}
		}
		fout<<endl;
	}
	f.close();
	fout.close();
    return 0;
}
