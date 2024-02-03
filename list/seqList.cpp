//
// Created by Lenovo on 2023/9/25.
//
#include "list.h"
class OutofBound{};
class IllegalSize{};
template <class elemType>
class seqList:public list<elemType>{
private:
    elemType *data;
    int currentLength;
    int maxSize;
    void doubleSpace();
public:
    seqList(int initSize=10);
    ~seqList();
    void clear();
    int length()const;
    void insert(int i,const elemType &x);
    void remove(int i);
    int search(const elemType &x) const;
    elemType visit(int i) const;
    void traverse() const;
};

template<class elemType>
void seqList<elemType>::doubleSpace() {
    maxSize*=2;
    elemType *tmp=data;
    if(!tmp) throw IllegalSize();
    data=new elemType[maxSize];
    for(int i=0;i<currentLength;i++) data[i]=tmp[i];
    delete []tmp;
}

template <class elemType>
seqList<elemType>::seqList(int initSize) {
    data = new elemType [initSize];
    currentLength=0;
    maxSize=initSize;
}
template<class elemType>
seqList<elemType>::~seqList() {
    delete []data;
}

template<class elemType>
void seqList<elemType>::clear() {
    currentLength=0;
}

template<class elemType>
int seqList<elemType>::length() const {
    return currentLength;
}

template<class elemType>
void seqList<elemType>::insert(int i, const elemType &x) {
    if(i<0||i>currentLength) throw OutofBound();
    if(currentLength==maxSize) doubleSpace();
    for(int j=currentLength;j>i;j--){
        data[j]=data[j-1];
    }
    data[i]=x;
    ++currentLength;
}

template<class elemType>
void seqList<elemType>::remove(int i) {
    if(i<0||i>=currentLength) throw OutofBound();
    for(int j=i;j<currentLength-1;j++){
        data[j]=data[j+1];
    }
    --currentLength;
}

template<class elemType>
int seqList<elemType>::search(const elemType &x) const {
    for(int i=0;i<currentLength;i++){
        if(data[i]==x) return i;
    }
    return -1;
}

template<class elemType>
elemType seqList<elemType>::visit(int i) const {
    if(i<0||i>=currentLength) throw OutofBound();
    return data[i];
}

template<class elemType>
void seqList<elemType>::traverse() const {
    cout<<endl;
    for(int i=0;i<currentLength;++i) cout<<data[i]<<' ';
}


