//
// Created by Lenovo on 2023/10/9.
//

#ifndef QUEUE_QUEUE_H
#define QUEUE_QUEUE_H

template <class elemType>
class queue{
public:
    virtual bool isEmpty()const=0;
    virtual bool enQueue(const elemType&x)=0;
    virtual elemType deQueue()=0;
    virtual elemType getHead()const=0;
    virtual ~queue()=0;
};

//顺序储存
template <class elemType>
class seqQueue:public queue<elemType>{
private:
    elemType *elem;
    int maxSize;
    int front,rear;
    void doubleSpace();
public:
    seqQueue(int size=10);
    ~seqQueue();
    bool isEmpty()const;
    void enQueue(const elemType &x);
    elemType deQueue();
    elemType getHead()const;
};

template <class elemType>
seqQueue<elemType>::seqQueue(int size) {
    elem=new elemType[size];
    maxSize=size;
    front=rear=0;
}

template <class elemType>
seqQueue<elemType>::~seqQueue() {
    delete []elem;
}

template <class elemType>
bool seqQueue<elemType>::isEmpty() const {
    return front==rear;
}

template <class elemType>
elemType seqQueue<elemType>::getHead() const {
    return elem[(front+1)%maxSize];
}

template <class elemType>
elemType seqQueue<elemType>::deQueue() {
    front=(front+1)%maxSize;
    return elem[front];
}

template <class elemType>
void seqQueue<elemType>::doubleSpace() {
    elemType *tmp=elem;
    elem=new elemType[2*maxSize];
    for(int i=0;i<maxSize;i++){
        elem[i]=tmp[(i+front)%maxSize];
    }
    front=0;
    rear=maxSize-1;
    maxSize*=2;
    delete tmp;
}

template <class elemType>
void seqQueue<elemType>::enQueue(const elemType &x){
    if((rear+1)%maxSize==front) doubleSpace();
    rear=(rear+1)%maxSize;
    elem[rear]=x;
}

//链接队列
template <class elemType>
class linkQueue:public queue<elemType> {
private:
        struct node{
            elemType data;
            node* next;
            node(const elemType &x,node *n= nullptr){
                data=x;
                next=n;
            }
            node():next(nullptr){}
            ~node(){}
        };
        node *front,*rear;
public:
        linkQueue();
        ~linkQueue();
        bool isEmpty()const;
        void enQueue(const elemType &x);
        elemType deQueue();
        elemType getHead()const;
    };

template<class elemType>
linkQueue<elemType>::linkQueue() {
    front=rear= nullptr;
}

template<class elemType>
linkQueue<elemType>::~linkQueue() {
    node *p;
    while(front!= nullptr){
        p=front;
        front=front->next;
        delete p;
    }
}

template<class elemType>
bool linkQueue<elemType>::isEmpty() const {
    return front== nullptr;
}

template<class elemType>
void linkQueue<elemType>::enQueue(const elemType &x) {
    if(isEmpty()){
        front=rear=new node(x);
    }
    else{
    rear->next=new node(x);
    rear=rear->next;
    }
}

template<class elemType>
elemType linkQueue<elemType>::deQueue() {
    node *tmp=front;
    elemType x=tmp->data;
    front=front->next;
    if(front== nullptr) rear= nullptr; //出队后为空队列
    delete tmp;
    return x;
}

template<class elemType>
elemType linkQueue<elemType>::getHead() const {
    return front->data;
}


#endif //QUEUE_QUEUE_H
