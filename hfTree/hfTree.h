//
// Created by Lenovo on 2023/11/5.
//

#ifndef HFTREE_HFTREE_H
#define HFTREE_HFTREE_H
#include <iostream>
#include <string>
using namespace std;
template <class Type>
class hfTree{
private:
    struct Node{
        Type data;
        int weight;
        int parent,left,right;
    };
    Node *elem;
    int length;
private:
    struct hfCode{
        Type data;
        string code;
    };
    hfTree(const Type* v,const int *w,int size);
    void getCode(hfCode result[]);
    ~hfTree(){
        delete []elem;
    }
};

template <class Type>
hfTree<Type>::hfTree(const Type *v, const int *w, int size) {
    int min1,min2,x,y;
    length=2*size;
    elem= new Node [length];
    //初值
    for(int i=size;i<length;i++){
        elem[i].data=v[i-size];
        elem[i].weight=w[i-size];
        elem[i].parent=elem[i].right=elem[i].left=0;
    }
    if(size==1){
        return;
    }
    for(int i=size-1;i>0;--i){
        min1=min2=INT_MAX;
        x=y=0;
        for(int j=i+1;j<size;j++){
            if(elem[j].weight<min1){
                min2=min1;
                x=y;
                min1=elem[j].weight;
                y=j;
            }
            else if(elem[j].weight<min2){
                min2=elem[j].weight;
                x=j;
            }
        }
        elem[i].weight=min1+min2;
        elem[i].left=x;
        elem[i].right=y;
        elem[i].parent=0;
        elem[x].parent=i;
        elem[y].parent=i;
    }
}
template <class Type>
void hfTree<Type>::getCode(hfTree::hfCode *result) {
    int size=length/2;
    int p,s;
    for(int i=size;i<length;++i){
        result[i-size].data=elem[i].data;
        result[i-size].code="";
        p=elem[i].parent;s=i;
        while (p){
            if(elem[p].left==s){
                result[i-size].code+='0';
            }
            else result[i-size].code+='1';
            s=p;
            p=elem[p].parent;
        }
    }
}
#endif //HFTREE_HFTREE_H
