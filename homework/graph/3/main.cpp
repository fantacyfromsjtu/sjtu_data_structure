#include <iostream>
#include <queue>
#include <vector>
using namespace std;
class graph{
private:
    struct edgeNode{//邻接表中存储边的结点类
        int end;
        edgeNode *next;
        edgeNode(int e,edgeNode *n= nullptr){
            end=e;
            next=n;
        }
    };
    struct verNode{
        edgeNode *head; //对应的单链表头指针
        verNode(edgeNode *h= nullptr){
            head=h;
        }
    };
    vector<verNode *> verlist;
public:
    int numofver;
    int numofegde;
    vector<int> res;
    graph(int size){
        numofver=size;
        numofegde=0;
        for (int i = 0; i < size; i++) {
            verlist.push_back(new verNode(new edgeNode(-1)));
        }
    }
    ~graph(){}
    void insert(int x,int y){
        verlist[x]->head=new edgeNode(y,verlist[x]->head);
        ++numofegde;
    }
    void topSort(){
        vector<int> inDegree(numofver,0);
        for(int i=0;i<numofver;i++){
            for(edgeNode *p=verlist[i]->head;p;p=p->next){
                ++inDegree[p->end];
            }
        }
        priority_queue<int,vector<int>,greater<>> q;
        for(int i=0;i<numofver;i++){
            if(inDegree[i]==0) q.emplace(i);
        }
        while (!q.empty()){
            int cur=q.top();
            q.pop();
            res.push_back(cur+1);
            for(edgeNode *p=verlist[cur]->head;p;p=p->next){
                --inDegree[p->end];
                if(!inDegree[p->end]) q.emplace(p->end);
            }
        }
    }
};
int main() {
    int n,m;
    cin>>n>>m;
    graph G(n);
    for(int i=0;i<m;i++){
        int u,v;
        cin>>u>>v;
        G.insert(u-1,v-1);
    }
    G.topSort();
    for(int i=0;i<G.numofver-1;i++) cout<<G.res[i]<<' ';
    cout<<G.res[G.numofver-1];
    return 0;
}
