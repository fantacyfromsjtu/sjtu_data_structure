//
// Created by Lenovo on 2023/12/18.
//

#ifndef GRAPH_GRATH_H
#define GRAPH_GRATH_H
#include <iostream>
#include <queue>

using namespace std;
//图的抽象类
template <class TypeOfVer, class TypeOfEdge>
class graph{
public:
    virtual void insert(TypeOfVer x, TypeOfVer y,TypeOfEdge w)=0;
    virtual void remove(TypeOfVer x, TypeOfVer y)=0;
    virtual bool exist(TypeOfVer x,TypeOfVer y)const=0;
    int numOfVer()const{
        return Vers;
    }
    int numOfEdge()const{
        return Edges;
    }
protected:
    int Vers;//节点数
    int Edges;//边数
};

//基于邻接矩阵的图类定义
template <class TypeOfVer, class TypeOfEdge>
class adjMatrixGraph:public graph<TypeOfVer,TypeOfEdge>{
public:
    adjMatrixGraph(int vSize,const TypeOfVer d[],const TypeOfEdge noEdgeFlag);
    void insert(TypeOfVer x, TypeOfVer y,TypeOfEdge w);
    void remove(TypeOfVer x, TypeOfVer y);
    bool exist(TypeOfVer x, TypeOfVer y)const;
    ~adjMatrixGraph();
private:
    TypeOfEdge **edge;//邻接矩阵
    TypeOfVer *ver;//节点值
    TypeOfEdge noEdge;
    int find(TypeOfVer v) const{
        for(int i=0;i<this->Vers;++i){
            if (ver[i]==v) return i;
        }
        return -1;
    }
};

template<class TypeOfVer, class TypeOfEdge>
adjMatrixGraph<TypeOfVer, TypeOfEdge>::adjMatrixGraph(int vSize,
       const TypeOfVer *d, const TypeOfEdge noEdgeFlag) {
    this->Vers=vSize;
    this->Edges =0;
    noEdge=noEdgeFlag;

    //节点数组初始化
    ver=new TypeOfVer[vSize];
    for (int k = 0; k <vSize ; ++k) {
        ver[k]=d[k];
    }
    //邻接矩阵初始化
    edge=new TypeOfEdge * [vSize];
    for (int i=0;i<vSize;++i) {
        edge[i]=new TypeOfEdge[vSize];
        for(int j=0;j<vSize;j++){
            edge[i][j]=noEdge;
        }
        edge[i][i]=0;
    }
}

template<class TypeOfVer, class TypeOfEdge>
void adjMatrixGraph<TypeOfVer, TypeOfEdge>::insert(TypeOfVer x, TypeOfVer y, TypeOfEdge w) {
    int i= find(x),j= find(y);
    if(i==-1||j==-1) return;
    edge[i][j]=w;
    ++this->Edges;
}

template<class TypeOfVer, class TypeOfEdge>
void adjMatrixGraph<TypeOfVer, TypeOfEdge>::remove(TypeOfVer x, TypeOfVer y) {
    int i= find(x),j= find(y);
    if(i==-1||j==-1) return;
    edge[i][j]=noEdge;
    --this->Edges;
}

template<class TypeOfVer, class TypeOfEdge>
bool adjMatrixGraph<TypeOfVer, TypeOfEdge>::exist(TypeOfVer x, TypeOfVer y) const {
    int i= find(x),j= find(y);
    if(i==-1||j==-1) return false;
    if(edge[i][j]==noEdge) return false;
    else return true;
}

template<class TypeOfVer, class TypeOfEdge>
adjMatrixGraph<TypeOfVer, TypeOfEdge>::~adjMatrixGraph() {
    delete []ver;
    for(int i=0;i< this->Vers;i++){
        delete []edge[i];//释放每一行
    }
    delete []edge; //释放指向每一行首地址的指针数组
}

