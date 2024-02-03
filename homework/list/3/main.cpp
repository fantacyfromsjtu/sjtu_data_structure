#include <iostream>
using namespace std;

template <class elemType>
class list
{
public:
    virtual int length() const = 0;
    virtual int search(const elemType &x) const = 0 ;
    virtual elemType visit(int i) const = 0;
    virtual void insert(int i, const elemType &x) = 0;
    virtual void remove(int i) = 0;
    virtual void clear() = 0;
    virtual void traverse() const = 0;
    virtual ~list() = default;
};
template<class elemType>
class LinkList: public list<elemType>{
    struct node{
        elemType data;
        node* next;

        explicit node(const elemType &x,node *n = nullptr){
            data=x;
            next=n;
        }
        node(){
            next= nullptr;
        }
        ~node(){}
    };
    int currentLength;
    node *head;

    node *move(int i)const;
public:
    LinkList();
    void clear();
    ~LinkList(){
        clear();
        delete head;
    }
    int length()const;
    int search(const elemType &x) const;
    elemType visit(int i) const;
    void insert(int i, const elemType &x);
    void remove(int i);
    void traverse() const;
};

template<class elemType>
LinkList<elemType>::LinkList() {
    head=new node;
    currentLength=0;
}

template<class elemType>
typename LinkList<elemType>::node *LinkList<elemType>::move(int i)const {
    if(i<-1||i>=currentLength) return nullptr;
    node *p=head;
    while (i-->=0) p=p->next;
    return p;
}

template<class elemType>
void LinkList<elemType>::clear() {
    node *p=head->next,*q;
    while (p){
        q=p->next;
        delete p;
        p=q;
    }
    currentLength=0;
}

template<class elemType>
int LinkList<elemType>::length() const {
    return currentLength;
}

template<class elemType>
int LinkList<elemType>::search(const elemType &x) const {
    node *p=head->next;
    int i=0;
    while(p){
        if(p->data==x)return i;
        i++;
        p=p->next;
    }
    return -1;
}

template<class elemType>
elemType LinkList<elemType>::visit(int i) const {
    return move(i)->data;
}

template<class elemType>
void LinkList<elemType>::insert(int i, const elemType &x) {
    node *p= move(i);
    p->next=new node(x,p->next);
    ++currentLength;
}

template<class elemType>
void LinkList<elemType>::remove(int i) {
    node *p= move(i-2);
    node *tmp=p->next;
    p->next=tmp->next;
    delete tmp;
    --currentLength;
}

template<class elemType>
void LinkList<elemType>::traverse() const {
    node *p=head->next;
    while(p){
        cout<<p->data<<' ';
        p=p->next;
    }

}

int main() {
    int n,m;
    cin>>n>>m;
    LinkList<int> L;
    for(int i=0;i<n;i++){
        int x;
        cin>>x;
        L.insert(i-1,x);
        cin.ignore();
    }
    for(int i=1;i<=m;i++){
        int op;
        cin>>op;
        if(op==1){
            int x,y;
            cin>>x>>y;
            L.insert(x-1,y);
        }
        else if(op==2){
            int x;
            cin>>x;
            L.remove(x);
        }
    }
    L.traverse();
    return 0;
}