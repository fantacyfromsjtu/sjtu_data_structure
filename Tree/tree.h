//
// Created by Lenovo on 2023/11/1.
//

#ifndef TREE_TREE_H
#define TREE_TREE_H
#include <iostream>
#include <queue>
#include <stack>
using namespace std;
template <class T>
class tree{
public:
    virtual void clear()=0;
    virtual T root(T flag)const=0;
    virtual T parent(T x,T flag)const=0;
    virtual T child(T x,int i,T flag)const=0;
    virtual void remove(T x,int i)=0;
    virtual void traverse()const=0;
};
template <class T>
class btree{
public:
    virtual void clear()=0;
    virtual bool isEmpty()const=0;
    virtual T Root(T flag)const=0;
    virtual T parent(T x,T flag)const=0;
    virtual T lchild(T x,T flag)const=0;
    virtual T rchild(T x,T flag)const=0;
    virtual void delLeft(T x)=0;
    virtual void delRight(T x)=0;
    virtual void preOrder()const=0;
    virtual void midOrder()const=0;
    virtual void postOrder()const=0;
    virtual void levelOrder()const=0;
};

//二叉链表类
template <class T>
class binaryTree:public btree<T>{
    friend void printTree(const binaryTree &t, T flag);
private:
    struct Node{
        Node *left,*right;
        T data;
        Node():left(nullptr),right(nullptr){}
        Node(T item,Node *L= nullptr,Node* R= nullptr){
            data=item;
            left=L;
            right=R;
        }
        ~Node(){}
    };
    Node *root;

public:
    binaryTree():root(nullptr){}
    binaryTree(T x){
        root=new Node(x);
    }
    ~binaryTree();
    void clear();
    bool isEmpty()const;
    T Root (T flag) const;
    T lchild(T x,T flag)const;
    T rchild(T x,T flag)const;
    void delLeft(T x);
    void delRight(T x);
    void preOrder()const;
    void midOrder()const;
    void postOrder()const;
    void preOrder_nodigui()const;
    void midOrder_nodigui()const;
    void postOrder_nodigui()const;
    void levelOrder()const;
    void createTree(T flag);
    T parent(T x, T flag)const{return flag;}
private:
    Node *find(T x,Node *t)const;
    void clear(Node *&t);
    void preOrder(Node *t)const;
    void midOrder(Node *t)const;
    void postOrder(Node *t)const;

    Node *buildTree_with_pre_mid(T pre[], int pl, int pr, T mid[], int ml, int mr);
    Node *buildTree_with_mid_post(T post[],int pl,int pr,T mid[],int ml,int mr);
};


template<class T>
binaryTree<T>::~binaryTree() {
    clear(root);
}

template<class T>
void binaryTree<T>::clear() {
    clear(root);
}

template<class T>
bool binaryTree<T>::isEmpty() const {
    return root== nullptr;
}

template<class T>
T binaryTree<T>::Root(T flag) const {
    if(!root) return flag;
    return root->data;
}

template<class T>
T binaryTree<T>::lchild(T x, T flag) const {
    Node *cur=find(x,root);
    if(!cur||!cur->left) return flag;
    return cur->left->data;
}

template<class T>
T binaryTree<T>::rchild(T x, T flag) const {
    Node *cur=find(x,root);
    if(!cur||!cur->right) return flag;
    return cur->right->data;
}

template<class T>
void binaryTree<T>::delLeft(T x) {
    Node *cur=find(x,root);
    if(!cur) return;
    clear(cur->left);
}

template<class T>
void binaryTree<T>::delRight(T x) {
    Node *cur=find(x,root);
    if(!cur) return;
    clear(cur->right);
}

template<class T>
void binaryTree<T>::preOrder() const {
    cout<<"前序遍历"<<endl;
    preOrder(root);
}

template<class T>
void binaryTree<T>::midOrder() const {
    cout<<"中序遍历"<<endl;
    midOrder(root);
}

template<class T>
void binaryTree<T>::postOrder() const {
    cout<<"后序遍历"<<endl;
    postOrder(root);
}

template<class T>
void binaryTree<T>::levelOrder() const {
    cout<<"层次遍历"<<endl;
    if(!root)
        return;
    queue<Node *> que;
    Node *tmp;
    que.emplace(root);
    while (!que.empty()){
        tmp=que.front();
        que.pop();
        cout<<tmp->data<<' ';
        if(tmp->left) que.emplace(tmp->left);
        if(tmp->right) que.emplace(tmp->right);
    }
}

template<class T>
void binaryTree<T>::createTree(T flag) {
    queue<Node *> que;
    Node *tmp;
    T x,ldata,rdata;
    //创建树，输入flag表示空
    cout<<"输入根节点"<<endl;
    cin>>x;
    root=new Node(x);
    que.emplace(root);
    while (!que.empty()){
        tmp=que.front();
        que.pop();
        cout<<"输入"<<tmp->data<<"的两个儿子，"<<flag<<"表示空节点";
        cin>>ldata>>rdata;
        if(ldata!=flag){
            tmp->left=new Node(ldata);
            que.emplace(tmp->left);
        }
        if(rdata!=flag){
            tmp->right=new Node(rdata);
            que.emplace(tmp->right);
        }
    }
    cout<<"complete!"<<endl;
}

template<class T>
typename binaryTree<T>::Node *binaryTree<T>::find(T x, binaryTree::Node *t) const {
    Node *tmp;
    if(!t) return nullptr;
    if(t->data==x) return t;
    if(tmp= find(x,t->left)) return tmp;
    else return find(x,t->right);
}

