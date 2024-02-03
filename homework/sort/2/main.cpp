#include <iostream>

using namespace std;
int divide(int a[],int low,int high){
    int stand=a[low];
    while (low<high){
        while (low<high&&stand<=a[high]) high--;
        if(low<high) a[low]=a[high];
        while (low<high&&stand>=a[low]) low++;
        if(low<high) a[high]=a[low];
    }
    a[low]=stand;
    return low;
}
void quicksort(int a[],int low,int high){
    if(low>=high) return;
    int mid= divide(a,low,high);
    quicksort(a,low,mid-1);
    quicksort(a,mid+1,high);
}
int main(void){
    int a[100000];
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    quicksort(a,0,n-1);
    for(int i=0;i<n;i++) cout<<a[i]<<' ';

    return 0;
}

