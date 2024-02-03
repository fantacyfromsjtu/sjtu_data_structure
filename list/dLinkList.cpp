//
// Created by Lenovo on 2023/10/1.
//
#include "list.h"
template <class elemType>
class dLinkList:public list<elemType>{
private:
    struct node{
        elemType data;
        node* next,*prev;

        node(const elemType &x,node *p= nullptr,node *n= nullptr){
            data=x;
            prev=p;
            next=n;
        }
        node():prev(nullptr),next(nullptr){}
        ~node(){}
    };
    node *head,*tail;
    int currentLength;

    node *move(int i) const;

public:
    dLinkList();
    ~dLinkList(){
        clear();
        delete head;
        delete tail;
    }
    void clear();
    int length() const;
    void insert(int i,const elemType &x);
    void remove(int i);
    int search(const elemType &x) const;
    elemType visit(int i) const;
    void traverse()const;
};

template<class elemType>
typename dLinkList<elemType>::node *dLinkList<elemType>::move(int i) const {
    if(i<-1||i>=currentLength) return nullptr;
    auto p=head;
    while (i-->=0) p=p->next;
    return p;
}

template<class elemType>
dLinkList<elemType>::dLinkList() {
    head=new node;
    tail=new node;
    head->next=tail;
    tail->prev=head;
    currentLength=0;
}

template<class elemType>
void dLinkList<elemType>::clear() {
    node *p=head->next,*q;
    head->next=tail;
    tail->prev=head;
    while(p!=tail){
        q=p->next;
        delete p;
        p=q;
    }
    currentLength=0;
}

template<class elemType>
int dLinkList<elemType>::length() const {
    return currentLength;
}

template<class elemType>
void dLinkList<elemType>::insert(int i, const elemType &x) {
    node *pos,*tmp;
    pos= move(i);
    tmp= new node(x,pos->prev,pos);
    pos->prev->next=tmp;
    pos->prev=tmp;
    ++currentLength;
}

template<class elemType>
void dLinkList<elemType>::remove(int i) {
    node *p= move(i);
    p->prev->next=p->next;
    p->next->prev=p->prev;
    delete p;
    --currentLength;
}

template<class elemType>
int dLinkList<elemType>::search(const elemType &x) const {
    node *p=head->next;
    int i=0;
    while(p!=tail){
        if(p->data==x) return i;
        i++;
        p=p->next;
    }
    return -1;
}

template<class elemType>
elemType dLinkList<elemType>::visit(int i) const {
    return move(i)->data;
}

template<class elemType>
void dLinkList<elemType>::traverse() const {
    node *p=head->next;
    cout<<endl;
    while(p!=tail){
        cout<<p->data<<" ";
        p=p->next;
    }
    cout<<endl;
}

