#include<bits/stdc++.h>
using namespace std;
int main()
{
	ifstream f;
	f.open("db.txt");
	string s;

    const string STR = "a";
	ofstream fout;
	fout.open("replace_with_constant_output.txt");
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
