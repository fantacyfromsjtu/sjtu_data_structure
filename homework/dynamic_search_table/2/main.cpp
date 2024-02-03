#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;

template <class KEY, class OTHER>
struct SET
{
    KEY key;  //如学号
    OTHER other;  //包含姓名、性别、出生日期等的结构体变量
    bool operator == (const SET &x) const {
        return this->key == x.key;
    }
    bool operator < (const SET &x) const {
        return this->key < x.key;
    }
    bool operator > (const SET &x) const {
        return this->key > x.key;
    }
};

//动态查找表
template <class KEY, class OTHER>
class dynamicSearchTable
{
public:
    virtual SET<KEY, OTHER> *find(const KEY &x) const = 0;
    virtual void insert(const SET<KEY, OTHER> &x) = 0;
    virtual void remove(const KEY &x) = 0;
    virtual ~dynamicSearchTable() {};
};
//平衡二叉查找树
template <class KEY, class OTHER>
class AvlTree: public dynamicSearchTable<KEY, OTHER>
{
    struct AvlNode
    {
        SET<KEY, OTHER> data;
        AvlNode *left, *right;
        int height;  //结点的高度
        AvlNode(const SET<KEY, OTHER> &element, AvlNode *lt, AvlNode *rt, int h=1) :
                data(element), left(lt), right(rt), height(h) { }
    };
    AvlNode *root;

public:
    AvlTree() {root = NULL;}
    ~AvlTree() {}
    SET<KEY, OTHER> *find(const KEY &x) const;                      //查找非递归实现
    SET<KEY, OTHER> *find(const KEY &x, const AvlNode* &t) const;   //查找递归实现
    void insert(const SET<KEY, OTHER> &x) {insert(x, root);}
    void remove(const KEY &x) {remove(x, root);}
    vector<int> InOrder (){
        vector<int> order_list;
        return InOrder(root,order_list);
    }                               //按中序遍历输出平衡二叉树的结点的关键字值

private:
    void insert(const SET<KEY, OTHER> &x, AvlNode* &t) ;
    bool remove(const KEY &x, AvlNode* &t) ;
    int height(AvlNode *t) const { return t == NULL ? 0 : t->height;}
    void LL(AvlNode* &t);
    void LR(AvlNode* &t);
    void RL(AvlNode* &t);
    void RR(AvlNode* &t);
    int max(int a, int b) {return (a>b)?a:b;}
    bool adjust(AvlNode* &t, int subTree);
    vector<int> InOrder(AvlNode *t,vector<int> &order_list);
};

template <class KEY, class OTHER>
vector<int> AvlTree<KEY, OTHER>::InOrder(AvlNode *t,vector<int> &order_list)
{
    if(!t) return order_list;
    InOrder(t->left,order_list);
    order_list.push_back(t->data.key);
    InOrder(t->right,order_list);
    return order_list;
}

template <class KEY, class OTHER>
SET<KEY, OTHER>* AvlTree<KEY, OTHER>::find(const KEY &x, const AvlNode* &t) const
{
    if (!t) return NULL;

    if (x == t->data.key) return (SET<KEY, OTHER> *) t;
    if (x>t->data.key) return find(x, t->right);
    else return find(x, t->left);
}

template <class KEY, class OTHER>
SET<KEY, OTHER>* AvlTree<KEY, OTHER>::find(const KEY &x) const
{
    AvlNode *t = root;

    while (t != NULL && t->data.key != x)
        if (t->data.key > x) t = t->left;
        else t = t->right;

    if (t == NULL) return NULL;
    else return (SET<KEY, OTHER> *) t;
}

template <class KEY, class OTHER>
void AvlTree<KEY, OTHER>::insert(const SET<KEY, OTHER> &x, AvlNode* &t)
{
    if(t == NULL)                                              //在空树上插入
    {
        t = new AvlNode(x, NULL, NULL);
    }
    else if(x.key < t->data.key)                               //在左子树上插入
    {
        insert(x, t->left);
        if (height(t->left) - height(t->right) == 2)           //t失衡
            if (x.key < t->left->data.key) LL(t);
            else LR(t);
    }
    else if (x.key > t->data.key)                              //在右子树上插入
    {
        insert(x, t->right);
        if(height(t->left) - height(t->right) == - 2)          //t失衡
            if(x.key > t->right->data.key) RR(t);
            else RL(t);
    }
    //重新计算t的高度
    t->height = max(height(t->left), height(t->right)) + 1;
}

