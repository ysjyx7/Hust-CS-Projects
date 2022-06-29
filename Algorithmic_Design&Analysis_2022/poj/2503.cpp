#include<iostream>
#include<string>
#include<stdio.h>
#include<map>
using namespace std;
int main()
{
    map<string,string> hash;
    string str1;
    string str2;
    while(1)
    {
        char c;
        if((c=getchar())=='\n')
        {
            break;
        }
        cin>>str1;
        str1=c+str1;
        cin>>str2;
        getchar();
        hash[str2]=str1;
    }
   // string str1;
    char word[11];
    while(scanf("%s",word)!=EOF)
    {
        if(hash.count(word))
            cout<<hash[word]<<endl;
        else
            cout<<"eh"<<endl;
    }

}