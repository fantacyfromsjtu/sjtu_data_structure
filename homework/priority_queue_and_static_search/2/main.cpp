#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

int main(){
    int n,m;
    cin>>n>>m;
    vector<int> a(n);
    vector<int> b(m);
    for(int i = 0; i < n; i++){
        cin>>a[i];
    }
    for(int i = 0; i < m; i++){
        cin>>b[i];
    }
    //输入已经给出
    for(auto &x:b){
        int low=0,high=n-1,mid;
        bool flag= false;
        while(low<=high){
            mid=(low+high)/2;
            if(a[mid]==x) {
                cout<<1<<endl;
                flag= true;
                break;
            }
            else if(a[mid]<x) low=mid+1;
            else high=mid-1;
        }
        if(!flag) cout<<0<<endl;
    }
    //在标准输出流中输出(cout,printf)
    return 0;
}