template <class KEY, class OTHER>
void AvlTree<KEY, OTHER>::LL(AvlNode* &t)
{
    AvlNode *t1 = t->left;                                   //未来的树根
    t->left = t1->right;
    t1->right = t;
    t->height = max(height(t->left), height(t->right)) + 1;
    t1->height = max(height(t1->left), height(t)) + 1;
    t = t1;                                                  //新的父子关联
}

template <class KEY, class OTHER>
void AvlTree<KEY, OTHER>::RR(AvlNode* &t)
{
    AvlNode *t1 = t->right;
    t->right = t1->left;
    t1->left = t;
    t->height = max(height(t->left), height(t->right)) + 1;
    t1->height = max(height(t1->right), height(t)) + 1;
    t = t1;
}

template <class KEY, class OTHER>
void AvlTree<KEY, OTHER>::LR(AvlNode* &t)
{
    RR(t->left);
    LL(t);
}

template <class KEY, class OTHER>
void AvlTree<KEY, OTHER>::RL(AvlNode* &t)
{
    LL(t->right);
    RR(t);
}

template <class KEY, class OTHER>
bool AvlTree<KEY, OTHER>::remove(const KEY &x, AvlNode* &t)
{
    if(t == NULL) return true;
    if (x == t->data.key)                                       //删除根结点
    {
        if (t->left == NULL || t->right == NULL)
        {
            AvlNode *oldNode = t;
            t = (t->left != NULL) ? t->left : t->right;
            delete oldNode;
            return false;
        }
        else
        {
            AvlNode *tmp = t->right;
            while(tmp->left != NULL) tmp = tmp->left;
            t->data = tmp->data;
            if (remove(tmp->data.key, t->right)) return true;
            return adjust(t, 1);
        }
    }
    else if (x < t->data.key)                                   //在左子树上删除
    {
        if (remove(x, t->left)) return true;
        return adjust(t, 0);
    }
    else                                                        //在右子树上删除
    {
        if (remove(x, t->right)) return true;
        return adjust(t, 1);
    }
}

template <class KEY, class OTHER>
bool AvlTree<KEY, OTHER>::adjust(AvlNode* &t, int subTree)
{
    if (subTree)                           //1 在右子树上删除，使右子树变矮
    {
        if (height(t->left) - height(t->right) == 1) return true;
        if (height(t->right) == height(t->left)) {--t->height; return false;}
        if (height(t->left->right) > height(t->left->left)) {LR(t); return false;}
        LL(t);
        if (height(t->right) == height(t->left)) return false;
        else return true;
    }
    else                                   //在左子树删除
    {
        if (height(t->right) - height(t->left) == 1) return true;
        if (height(t->right) == height(t->left)) {--t->height; return false;}
        if (height(t->right->left) > height(t->right->right)) {RL(t); return false;}
        RR(t);
        if (height(t->right) == height(t->left)) return false;
        else return true;
    }
}

int main(){
    int n;
    cin>>n;
    AvlTree<int, string > avl;

    while(n--){
        int opt, x;
        cin>>opt>>x;
        SET<int ,string > X;
        X.key=x;
        switch (opt) {
            case 1:
                avl.insert(X);
                break;
            case 2:
                avl.remove(x);
                break;
            case 3: {
                vector<int> order = avl.InOrder();
                int i=0;
                while (i<order.size()&&order[i]<x) i++;
                cout<<i+1<<endl;
                break;
            }
            case 4:
            {
                vector<int> order = avl.InOrder();
                bool flag= false;
                if(order[0]>=x){
                    cout<<-1<<endl;
                    break;
                }
                for(int i=1;i<order.size();i++){
                    if(order[i]>=x){
                        flag= true;
                        cout<<order[i-1]<<endl;
                        break;
                    }
                }
                if(!flag) cout<<order[order.size()-1]<<endl;
                break;
            }
            case 5:
            {
                vector<int> order = avl.InOrder();
                bool flag= false;
                int n=order.size();
                if(order[n-1]<=x){
                    cout<<-1<<endl;
                    break;
                }
                for(int i=n-2;i>=0;i--){
                    if(order[i]<=x){
                        flag= true;
                        cout<<order[i+1]<<endl;
                        break;
                    }
                }
                if(!flag) cout<<order[0]<<endl;
                break;
            }
        }

    }
    return 0;
}