template<class T>
void binaryTree<T>::clear(binaryTree::Node *&t) {
    if(!t) return;
    clear(t->left);
    clear(t->right);
    delete t;
    t= nullptr;
}

template<class T>
void binaryTree<T>::preOrder(binaryTree::Node *t) const {
    if(!t) return;
    cout<<t->data<<' ';
    preOrder(t->left);
    preOrder(t->right);
}

template<class T>
void binaryTree<T>::midOrder(binaryTree::Node *t) const {
    if(!t) return;
    preOrder(t->left);
    cout<<t->data<<' ';
    preOrder(t->right);
}

template<class T>
void binaryTree<T>::postOrder(binaryTree::Node *t) const {
    if(!t) return;
    preOrder(t->left);
    preOrder(t->right);
    cout<<t->data<<' ';
}

template <class T>
void printTree(const binaryTree<T> &t,T flag){
    queue<T> q;
    q.emplace(t.root->data);
    while(!q.empty()){
        char p,l,r;
        p=q.front();
        q.pop();
        l=t.lchild(p,flag);
        r=t.rchild(p,flag);
        cout<<p<<' '<<l<<' '<<r<<' ';
        if(l!=flag) q.emplace(l);
        if(r!=flag) q.emplace(r);
    }
}
//遍历的非递归实现
template<class T>
void binaryTree<T>::preOrder_nodigui() const {
    cout<<"前序遍历（非递归）"<<endl;
    stack<Node*> s;
    if(!root) return;
    s.push(root);
    Node *tmp;
    while (!s.empty()){
        tmp=s.top();
        s.pop();
        cout<<tmp->data;
        if(tmp->left) s.push(tmp->left);
        if(tmp->right) s.push(tmp->right);
    }
}

template<class T>
void binaryTree<T>::midOrder_nodigui() const {
    cout<<"中序遍历（非递归）"<<endl;
    if(!root)
        return;
    stack<pair<Node*,int>> s;
    pair<Node*,int> ROOT(root,0);
    s.emplace(ROOT);
    pair<Node*,int> cur;
    while(!s.empty()){
        cur=s.top();
        s.pop();
        if(cur.second==0){
            cur.second++;
            s.push(cur);
            if(cur.first->left) s.push(cur.first->left,0);
        }
        else{
            cout<<cur.first->data<<' ';
            if(cur.first->right) s.push(cur.first->right,0);
        }
    }
}

template<class T>
void binaryTree<T>::postOrder_nodigui() const {
    cout<<"后序遍历（非递归）"<<endl;
    if(!root)
        return;
    stack<pair<Node*,int>> s;
    pair<Node*,int> ROOT(root,0);
    s.emplace(ROOT);
    pair<Node*,int> cur;
    while(!s.empty()){
        cur=s.top();
        s.pop();
        if(cur.second==0){
            cur.second++;
            s.push(cur);
            if(cur.first->left) s.push(cur.first->left,0);
        }
        else if(cur.second==1){
            cur.second++;
            s.push(cur);
            if(cur.first->right) s.push(cur.first->right,0);
        }
        else{
            cout<<cur.first->data<<' ';
        }
    }
}
//根据前序遍历和中序遍历建立二叉树
template<class T>
typename binaryTree<T>::Node *binaryTree<T>::
        buildTree_with_pre_mid(T pre[], int pl, int pr, T mid[], int ml, int mr) {
    Node *p,*leftroot,*rightroot;
    int i=0,pos,num;
    int lpl,lpr,rpl,rpr;//前序遍历左（右）子树的左（右）边界；
    int lml,lmr,rml,rmr;//中序遍历左（右）子树的左（右）边界；
    if(pl>pr) return nullptr;
    p=new Node(pre[pl]);
    for(i=ml;i<=mr;i++){
        if(mid[i]==p->data){
            pos=i;
            break;
        }
    }
    num=pos-ml;
    lpl=pl+1;
    lpr=pl+num;
    lml=ml;
    lmr=pos-1;
    leftroot= buildTree_with_pre_mid(pre,lpl,lpr,mid,lml,lmr);
    rpl=pl+num+1;
    rpr=pr;
    rml=pos+1;
    rmr=mr;
    rightroot= buildTree_with_pre_mid(pre,rpl,rpr,mid,rml,rmr);
    p->left=leftroot;
    p->right=rightroot;
    return p;
}

//根据后序遍历和中序遍历建立二叉树
template<class T>
typename binaryTree<T>::Node *binaryTree<T>::
        buildTree_with_mid_post(T post[], int pl, int pr, T mid[], int ml, int mr) {
    Node *p,*leftroot,*rightroot;
    int i=0,pos,num;
    int lpl,lpr,rpl,rpr;//后序遍历左（右）子树的左（右）边界；
    int lml,lmr,rml,rmr;//中序遍历左（右）子树的左（右）边界；
    if(pl>pr) return nullptr;
    p=new Node(post[pr]);
    for(i=ml;i<=mr;i++){
        if(mid[i]==p->data){
            pos=i;
            break;
        }
    }
    num=pos-ml;
    lpl=pl;
    lpr=pl+num;
    lml=ml;
    lmr=pos-1;
    leftroot= buildTree_with_mid_post(post,lpl,lpr,mid,lml,lmr);
    rpl=pl+num+1;
    rpr=pr-1;
    rml=pos+1;
    rmr=mr;
    rightroot= buildTree_with_mid_post(post,rpl,rpr,mid,rml,rmr);
    p->left=leftroot;
    p->right=rightroot;
    return p;
}


#endif //TREE_TREE_H
