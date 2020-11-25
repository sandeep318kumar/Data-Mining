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
                //cout<<sum<<" ";
		    }
		}
		//cout<<endl;
	}
    f.close();

    ofstream fout;
	fout.open("replace_with_mean_output.txt");

	vector<int>mean(trans.size());
	for(t = trans.begin();t != trans.end();t++){
        fout<<t->first<<" ";
        int n = t->second.size();
        const int DIVIDE = 3;
        for(int i=0;i<n;i++){
            int m = 0;
            for(int j=i;j<i+DIVIDE;j++)
                m += t->second[i];
            m = m/DIVIDE;
            for(int j=i;j<i+DIVIDE;j++){
                fout<<m<<" ";
            }
            i += DIVIDE;
        }
		fout<<endl;
	}

	fout.close();
    return 0;
}
