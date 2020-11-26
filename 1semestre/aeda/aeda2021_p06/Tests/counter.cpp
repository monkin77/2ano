#include <queue>
#include <cstdlib>
#include "counter.h"
#include "exceptions.h"
#include <random>

using namespace std;

//TODO
Client::Client() {
    this->numGifts = rand() % 5 + 1 ;
}

//TODO
unsigned Client::getNumGifts() const {
    return this->numGifts;
}


//TODO
Counter::Counter(unsigned wt): wrappingTime(wt) {
    this->actualTime = 0;
    this->nextEnter = rand() % 20 + 1;
    this->nextLeave = 0;
    this->numAttendedClients = 0;
}

//TODO
unsigned Counter::getActualTime() const {
    return this->actualTime;
}

//TODO
unsigned Counter::getNextEnter() const {
    return this->nextEnter;
}

//TODO
unsigned Counter::getNumAttendedClients() const {
    return this->numAttendedClients;
}

//TODO
unsigned Counter::getWrappingTime() const {
    return this->wrappingTime;
}

//TODO
unsigned Counter::getNextLeave() const {
    return this->nextLeave;
}

//TODO
Client & Counter::getNextClient() {
    if(this->clients.empty()){
        throw EmptyQueue();
    }
    Client *cl = new Client();
    *cl = this->clients.front();
    return *cl;
}

//TODO
void Counter::enter(){
    Client cl;
    this->clients.push(cl);
    this->nextEnter = rand() % 20 + 1;
    if(this->clients.size() == 1){
        this->nextLeave = (this->actualTime + cl.getNumGifts()) * this->wrappingTime;
    }
    cout << "Actual time: " << this->actualTime << " New customer arrived with " << cl.getNumGifts() << " gifts" << endl;
}

//TODO
void Counter::leave(){
    Client cl;
    try{
        cl = this->getNextClient();
    }
    catch(EmptyQueue& eq){
        cout << eq.getMsg() << endl;
    }

    cout << "Actual time: " << this->actualTime << " Customer left with " << cl.getNumGifts() << " gifts" << endl;
    this->clients.pop();
    this->nextLeave = (this->actualTime + this->clients.front().getNumGifts()) * this->wrappingTime;   // new client is on the back
}

//TODO
void Counter::nextEvent(){
    if(this->nextEnter <= this->nextLeave){
        this->enter();
        this->actualTime += this->nextEnter;
    }
    else{
        this->leave();
        this->actualTime += this->nextLeave;
    }
}


//TODO

ostream & operator << (ostream & out, const Counter & c2){
    out << c2.getNumAttendedClients() << " " << c2.clients.size() << endl;
    return out;
}


