#include<bits/stdc++.h>
#include<string>
using namespace std;
int main()
{
	ofstream f;
    f.open("db.txt");
    string s;
    cout<<"enter number of transactions \n";
    int a;
    cin>>a;
    
    vector<vector<string> >v(a);
    
    for(int i=0;i<a;i++){
    	getline(cin, s);
    	while(s != "-1"){
    		v[i].push_back(s);
    		getline(cin, s);
		}
    		
	}
	
	for(int i=0;i<a;i++){
		string k;
		k = (i+1) + '0';
		string k1 = "T" + k;
		f<<"T";
		f<<k<<" ";
		for(int j=0;j<v[i].size();j++){
			f<<v[i][j]<<" ";
		}
		f<<endl;
	}    
    f.close();

    return 0;
}