//邻接表类
template<class TypeOfVer, class TypeOfEdge>
class adjListGraph:public graph<TypeOfVer,TypeOfEdge>
{
public:
    adjListGraph(int vSize,const TypeOfVer d[]);
    void insert(TypeOfVer x, TypeOfVer y,TypeOfEdge w);
    void remove(TypeOfVer x, TypeOfVer y);
    bool exist(TypeOfVer x, TypeOfVer y)const;
    void dfs()const;
    void bfs()const;
    void topSort()const;//拓扑排序
    ~adjListGraph();
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
    int find(TypeOfVer v)const
    {
        for(int i=0;i<this->Vers;i++){
            if(verList[i].ver==v) return i;
        }
        return -1;
    }
    void dfs(int start,bool visited[])const;
};


//拓扑排序
template<class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::topSort() const {
    queue<int> q;
    edgeNode *p;
    int cur;
    int *inDegree = new int [this->Vers];
    for(int i=0;i<this->Vers;i++){
        inDegree[i]=0;
    }
    for(int i=0;i< this->Vers;i++){
        for(p=verList[i].head;p;p=p->next){
            ++inDegree[p->end];
        }
    }//计算每个节点的入度
    for(int i=0;i<this->Vers;i++){
        if(inDegree[i]==0){
            q.emplace(i);
        }
    }
    while (!q.empty()){
        cur=q.front();
        q.pop();
        cout<<verList[cur].ver<<'\t';
        for(p=verList[cur].head;p;p=p->next){
            --inDegree[p->end];
            if(inDegree[p->end]==0) q.emplace(p->end);
        }
    }
    cout<<endl;
}


template<class TypeOfVer, class TypeOfEdge>
adjListGraph<TypeOfVer, TypeOfEdge>::adjListGraph(int vSize, const TypeOfVer *d) {
    this->Vers=vSize;
    this->Edges=0;
    verList= new verNode[vSize];
    for(int i=0;i<this->Vers;++i) verList[i].ver=d[i];
}

template<class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::insert(TypeOfVer x, TypeOfVer y, TypeOfEdge w) {
    int u=find(x),v= find(y);
    verList[u].head=new edgeNode(v,w,verList[u].head);
    ++this->Edges;
}

template<class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::remove(TypeOfVer x, TypeOfVer y) {
    int u=find(x),v=find(y);
    edgeNode *p=verList[u].head,*q;
    if(!p) return;
    //区分第一个节点就是被删除的边
    if(p->end==v){
        verList[u].head=p->next;
        delete p;
        --this->Edges;
        return;
    }
    while(p->next&&p->next->end!=v) p=p->next;
    if(p->next){
        q=p->next;
        p->next=q->next;
        delete q;
        --this->Edges;
    }
}

template<class TypeOfVer, class TypeOfEdge>
bool adjListGraph<TypeOfVer, TypeOfEdge>::exist(TypeOfVer x, TypeOfVer y) const {
    int u= find(x),v= find(y);
    edgeNode *p=verList[u].head;
    while (p){
        if(p->end==v) return true;
        p=p->next;
    }
    return false;
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

//深度优先搜索
template<class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::dfs() const {
    bool *visited= new bool [this->Vers];
    for(int i=0;i<this->Vers;i++) visited[i]= false;
    for(int i=0;i<this->Vers;i++){
        if(visited[i]) continue;
        dfs(i,visited);
        cout<<endl;
    }
}

template<class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::dfs(int start,bool visited[]) const{
    edgeNode  *p=verList[start].head;
    cout<<verList[start].ver<<'\t';  //访问结点
    visited[start]= true;

    while (p){
        if(visited[p->end]== false) dfs(p->end,visited);
        p=p->next;
    }//精华
}

template<class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::bfs() const {
    bool *visited= new bool [this->Vers];
    for(int i=0;i<this->Vers;i++) visited[i]= false;
    int cur;
    queue<int> q;
    edgeNode *p;
    for(int i=0;i<this->Vers;i++){
        if(visited[i]) continue;
        q.emplace(i);
        while (!q.empty()) {
            cur=q.front();
            q.pop();
            if(visited[cur]) continue;
            visited[cur]= true;
            cout<<verList[cur].ver<<" ";
            p=verList[cur].head;
            while (p){
                if(!visited[p->end]) q.emplace(p->end);
                p=p->next;
            }
        }
        cout<<endl;
    }
}


#endif //GRAPH_GRATH_H
