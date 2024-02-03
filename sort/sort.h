//
// Created by Lenovo on 2023/12/4.
//

#ifndef SORT_SORT_H
#define SORT_SORT_H
#include <iostream>
using namespace std;
//集合的定义
template<class KEY,class OTHER>
struct SET{
    KEY key;
    OTHER other;
};

// 插入排序（直接，二分，希尔）

//直接插入排序
template <class KEY,class OTHER>
void simple_insert_sort(SET<KEY,OTHER> a[],int size){
    SET<KEY,OTHER> tmp;int j;
    for(int i=1;i<size;i++){
        tmp=a[i];
        for(j=i-1;j>=0;j--){
            if(a[j]<=tmp.key) break;
            a[j+1]=a[j];
        }
        a[j+1]=tmp;
    }
}

//希尔排序
template <class KEY,class OTHER>
void shell_sort(SET<KEY,OTHER> a[],int size){
    int step,i,j;
    SET<KEY,OTHER> tmp;

    for(step=size/2;step>=1;step/=2){
        for(i=step;i<size;++i){
            tmp=a[i];
            for(j=i-step;j>=0;j-=step){
                if(a[j]<=tmp.key) break;
                a[j+step]=a[j];
            }
            a[j+step]=tmp;
        }
    }
}

//选择排序(直接选择排序，堆排序）

//直接选择排序
template <class KEY,class OTHER>
void simple_select_sort(SET<KEY,OTHER> a[],int size){
    int i,j,min;
    SET<KEY,OTHER>tmp;
    for(i=0;i<size-1;++i){
        min=i;
        for(j=i+1;j<size-1;++j){
            if(a[j].key<a[min].key) min=j;
        }
        tmp=a[i];
        a[i]=a[j];
        a[j]=tmp;
    }
}

//堆排序
template <class KEY,class OTHER>
void percolateDown(SET<KEY,OTHER>a[],int hole,int size){
    int child;
    SET<KEY,OTHER> tmp=a[hole];
    for(;hole*2+1<size;hole=child){
        child=hole*2+1;
        if(child!=size-1&&a[child].key<a[child+1].key) child++;
        if(a[child].key>tmp.key) a[hole]=a[child];
        else break;
    }
    a[hole]=tmp;
}
template <class KEY,class OTHER>
void heap_sort(SET<KEY,OTHER> a[],int size){
    int i;
    SET<KEY,OTHER> tmp;
    //建堆
    for(i=size/2-1;i>=0;i--){
        percolateDown(a,i,size);
    }
    //出队
    for(i=size-1;i>0;--i){
        tmp=a[0];
        a[0]=a[i];
        a[i]=tmp;
        percolateDown(a,0,i);
    }
}

//交换排序

//最会的冒泡
template <class KEY,class OTHER>
void bubbleSort(SET<KEY,OTHER>a[],int size){
    bool flag= true;
    for(int i=1;i<size&& flag;i++){
        flag= false;
        for(int j=0;j<size-i;j++){
            if(a[j].key>a[j+1].key){
                flag= true;
                SET<KEY,OTHER>tmp=a[j];
                a[j]=a[j+1];
                a[j+1]=tmp;
            }
        }
    }
}

//快速排序
template <class KEY,class OTHER>
int divide(SET<KEY,OTHER>a[],int low,int high){
    SET<KEY,OTHER> k=a[low];
    do{
        while (low<high&&a[high].key>=k.key) high--;
        if(low<high){
            a[low]=a[high];
            ++low;
        }
        while (low<high&&a[low].key<=k.key) low++;
        if(low<high){
            a[high]=a[low];
            --high;
        }
    } while (low!=high);
    a[low]=k;
    return low;
}
template<class KEY,class OTHER>
void quickSort(SET<KEY,OTHER>a[],int low,int high){
    if(low>=high)return;
    int mid= divide(a,low,high);
    quickSort(a,low,mid-1);
    quickSort(a,mid+1,high);
}
template<class KEY,class OTHER>
void quickSort(SET<KEY,OTHER>a[],int size){
    quickSort(a,0,size-1);
}

//归并排序
template<class KEY,class OTHER>
void merge(SET<KEY,OTHER>a[],int left,int mid,int right){
    auto *tmp=new SET<KEY,OTHER>[right-left+1];
    int i=left,j=mid,k=0;
    while(i<mid&&j<=right){
        if(a[i].key<a[j].key) tmp[k++]=a[i++];
        else tmp[k++]=a[j++];
    }
    while (i<mid) tmp[k++]=a[i++];
    while(j<=right) tmp[k++]=a[j++];
    i=left;
    while(i<=right){
        a[i]=tmp[i-left];
        i++;
    }
    delete[]tmp;
}

template <class KEY,class OTHER>
void mergeSort(SET<KEY,OTHER>a[],int left,int right){
    if(left==right) return;
    int mid=(left+right)/2;
    mergeSort(a,left,mid);
    mergeSort(a,mid+1,right);
    merge(a,left,mid+1,right);
}
template <class KEY,class OTHER>
void mergeSort(SET<KEY,OTHER>a[],int size){
    mergeSort(a,0,size-1);
}

//基数排序
template<class OTHER>
struct node{
        SET<int,OTHER> data;
        node *next;

        node(){
            next= nullptr;
        }
        node(SET<int,OTHER> d){
            data=d;
            next= nullptr;
        }
    };
template<class OTHER>
void bucketSort(node<OTHER>*&p){
    node<OTHER> *bucket[10], *last[10], *tail;
    int i,j,k,base=1,max=0,len=0;
    //先找最大键值
    for(tail=p;tail;tail=tail->next){
        if(tail->data.key>max) max=tail->data.key;
    }
    while(max>0){
        ++len;
        max/=10;
    }
    for(i=1;i<len;i++){
        for(j=0;j<=9;j++){
            bucket[j]=last[j]= nullptr;
        }
        while (p){
            k=p->data.key/base%10;
            if(bucket[k]== nullptr){
                bucket[k]=last[k]=p;
            }
            else last[k]=last[k]->next=p;
            p=p->next;
        }
        p= nullptr;
        for(j=0;j<=9;j++){
            if(bucket[j]== nullptr) continue;
            if(!p) p=bucket[j];
            else tail->next=bucket[j];
            tail=last[j];
        }
        tail->next= nullptr;
        base*=10;
    }
}
#endif //SORT_SORT_H
