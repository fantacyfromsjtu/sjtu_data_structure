#include<bits/stdc++.h>
using namespace std;


int main(void){
    int a[100000];
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    for(int i=0;i<n-1;i++){
        bool flag= false;
        for(int j=1;j<n-i;j++){
            if(a[j-1]>a[j]){
                flag= true;
                int tmp=a[j-1];
                a[j-1]=a[j];
                a[j]=tmp;
            }
        }
        if(!flag) break;
    }
    for(int i=0;i<n-1;i++){
        cout<<a[i]<<' ';
    }
    cout<<a[n-1];




    return 0;
}
