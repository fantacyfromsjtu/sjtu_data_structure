#include <iostream>
#include <vector>
#include <queue>
using namespace std;
const int MXN = 100005;

struct Node{
    Node *left;
    Node *right;
    int data;
    Node():left(nullptr),right(nullptr){}
    Node(int num,Node *L= nullptr,Node *R= nullptr){
        data=num;
        left=L;
        right=R;
    }
    ~Node(){}
};

int main() {
    int n;
    cin >> n;
    int leftnd[MXN],rightnd[MXN];
    for(int i=0;i<n;i++){
        cin>>leftnd[i]>>rightnd[i];
    }
    vector<Node*> nodes;
    for(int i=0;i<n;i++){
        Node *p=new Node(i+1);
        nodes.push_back(p);
    }
    for(int i=0;i<n;i++){
        Node *p=nodes[i];
        if(leftnd[i]) p->left=nodes[leftnd[i]-1];
        if(rightnd[i]) p->right=nodes[rightnd[i]-1];
    }
    queue<Node*> que;
    Node *root=nodes[n-1];
    que.emplace(root);
    while (!que.empty()){
        Node *tmp=que.front();
        que.pop();
        if(tmp){
            que.push(tmp->left);
            que.push(tmp->right);
        }
        else{
            while(!que.empty()){
                tmp=que.front();
                que.pop();
                if(tmp){ cout<<'N';return 0;}
            }
        }
    }
    cout<<'Y';
    return 0;
}
