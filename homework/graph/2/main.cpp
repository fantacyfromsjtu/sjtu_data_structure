#include <iostream>
#include <iomanip>
#include <queue>
using namespace std;
template <class TypeOfVer, class TypeOfEdge>
class graph{
public:
    virtual void insert(TypeOfVer x, TypeOfVer y,TypeOfEdge w)=0;
protected:
    int Vers;//节点数
    int Edges;//边数
};
template<class TypeOfVer, class TypeOfEdge>
class adjListGraph:public graph<TypeOfVer,TypeOfEdge>
{
public:
    adjListGraph(int vSize,const TypeOfVer d[]);
    void insert(TypeOfVer x, TypeOfVer y,TypeOfEdge w);
    ~adjListGraph();
    void findnext(bool visited[],int num);
private:
    struct edgeNode{//邻接表中存储边的结点类
        int end;
        TypeOfEdge weight;// 权值
        edgeNode *next;
        edgeNode(int e,TypeOfEdge w,edgeNode *n= nullptr){
            end=e;
            weight=w;
            next=n;
        }
    };

    struct verNode{
        TypeOfVer ver;//顶点值
        edgeNode *head; //对应的单链表头指针
        verNode(edgeNode *h= nullptr){
            head=h;
        }
    };

    verNode *verList;
};

template<class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::findnext(bool visited[], int num) {
    queue<int> q;
    int distance[200]; // 记录节点到起始节点的距离
    for (int i = 0; i < this->Vers; ++i) {
        visited[i] = false;
        distance[i] = -1; // 初始化距离为-1表示尚未访问到
    }

    visited[num] = true;
    distance[num] = 0;
    q.push(num);

    while (!q.empty()) {
        int curr = q.front();
        q.pop();

        if (distance[curr] == 6) {
            break; // 距离超过6，跳出循环
        }

        edgeNode* p = verList[curr].head;
        while (p != nullptr) {
            int neighbor = p->end;
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                distance[neighbor] = distance[curr] + 1;
                q.push(neighbor);
            }
            p = p->next;
        }
    }
}


template<class TypeOfVer, class TypeOfEdge>
adjListGraph<TypeOfVer, TypeOfEdge>::adjListGraph(int vSize, const TypeOfVer *d) {
    this->Vers=vSize;
    this->Edges=0;
    verList= new verNode[vSize];
    for(int i=0;i<this->Vers;++i) verList[i].ver=d[i];
}

template<class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::insert(TypeOfVer u, TypeOfVer v, TypeOfEdge w) {
    verList[u].head=new edgeNode(v,w,verList[u].head);
    ++this->Edges;
}


template<class TypeOfVer, class TypeOfEdge>
adjListGraph<TypeOfVer, TypeOfEdge>::~adjListGraph() {
    edgeNode *p;
    for(int i=0;i<this->Vers;i++){
        while ((p=verList[i].head)!= nullptr){
            verList[i].head=p->next;
            delete p;
        }
    }
    delete []verList;
}




int main() {
    int n;//节点数
    int m;//边数
    cin>>n>>m;
    int d[200];
    for(int i=0;i<n;i++) d[i]=i;
    adjListGraph<int,int> G(n,d);
    for(int i=1;i<=m;i++){
        int x,y;
        cin>>x>>y;
        G.insert(x-1,y-1,1);
        G.insert(y-1,x-1,1);
    }
    for(int i=0;i<n;i++) {
        bool visited[200];
        for (int k = 0;k < n; k++) visited[k] = false;
        G.findnext(visited,i);
        int meet=0;
        for(int k=0;k<n;k++){
            if(visited[k]) meet++;
        }
        double rate= meet*100.0/n;
        cout<<i+1<<": "<<fixed<<setprecision(2)<<rate<<"%"<<endl;
    }
    return 0;
}
