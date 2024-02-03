#include <cstdio>
#include <iostream>

using namespace std;

int main() {
    int n,k;
    cin>>n>>k;
    int *a=new int[n];
    for(int i=0;i<n;i++) cin>>a[i];
    int *maxnum = new int[n-k+1];
    int *minnum = new int[n-k+1];

    for(int i=0;i<n-k+1;i++){
        int curmax=a[i],curmin=a[i];
        for(int j=i;j<i+k;j++){
            curmax=max(curmax,a[j]);
            curmin=min(curmin,a[j]);
        }
        maxnum[i]=curmax;
        minnum[i]=curmin;
    }
    for(int i=0;i<n-k+1;i++){
        cout<<minnum[i]<<' ';
    }
    for(int i=0;i<n-k+1;i++){
        cout<<maxnum[i]<<' ';
    }
    cout<<endl;


    return 0;
}
