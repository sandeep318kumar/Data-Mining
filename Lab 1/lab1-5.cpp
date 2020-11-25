#include<bits/stdc++.h>
using namespace std;
int main()
{
	srand(time(0));
	ofstream f;
	f.open("output.txt");

	string str;
	int transactions = rand()%20;

	for(int i=1;i<transactions;i++){
		int characs = rand()%25;
		f<<"T"<<i<<" ";
		for(int j=0;j<characs;j++){
			char ch = rand()%25 +'a';
			f<<ch<<" ";
		}
		f<<endl;
	}
	f.close();
	return 0;
}
