//
// Created by Lenovo on 2023/9/25.
//

#ifndef LIST_LIST_H
#define LIST_LIST_H
#include <iostream>
using namespace std;
template <class elemType>
class list{
public:
    virtual void clear()=0;
    virtual int length() const = 0;
    virtual void insert(int i,const elemType &x)=0;
    virtual void remove(int i)=0;
    virtual int search(const elemType &x) const=0;
    virtual elemType visit(int i) const=0;
    virtual void traverse() const=0;
    virtual ~list(){};
};
#endif //LIST_LIST_H
