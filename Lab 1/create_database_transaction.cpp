#include <iostream>

using namespace std;

int main(){
    int no_of_files;
    char curr_file_name[50];
    char c;

    cout<<"No of files : ";
    cin>>no_of_files;

    while(no_of_files--){
        cout<<"File Name : ";
        cin>>curr_file_name;
        FILE *fout = fopen(curr_file_name,"w");
        if(fout == NULL){
            cout<<"Failed to open file";
            continue;
        }
        cout<<"Transaction_name amount1 amount2 amount3 ..."<<endl;
        c = getc(stdin);
        bool newline = false;
        while(true){
            c = getc(stdin);
            if(c=='\n' || c=='\0'){
                if(newline)
                    break;
                newline = true;
            }else{
                newline = false;
            }
            fputc(c,fout);
        }

        fclose(fout);
    }
}
