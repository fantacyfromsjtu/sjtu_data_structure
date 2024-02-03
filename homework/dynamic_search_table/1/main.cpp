
#include<bits/stdc++.h>
using namespace std;

class Node
{
public:
    int key;
    Node *left, *right;
};

// 生成二叉树
Node *newNode(int item)
{
    Node *temp = new Node;
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}

// 递归调用以找到第k大的元素
void kthLargestUtil(Node *root, int k, int &c)
{
    // 在这里填补
    if(root->right) kthLargestUtil(root->right,k,c);
    c++;
    if(k==c){
        cout<<root->key;
        return;
    }
    if(root->left) kthLargestUtil(root->left,k,c);
}

// 调用以找到第k大的元素
void kthLargest(Node *root, int k)
{

    int c = 0;
    kthLargestUtil(root, k, c);
}

// 在树中插入元素
Node* insert(Node* node, int key)
{
    if (node == NULL) return newNode(key);

    if (key < node->key)
        node->left  = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);

    return node;
}

int main()
{
    int num = 0;
    int k_th = 0;
    int root_value = 0;
    cin>>num;
    cin>>k_th;
    cin>>root_value;
    Node *root = NULL;
    root = insert(root, root_value);
    for (int node_id = 0; node_id<num-1;++node_id) {
        int node_temp_val = 0;
        cin>>node_temp_val;
        insert(root, node_temp_val);
    }
    kthLargest(root, k_th);
    return 0;
}