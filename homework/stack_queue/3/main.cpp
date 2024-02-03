#include<iostream>
using namespace std;
class Outofbound{};
template<class elemType>
class stack{
public:
    virtual bool isEmpty()const=0;
    virtual void push(const elemType &x)=0;
    virtual elemType pop()=0;
    virtual elemType top()const=0;
    virtual ~stack(){}
};


template<class elemType>
class seqStack: public stack<elemType>{
private:
    elemType* elem;
    int maxsize;
    void doubleSpace();
public:
    seqStack(int initSize=0);
    ~seqStack();
    bool isEmpty()const;
    void push(const elemType&x);
    elemType pop();
    elemType top() const;

    int top_p;
};

template<class elemType>
seqStack<elemType>::seqStack(int initSize) {
    elem= new elemType[initSize];
    top_p=-1;
    maxsize=initSize;
}

template<class elemType>
seqStack<elemType>::~seqStack() {
    delete[]elem;
}

template<class elemType>
bool seqStack<elemType>::isEmpty() const {
    return top_p==-1;
}

template<class elemType>
void seqStack<elemType>::push(const elemType &x) {
    if(top_p==maxsize-1) doubleSpace();
    top_p++;
    elem[top_p]=x;
}

template<class elemType>
void seqStack<elemType>::doubleSpace() {
    elemType *tmp=elem;
    maxsize*=2;
    elem=new elemType[maxsize];
    for(int i=0;i<=top_p;i++) elem[i]=tmp[i];
    delete []tmp;
}

template<class elemType>
elemType seqStack<elemType>::pop() {
    if(isEmpty()) throw Outofbound();
    return elem[--top_p];
}

template<class elemType>
elemType seqStack<elemType>::top()const {
    if(isEmpty()) throw Outofbound();
    return elem[top_p];
}


//链接栈
template <class elemType>
class linkStack:public stack<elemType>{
private:
    struct node{
        elemType data;
        node *next;
        node():next(nullptr){}
        node(const elemType& x,node *n= nullptr){
            data=x;
            next=n;
        }
        ~node(){}
    };
    node *top_p;
public:
    linkStack();
    ~linkStack();
    bool isEmpty()const;
    void push(const elemType& x);
    elemType pop();
    elemType top()const;
};

template<class elemType>
linkStack<elemType>::linkStack() {
    top_p= nullptr;
}

template<class elemType>
linkStack<elemType>::~linkStack() {
    node *tmp;
    while (top_p){
        tmp=top_p;
        top_p=top_p->next;
        delete tmp;
    }
}

template<class elemType>
bool linkStack<elemType>::isEmpty() const {
    return top_p== nullptr;
}

template<class elemType>
void linkStack<elemType>::push(const elemType &x) {
    top_p=new node(x,top_p);
}

template<class elemType>
elemType linkStack<elemType>::pop() {
    if(isEmpty()) throw Outofbound();
    node *tmp=top_p;
    elemType x=tmp->data;
    top_p=top_p->next;
    delete tmp;
    return x;
}

template<class elemType>
elemType linkStack<elemType>::top() const {
    return top_p->data;
}

int order[50000];
bool isok(int n,int room){
    int carnum=0;
    seqStack<int> station;
    for(int i=0;i<n;i++){
        if(carnum==order[i]){
            carnum++;
            continue;
        }
        if(!station.isEmpty()&&station.top()==order[i]){
            station.pop();
            continue;
        }
        while(carnum!=order[i]){
            if(station.top_p+1==room||carnum==n-1) return false;
            station.push(carnum);
            carnum++;
        }
        carnum++;
    }
    return true;
}
int main(){
    int t;
    cin >>t;
    while(t--) {
        int n, m;
        cin >> n >> m;
        for (int i = 0; i < n; i++) cin >> order[i];
        if(isok(n,m)) cout<<"YES"<<endl;
        else cout<<"NO"<<endl;
    }
    return 0;
}
