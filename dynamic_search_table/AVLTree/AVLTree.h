//
// Created by Lenovo on 2023/11/21.
//

#ifndef AVLTREE_AVLTREE_H
#define AVLTREE_AVLTREE_H
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

//AVL树定义
template<class KEY,class OTHER>
class AvlTree:public dynamicSearchTable<KEY,OTHER>{
    struct AvlNode{
        SET<KEY,OTHER> data;
        AvlTree *left;
        AvlTree *right;
        int height; //节点的高度

        AvlNode(const SET<KEY,OTHER> &element,AvlTree *lt,AvlTree *rt,int h=1):
        data(element),left(lt),right(rt),height(h){}
    };

    AvlNode *root;

public:
    AvlTree(){
        root= nullptr;
    }
    ~AvlTree(){
        makeEmpty(root);
    }
    SET<KEY,OTHER> *find(const KEY &x)const;
    void insert(const SET<KEY,OTHER> &x);
    void remove(const KEY &x);
private:
    void insert(const SET<KEY,OTHER> &x,AvlNode* &t);
    bool remove(const KEY &x,AvlNode* &t);
    void makeEmpty(AvlNode *t);
    int height(AvlNode *t)const{
        if(!t) return 0;
        else return t->height;
    }
    void LL(AvlNode* &t);
    void LR(AvlNode* &t);
    void RL(AvlNode* &t);
    void RR(AvlNode* &t);
    int max(int a,int b){
        return (a>b)?a:b;
    }
    bool adjust(AvlNode *&t,int subTree);
};

template<class KEY, class OTHER>
SET<KEY, OTHER> *AvlTree<KEY, OTHER>::find(const KEY &x) const {
    AvlNode *t=root;
    while(t){
        if(t->data.key==x) return (SET<KEY,OTHER>*) t;
        if(x<t->data.key) t=t->left;
        else t=t->right;
    }
    return nullptr;
}

template<class KEY, class OTHER>
void AvlTree<KEY, OTHER>::insert(const SET<KEY, OTHER> &x) {
    insert(x,root);
}

template<class KEY, class OTHER>
void AvlTree<KEY, OTHER>::remove(const KEY &x) {
    remove(x,root);
}

template<class KEY, class OTHER>
void AvlTree<KEY, OTHER>::insert(const SET<KEY, OTHER> &x, AvlTree::AvlNode *&t) {
    if(t== nullptr) t= new AvlNode(x, nullptr, nullptr);
    else if(x.key<t->data.key){
        insert(t->left);
        if(height(t->left)- height(t->right)>1){
            if(x.key<t->left->data.key) LL(t);
            else LR(t);
        }
    }
    else{
        insert(t->right);
        if(height(t->left)- height(t->right)>1){
            if(x.key<t->left->data.key) RL(t);
            else RR(t);
        }
    }
    t->height=max(height(t->left), height(t->right))+1; //更新高度
}

template<class KEY, class OTHER>
bool AvlTree<KEY, OTHER>::remove(const KEY &x, AvlTree::AvlNode *&t) {
    if (!t) return true;
    if(x==t->data.key){
        if(t->left== nullptr ||t->right== nullptr){
            AvlNode* oldNode =t;
            t=(t->left) ? t->left : t->right;
            delete oldNode;
            return false;
        } else{
            AvlNode* tmp=t->right;
            while (tmp->left) tmp=tmp->left;
            t->data=tmp->data;
            if(remove(tmp->data.key,t->right)) return true; //删除后右子树没有变矮
            return adjust(t,1);
        }
    }
    if(x<t->data.key){
        if(remove(x,t->left)) return true;
        return adjust(t,0);
    }
    else{
        if(remove(x,t->right)) return true;
        return adjust(t,1);
    }
}

template<class KEY, class OTHER>
void AvlTree<KEY, OTHER>::makeEmpty(AvlTree::AvlNode *t) {
    if(!t) return;
    makeEmpty(t->left);
    makeEmpty(t->right);
    delete t;
}

template<class KEY, class OTHER>
void AvlTree<KEY, OTHER>::LL(AvlTree::AvlNode *&t) {
    AvlNode *t1=t->left; //未来的树根
    t->left=t1->right;
    t1->right=t;
    //维护高度
    t->height=max(height(t->left), height(t->right))+1;
    t1->height=max(height(t1->left), height(t))+1;
    t=t1;
}

template<class KEY, class OTHER>
void AvlTree<KEY, OTHER>::LR(AvlTree::AvlNode *&t) {
    RR(t->left);
    LL(t);
}

template<class KEY, class OTHER>
void AvlTree<KEY, OTHER>::RL(AvlTree::AvlNode *&t) {
    LL(t->right);
    RR(t);
}

template<class KEY, class OTHER>
void AvlTree<KEY, OTHER>::RR(AvlTree::AvlNode *&t) {
    AvlNode *t1=t->right;
    t->right=t1->left;
    t1->left=t;
    //维护高度
    t->height=max(height(t->left), height(t->right))+1;
    t1->height=max(height(t1->right), height(t))+1;
    t=t1;
}

template<class KEY, class OTHER>
bool AvlTree<KEY, OTHER>::adjust(AvlTree::AvlNode *&t, int subTree) {
    if(subTree){//在右子树上删除，使右子树变矮
        if(height(t->left)- height(t->right)==1) return true; //情况a;
        if(height(t->right)== height(t->left)){//情况b
            --t->height;
            return false;
        }
        if(height(t->left->right)> height(t->left->left)){//情况d
            LR(t);
            return false;
        }
        LL(t);
        if(height(t->right)== height(t->left)) return false;
        else return true;
    }
    else{
        if(height(t->right)- height(t->left)==1) return true; //情况a;
        if(height(t->left)== height(t->right)){//情况b
            --t->height;
            return false;
        }
        if(height(t->right->left)> height(t->right->right)){//情况d
            RL(t);
            return false;
        }
        RR(t);
        if(height(t->left)== height(t->right)) return false;
        else return true;
    }
}

#endif //AVLTREE_AVLTREE_H
