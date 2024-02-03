//
// Created by Lenovo on 2023/11/18.
//

#ifndef BST_BST_H
#define BST_BST_H
#include <iostream>
//集合的定义
template<class KEY,class OTHER>
        struct SET{
            KEY key;
            OTHER other;
        };

//动态查找表抽象类
template<class KEY,class OTHER>
class dynamicSearchTable{
public:
     virtual SET<KEY,OTHER> *find(const KEY &x) const=0;
     virtual void insert(const SET<KEY,OTHER> &x)=0;
     virtual void remove(const KEY &x)=0;
     virtual ~dynamicSearchTable(){};
};

//BST定义
template<class KEY,class OTHER>
class BST:public dynamicSearchTable<KEY,OTHER>{
private:
    struct BinaryNode{
        SET<KEY,OTHER> data;
        BinaryNode *left;
        BinaryNode *right;
        BinaryNode(const SET<KEY,OTHER> thedata, BinaryNode *l= nullptr,BinaryNode *r= nullptr){
            data=thedata;
            left=l;right=r;
        }
    };
    BinaryNode *root;
public:
    BST();
    ~BST();
    SET<KEY,OTHER> *find(const KEY &x) const;
    void insert(const SET<KEY,OTHER> &x);
    void remove(const KEY &x);
private:
    void insert(const SET<KEY,OTHER> &x,BinaryNode *&t);
    void remove(const KEY &x,BinaryNode *&t);
    SET<KEY,OTHER> *find(const KEY &x,BinaryNode *t) const;
    void makeEmpty(BinaryNode *t);
};

//BST实现
template<class KEY, class OTHER>
BST<KEY, OTHER>::BST() {
    root= nullptr;
}

template<class KEY, class OTHER>
BST<KEY, OTHER>::~BST() {
    makeEmpty(root);
}

template<class KEY, class OTHER>
SET<KEY, OTHER> *BST<KEY, OTHER>::find(const KEY &x) const {
    find(x,root);
}

template<class KEY, class OTHER>
void BST<KEY, OTHER>::insert(const SET<KEY, OTHER> &x) {
    insert(x,root);
}

template<class KEY, class OTHER>
void BST<KEY, OTHER>::remove(const KEY &x) {
    remove(x,root);
}

template<class KEY, class OTHER>
void BST<KEY, OTHER>::insert(const SET<KEY, OTHER> &x, BST::BinaryNode *&t) {
    if(!t) t=new BinaryNode(x, nullptr, nullptr);
    else if(x<t->data.key) insert(x,t->left);
    else if(x>t->data.key) insert(x,t->right);
}

template<class KEY, class OTHER>
void BST<KEY, OTHER>::remove(const KEY &x, BST::BinaryNode *&t) {
    if(!t) return;
    if(x<t->data.key) remove(x,t->left);
    else if(x>t->data.key) remove(x,t->right);
    else if(t->left&&t->right){
        BinaryNode *tmp=t->right;
        while(tmp->left) tmp=tmp->left;
        t->data=tmp->data;
        remove(t->data.key,t->right);
    }
    else{
        BinaryNode *tmp=t;
        t=(t->left)?t->left:t->right;
        delete tmp;
    }
}

template<class KEY, class OTHER>
SET<KEY, OTHER> *BST<KEY, OTHER>::find(const KEY &x, BST::BinaryNode *t) const {
    if(t== nullptr||t->data.key==x){
        return (SET<KEY,OTHER> *) t;
    }
    if(x<t->data.key) return find(x,t->left);
    else return find(x,t->right);

    //非递归实现
//    BinaryNode *p=root;
//    while(p){
//        if(p->data.key==x) return (SET<KEY,OTHER> *) p;
//        else if(p->data.key<x) p=p->right;
//        else p=p->left;
//    }
//    return nullptr;
}

template<class KEY, class OTHER>
void BST<KEY, OTHER>::makeEmpty(BST::BinaryNode *t) {
    if(!t) return;
    makeEmpty(t->left);
    makeEmpty(t->right);
    delete t;
}



#endif //BST_BST_H
