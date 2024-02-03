#include <iostream>
using namespace std;
template <class elemType>
class queue{
public:
    virtual bool isEmpty()const=0;
    virtual void enQueue(const elemType&x)=0;
    virtual void deQueue()=0;
    virtual elemType getHead()const=0;
    virtual ~queue(){};
};

//顺序储存
template <class elemType>
class seqQueue:public queue<elemType>{
private:
    elemType *elem;
    int maxSize;
    int front,rear;
    int cursize;
    void doubleSpace();
public:
    seqQueue(int size=10);
    ~seqQueue();
    bool isEmpty()const;
    void enQueue(const elemType &x);
    void deQueue();
    elemType getHead()const;
};

template <class elemType>
seqQueue<elemType>::seqQueue(int size) {
    elem=new elemType[size];
    maxSize=size;
    front=rear=0;
    cursize=0;
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
void seqQueue<elemType>::deQueue() {
    if(isEmpty()){
        cout<<front<<' '<<cursize<<endl;
        return;
    }
    front=(front+1)%maxSize;
    cursize--;
    cout<<front<<' '<<cursize<<endl;
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
    cursize++;
    cout<<rear<<' '<<cursize<<endl;
}
int main()
{
    int s, n;
    cin >> s >> n;
    seqQueue<int> que(s);
    for (int i = 0; i < n; i++)
    {
        int t;
        cin >> t;
        if(!t){
            int x;
            cin>>x;
            que.enQueue(x);
        }
        else{
            que.deQueue();
        }
    }
    return 0;
}
