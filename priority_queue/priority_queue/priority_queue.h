//
// Created by Lenovo on 2023/11/14.
//

#ifndef PRIORITY_QUEUE_PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_PRIORITY_QUEUE_H
#include <iostream>
#include "queue"
using namespace std;
template <class Type>
class priorityQueue:public queue<Type>
{
public:
    priorityQueue(int capacity = 100);
    priorityQueue(const Type data[],int size);
    ~priorityQueue();
    bool isEmpty()const;
    void enQueue(const Type &x);
    Type deQueue();
    Type getHead()const;
private:
    int currentSize;
    Type *array;
    int maxsize;

    void doubleSpace();
    void buildHeap();
    void percolateDown(int hole);
};

template<class Type>
priorityQueue<Type>::priorityQueue(int capacity) {
    array=new Type[capacity];
    currentSize=0;
    maxsize=capacity;
}

template<class Type>
priorityQueue<Type>::priorityQueue(const Type *data, int size) {
    array = new Type[maxsize];
    for(int i=0;i<size;i++){
        array[i+1]=data[i];
    }
    buildHeap();
}

template<class Type>
priorityQueue<Type>::~priorityQueue() {
    delete []array;
}

template<class Type>
bool priorityQueue<Type>::isEmpty() const {
    return currentSize==0;
}

template<class Type>
void priorityQueue<Type>::enQueue(const Type &x) {
    if(currentSize==maxsize-1) doubleSpace();
    ++currentSize;
    //向上过滤
    int hole=currentSize;
    for(;hole>1&&x<array[hole/2];hole/=2){
        array[hole]=array[hole/2];
    }
    array[hole]=x;
}

template<class Type>
Type priorityQueue<Type>::deQueue() {
    Type minitem=array[1];
    array[1]=array[currentSize--];
    percolateDown(1);
    return minitem;
}

template<class Type>
Type priorityQueue<Type>::getHead() const {
    return array[1];
}

template<class Type>
void priorityQueue<Type>::doubleSpace() {
    Type *tmp= array;
    delete []array;
    maxsize*=2;
    array=new Type[maxsize];
    for(int i=0;i<=currentSize;i++){
        array[i]=tmp[i];
    }
    delete []tmp;
}

template<class Type>
void priorityQueue<Type>::buildHeap() {
    for(int i=currentSize/2;i>0;--i){
        percolateDown(i);
    }

}

template<class Type>
void priorityQueue<Type>::percolateDown(int hole) {
    int child;
    Type tmp=array[hole];
    for(;hole*2<=currentSize;hole=child){
        child=hole*2;
        if(child<currentSize&&array[child+1]<array[child]) child++;
        if(array[child]<tmp) array[hole]=array[child];
        else break;
    }
    array[hole]=tmp;
}


#endif //PRIORITY_QUEUE_PRIORITY_QUEUE_H
