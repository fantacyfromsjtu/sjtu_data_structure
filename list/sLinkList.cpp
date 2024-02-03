//
// Created by Lenovo on 2023/10/1.
//
#include "list.h"
template <class elemType>
class sLinkList:public list<elemType>{
private:
    struct node{
        elemType data;
        node *next;
        node(const elemType *x,node *n= nullptr){
            data=x;
            next=n;
        }
        node():next(nullptr){}
        ~node(){}
    };
    node *head;
    int currentLength;

    node *move(int i) const;//返回第i个节点的地址

public:
    sLinkList();
    ~sLinkList(){
        clear();
        delete head;
    }
    void clear();
    int length()const {
        return currentLength;
    }
    void insert(int i,const elemType &x);
    void remove(int i);
    int search(const elemType &x) const;
    elemType visit(int i) const;
    void traverse()const;
};


template<class elemType>
typename sLinkList<elemType>::node *sLinkList<elemType>::move(int i) const {
    if(i<-1||i>=currentLength) return nullptr;
    auto p=head;
    while (i-->=0) p=p->next;
    return p;
}

template<class elemType>
sLinkList<elemType>::sLinkList() {
    head = new node();
    currentLength=0;
}

template<class elemType>
void sLinkList<elemType>::clear() {
    node *p=head->next,*q;
    head->next= nullptr;
    while (p){
        q=p->next;
        delete p;
        p=q;
    }
    currentLength=0;
}

template<class elemType>
void sLinkList<elemType>::insert(int i, const elemType &x) {
    if(i<0||i>currentLength) return;
    node* p = move(i-1);
    p->next=new node(x,p->next);
    ++currentLength;
}

template<class elemType>
void sLinkList<elemType>::remove(int i) {
    if(i<0||i>=currentLength) return;
    node *p= move(i-1);
    node *q=p->next;
    p->next=q->next;
    delete q;
    --currentLength;
}

template<class elemType>
int sLinkList<elemType>::search(const elemType &x) const {
    node *p=head->next;
    int i=0;
    while(p){
        if(p->data==x) return i;
        i++;
        p=p->next;
    }
    return -1;
}

template<class elemType>
elemType sLinkList<elemType>::visit(int i) const {
    return move(i)->data;
}

template<class elemType>
void sLinkList<elemType>::traverse() const {
    node *p=head->next;
    cout<<endl;
    while(p){
        cout<<p->data<<' ';
        p=p->next;
    }
    cout<<endl;
}
