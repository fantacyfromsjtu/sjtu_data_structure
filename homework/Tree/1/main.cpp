#include <iostream>
using namespace std;

template <class elemType>
class hfTree{
private:
    struct  Node
    {
        elemType data;  //结点值
        int weight;  //结点的权值
        int parent, left, right;
    };

    Node *elem;
    int length;
public:
    //哈夫曼编码类
    struct hfCode
    {
        elemType data;
        string code;
    };
    hfTree(const elemType *x,
           const int *w, int size);
    void getCode(hfCode result[]);
    ~hfTree() {delete [] elem;}
};

template <class elemType>
hfTree<elemType>:: hfTree(const elemType *v, const int *w, int size)
//v:编码数据 w:权值 size:总结点数
{
    const int MAX_INT = 32767;
    int min1, min2;  //最小树、次最小树的权值
    int x, y;  //最小树、次最小树的下标
    length = 2 * size;  //置初值
    elem = new Node[length];
    for (int i = size; i < length; ++i)
    {
        elem[i].weight = w[i - size];
        elem[i].data = v[i - size];
        elem[i].parent = elem[i].left = elem[i].right = 0;
    }
    // 构造新的二叉树
    for (int i = size - 1; i > 0; --i)  //从下标最大的内部节点开始，到根结点
    {
        min1 = min2 = MAX_INT; x = y = 0;
        for (int j = i + 1; j < length; ++j) //找到最小的两个
        {
            if (elem[j].parent == 0)
            {
                if (elem[j].weight < min1)
                {
                    min2 = min1; min1 = elem[j].weight;
                    x = y; y = j;
                }
                else if (elem[j].weight < min2)
                {
                    min2 = elem[j].weight; x = j;
                }
            }  //end if
        }  //end for inner
        elem[i].weight = min1 + min2; //合并最小的两个
        elem[i].left = x; elem[i].right = y; elem[i].parent = 0;
        elem[x].parent = i; elem[y].parent = i;
    }  //end for outer
}  //end

template <class elemType>
void hfTree<elemType>:: getCode(hfCode result[])  //结果存储于result中
{
    int size = length / 2;
    int p,s;  //s是追溯过程中正在处理的结点，p是s的父结点下标
    for (int i = size; i < length; ++i)
    {
        result[i - size].data = elem[i].data; // 对每个待编码的符号
        result[i - size].code = string("");
        p = elem[i].parent; s = i;
        while (p)
        { // while（p!=0）
            if (elem[p].left == s)  //是父结点的左孩子编码末尾加0
                result[i - size].code = "0" + result[i -size].code;
            else
                result[i - size].code = "1" + result[i - size].code;  //加1
            s = p; p = elem[p].parent; //向上一层
        }
    }
}
int main(){
    int a[100005];
    int n;
    cin>>n;
    int *v=new int[114514];
    for(int i=0;i<n;i++) v[i]=i;
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    if(n==1||n==0) {
        cout<<n;
        return 0;
    }
    hfTree<int> tree(v,a,n);
    hfTree<int>::hfCode result[n];
    tree.getCode(result);
    int length=0;
    for(int i=0;i<n;i++){
        length+=a[i]*result[i].code.length();
    }
    cout<<length;
    return 0;
}