#include <iostream>
#include <string>

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

//基于线性探测法的闭散列表的实现
template <class KEY, class OTHER>
class closeHashTable: public dynamicSearchTable<KEY,OTHER>{
private:
    struct node{
        SET<KEY,OTHER> data;
        int state;//0-empty,1-active,2-deleted
        node(){state=0;}
    };
    node *array;
    int size;
    int (*key) (const KEY &x);
    static int defaultKey(const KEY & x){
        int res=0;
        for(auto m:x){
            res+=m;
        }
        return res;
    }
public:
    closeHashTable(int length = 101,int (*f)(const KEY &x)=defaultKey);
    ~closeHashTable(){ delete []array;}
    SET<KEY,OTHER> *find(const KEY &x) const;
    void insert(const SET<KEY,OTHER> &x);
    void remove(const KEY &x);
};

template<class KEY, class OTHER>
closeHashTable<KEY, OTHER>::closeHashTable(int length, int (*f)(const KEY &)) {
    size = length;
    array=new node [size];
    key=f;
}

template<class KEY, class OTHER>
SET<KEY, OTHER> *closeHashTable<KEY, OTHER>::find(const KEY &x) const {
    int initPos,pos;

    initPos=pos=key(x)%size;
    do{
        if(array[pos].state==0) return nullptr;
        if(array[pos].state==1&&array[pos].data.key==x) return (SET<KEY,OTHER>*) &array[pos];
        pos=(pos+1)%size;
    } while (pos!=initPos);
}

template<class KEY, class OTHER>
void closeHashTable<KEY, OTHER>::insert(const SET<KEY, OTHER> &x) {
    int initPos,pos;

    initPos=pos=key(x.key)%size;
    do{
        if(array[pos].state!=1){
            array[pos].data=x;
            array[pos].state=1;
            return;
        }
        pos=(pos+1)%size;
    } while (pos!=initPos);
}

template<class KEY, class OTHER>
void closeHashTable<KEY, OTHER>::remove(const KEY &x) {
    int initPos,pos;

    initPos=pos=key(x)%size;
    do{
        if(array[pos].state==0) return;
        if(array[pos].state==1&&array[pos].data.key==x){
            array[pos].state=2;
            return;
        }
        pos=(pos+1)%size;
    } while (pos!=initPos);
}

using namespace std;
int main() {
    int n;
    int t;
    cin >> n >> t;
    closeHashTable<string,string> A;
    for(int i=0;i<n;i++){
        string tmp;
        cin>>tmp;
        SET<string ,string > S;
        S.key=tmp;
        A.insert(S);
    }
    for(int i=1;i<=t;i++){
        string test;
        cin>>test;

        if(A.find(test)) cout<<1<<endl;
        else cout<<0<<endl;
    }
    return 0;
}
