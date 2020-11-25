#include<bits/stdc++.h>
using namespace std;
int main()
{
	ifstream f;
	f.open("vs.txt");
	string s;
	map<string, vector<int> >trans;
	map<string, vector<int> >::iterator t;
	while(getline(f, s)){
		string t = s.substr(0, 2);
		for(int i=2;i<s.size();i++){
		    if(s[i] != ' '){
                vector<char>st;
                while(s[i] != ' ' && i<s.size()){
                    st.push_back(s[i]);
                    i++;
                }
                int sum = 0;
                reverse(st.begin(), st.end());
                for(int i=0;i<st.size();i++){
                    int j = int(st[i] - '0');
                    sum += j*pow(10, i);
                }
                trans[t].push_back(sum);
		    }
		}
	}
    f.close();

    ofstream fout;
	fout.open("replace_with_boundary_output.txt");
	for(t = trans.begin();t != trans.end();t++){
        fout<<t->first<<" ";
        sort(t->second.begin(), t->second.end());
        int n = t->second.size();
        const int DIVIDE = 3;
        int i = 0;
        while(i<n){
            int l = t->second[i];
            int r = t->second[i + DIVIDE - 1];
            for(int j=i;j<i + DIVIDE;j++){
                if( (t->second[j] - l) <= (r - t->second[j]) )
                    fout<<l<<" ";
                else
                    fout<<r<<" ";
            }
            i += DIVIDE;
        }
        fout<<endl;
	}

	fout.close();
    return 0;
}
