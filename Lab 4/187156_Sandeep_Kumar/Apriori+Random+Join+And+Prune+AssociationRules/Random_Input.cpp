#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <string>
#include <fstream>
using namespace std;

int main()
{
    int total = rand()%20+7;

    fstream transactionsFile;
    transactionsFile.open("Random_Input.txt", ios::out);

    for(int i = 1;i<=total;++i)
    {
        int transactionId = rand()%1000 + 100;
        transactionsFile <<"T" <<transactionId << " ";
        for(int j = 0;j<rand()%6 + 1;++j)
        {
            int item = rand()%(total/2) + 1;
            transactionsFile <<"I"<<item<<" ";
        }
        transactionsFile << "\n";
    }
    transactionsFile.close();
    return 0;
}
