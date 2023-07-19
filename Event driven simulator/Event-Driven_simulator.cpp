#include <iostream>
#include<queue>
#include<time.h>
#include<vector>

using namespace std;

class Event{
    public:
    int v;
    double t;
    
    Event(int v1, double t1){
        v=v1;
        t=t1;
    }
};

class Comparator{
    public:
    bool operator()(const Event& lhs, const Event& rhs){
        return(lhs.t==rhs.t)?(lhs.v>rhs.v):(lhs.t>rhs.t);
    }
};

priority_queue<Event, vector<Event>, Comparator>meq;
time_t start;

Event processEvent(){
    time_t end;
    time(&end);
    Event top= meq.top();
    double now = difftime(end,start);
    Event e = Event(((rand()%250)+10),now+top.v);
    return e;
}

int main()
{
    time(&start);
    
    for(int i=0;i<20;i++){
        time_t end;
        time(&end);
        int v=((rand()%250)+10);
        meq.push(Event(v,difftime(end,start)));
    }
    
    int i=0;
    while(i<80){
        Event e = processEvent();
        meq.push(e);
        i++;
    }
    
    i=1;
    while(!meq.empty()){
        Event e = meq.top();
        cout<<i<<" "<<"t= "<<e.t<<"v= "<<e.v<<"\n";
        meq.pop();
        i++;
    }

    return 0;
}
