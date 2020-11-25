#include <iostream>
#include <fstream>
#include<bits/stdc++.h>
#include<map>
#include<vector>
using namespace std;
void printSubSeqRec(string str, int n ,map<string,int> &m, int index = -1, string curr = "")
{
    // base case
    if (index == n)
        return;

    if (!curr.empty()) {
        cout << curr << "\n";
        m[curr]++;
    }
    for (int i = index + 1; i < n; i++) {

        curr += str[i];
        printSubSeqRec(str, n,m, i, curr);

        // backtracking
        curr = curr.erase(curr.size() - 1);
    }
    return;
}
void printSubSeq(string str,map<string,int> &m)
{
    printSubSeqRec(str, str.size(),m);
}
int main()
{
    ofstream fout;
    string line;
  	fout.open("output2.txt");
    ifstream fin;
    fin.open("A1.txt");
    map<string,int> m;
  	int f=0;
 	while (fin) {
        getline(fin, line);
        string s;
		for(int i=2;i<line.size();i++){
			if(isalpha(line[i]))
			s=s+line[i];
		}
		printSubSeq(s,m);
    }
    fin.close();
    map<string,int>::iterator it;
    for(int i=1;i<=4;i++){
		int max=0;
		string r;
	    for(it=m.begin();it!=m.end();it++){
	    	if(it->second>max&&it->first.size()==i)
	    	{
	    		r=it->first;
	    		max=it->second;
			}
		}
		fout<<r<<" "<<max<<endl;
	}
	fout.close();
   	return 0;
}

