#include <iostream>
using namespace std;
//ͼ�ĳ�����
template <class TypeOfVer, class TypeOfEdge>
class graph{
public:
    virtual void insert(TypeOfVer x, TypeOfVer y,TypeOfEdge w)=0;
protected:
    int Vers;//�ڵ���
    int Edges;//����
};

//�����ڽӾ����ͼ�ඨ��
template <class TypeOfVer, class TypeOfEdge>
class adjMatrixGraph:public graph<TypeOfVer,TypeOfEdge>{
public:
    adjMatrixGraph(int vSize,const TypeOfVer d[],const TypeOfEdge noEdgeFlag);
    void insert(TypeOfVer x, TypeOfVer y,TypeOfEdge w);
    void dfs(int start,bool visited[])const;
    ~adjMatrixGraph();
private:
    TypeOfEdge **edge;//�ڽӾ���
    TypeOfVer *ver;//�ڵ�ֵ
    TypeOfEdge noEdge;
    int find(TypeOfVer v) const{
        for(int i=0;i<this->Vers;++i){
            if (ver[i]==v) return i;
        }
        return -1;
    }
};

template<class TypeOfVer, class TypeOfEdge>
void adjMatrixGraph<TypeOfVer, TypeOfEdge>::dfs(int start, bool *visited) const {
    visited[start]= true;
    for(int j=0;j<this->Vers;j++){
        if(edge[start][j]&&!visited[j]){
            dfs(j,visited);
        }
    }
}


template<class TypeOfVer, class TypeOfEdge>
adjMatrixGraph<TypeOfVer, TypeOfEdge>::adjMatrixGraph(int vSize,
                                                      const TypeOfVer *d, const TypeOfEdge noEdgeFlag) {
    this->Vers=vSize;
    this->Edges =0;
    noEdge=noEdgeFlag;

    //�ڵ������ʼ��
    ver=new TypeOfVer[vSize];
    for (int k = 0; k <vSize ; ++k) {
        ver[k]=d[k];
    }
    //�ڽӾ����ʼ��
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
    edge[j][i]=w;
    ++this->Edges;
}



template<class TypeOfVer, class TypeOfEdge>
adjMatrixGraph<TypeOfVer, TypeOfEdge>::~adjMatrixGraph() {
    delete []ver;
    for(int i=0;i< this->Vers;i++){
        delete []edge[i];//�ͷ�ÿһ��
    }
    delete []edge; //�ͷ�ָ��ÿһ���׵�ַ��ָ������
}


int main() {
    int n,m;
    cin>>n>>m;
    int *d=new int[n];
    for(int i=0;i<n;i++) d[i]=i;
    adjMatrixGraph<int,int> G(n,d,0);
    for(int i=0;i<m;i++){
        int u,v;
        cin>>u>>v;
        G.insert(u,v,1);
    }
    int count=0;
    bool *visited=new bool[n];
    for(int i=0;i<n;i++) visited[i]= false;
    for(int i=0;i<n;i++){
        if(!visited[i]){
            G.dfs(i,visited);
            count++;
        }
    }
    cout<<count;
    return 0;
}
