#include<iostream>
#include<thread>
#include<iostream>
using namespace std;

const int Nothreads=5;

class bakkeryLock{
int Nthreads;
bool *chos;
int * Ticket;


public:

bakkeryLock(int n){

Nthreads=n;
chos=new bool[n];
Ticket = new int[n];


for(int i =0;i<n;i++){

chos[i]=false;
Ticket[i]=0;

}
}

void unlocK(int id){

Ticket[id]=0;

}

void lock(int id){
chos[id]=true;
int m=0;

for(int i=0;i<Nthreads;i++){
if(Ticket[i]>m){
m=Ticket[i];
}
}

Ticket[id]=m+1;

chos[id]=false;


for(int i=0;i<Nthreads;i++){
while(chos[i]);
while((Ticket[i]!=0)&&((Ticket[i]<Ticket[id])||((Ticket[i]==Ticket[id])&&(i<id))));

}
}



};


bakkeryLock lock(Nothreads);
int shared_data = 0;

void thread_func(int thread_id) {
    for (int i = 0; i < 100; i++) {
        lock.lock(thread_id);
        cout<<shared_data<<endl;

        shared_data++;
        lock.unlocK(thread_id);
    }
}


int main() {
    std::thread threads[Nothreads];
    for (int i = 0; i < Nothreads; i++) {
        threads[i] = std::thread(thread_func, i);
    }

    for (int i = 0; i < Nothreads; i++) {
        threads[i].join();
    }

    std::cout << "Shared data: " << shared_data << std::endl;

    return 0;
}
