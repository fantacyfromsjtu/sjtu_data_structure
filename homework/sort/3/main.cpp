#include<iostream>
using namespace std;
void merge(int a[],int low,int mid,int high){
    int *tmp=new int[high-low+1];
    int i=low,j=mid,k=0;
    while (i<mid&&j<=high){
        if(a[i]<a[j]) tmp[k++]=a[i++];
        else tmp[k++]=a[j++];
    }
    while (i<mid) tmp[k++]=a[i++];
    while(j<=high) tmp[k++]=a[j++];
    for(int p=0;p<k;p++){
        a[p+low]=tmp[p];
    }
    delete[]tmp;
}
void mergesort(int a[],int low,int high){
    if(low==high) return;
    int mid=(low+high)/2;
    mergesort(a,low,mid);
    mergesort(a,mid+1,high);
    merge(a,low,mid+1,high);
}

int main(){
    int a[100000];
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    mergesort(a,0,n-1);
    for(int i=0;i<n;i++) cout<<a[i]<<' ';


    return 0;
}
