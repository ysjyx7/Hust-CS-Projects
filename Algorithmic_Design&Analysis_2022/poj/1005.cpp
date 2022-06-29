#include<iostream>
#include<cmath>
#define pi 3.1415926
using namespace std;
int main()
{
    int n;
    cin>>n;
    double x,y;
    int year;
    for(int i=0;i<n;i++)
    {
        cin>>x>>y;
        double temp=(x*x+y*y)*pi/100;
        year=(int)temp+1;
        cout<<"Property "<<i+1<<": This property will begin eroding in year "<<year<<"."<<endl;
    }
    cout<<"END OF OUTPUT.";
}