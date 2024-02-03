#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;
class priorityQueue{
private:
    struct node
    {
        int order;
        float time;
        node(int num,float value){
            order=num;
            time=value;
        }
    };
    vector<node> queue;
    static bool greaterThan(node a,node b){
        return a.time>b.time;
    }
public:
    priorityQueue(int size){
        queue.reserve(size);
    }
    void insert(int order, float time) {
        node cur(order, time);
        queue.push_back(cur);
        int cursize = queue.size()-1;
        int hole = cursize;
        for (; hole > 1 && greaterThan(queue[hole / 2], cur); hole /= 2) {
            queue[hole] = queue[hole / 2];
        }
        queue[hole] = cur;
    }
    int deQueue() {
        int top = queue[1].order;
        int cursize = queue.size();
        queue[1] = queue[cursize - 1];
        queue.erase(queue.begin()+1);
        percolatedown(1);
        return top;
    }

    void percolatedown(int hole){
        int child;
        node tmp=queue[hole];
        for(;hole*2<=queue.size();hole=child){
            child=hole*2;
            if(child!=queue.size()&& greaterThan(queue[child],queue[child+1])) child++;
            if (greaterThan(tmp,queue[child]))queue[hole]=queue[child];
            else break;
        }
        queue[hole]=tmp;
    }
    bool isEmpty(){
        return queue.empty();
    }
};
int main(){
    int numOfEvent;
    cin>>numOfEvent;
    priorityQueue pq(numOfEvent+1);
    pq.insert(0,0);
    for(int i=1;i<=numOfEvent;++i){
        float cur;
        cin>>cur;
        //implement
        pq.insert(i,cur);
        //

    }
    for(int i=0;i<numOfEvent;++i){
        //implement
        cout<<pq.deQueue()<<' ';
        //
    }
    return 0;
}