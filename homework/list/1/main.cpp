#include<cstdio>
#include<iostream>
using namespace std;

int a[10000];
int main(void){
    int n,m;
    cin>>n>>m;
    for(int i=0;i<n;i++){
        cin>>a[i];
    }

    /////////////////////////
    // n,m,a已经输入
    int cur=0,maxsum=0;
    for(int i=0;i<m;i++){
        cur+=a[i];
    }
    for(int i=m;i<n;i++){
        cur+=a[i]-a[i-m];
        if(cur>maxsum) maxsum=cur;
    }
    cout<<maxsum;

    // 在标准输出流中输出(cout,pritf)
    /////////////////
    return 0;
}
