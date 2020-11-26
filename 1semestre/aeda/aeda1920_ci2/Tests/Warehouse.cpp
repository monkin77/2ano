#include "Warehouse.h"
#include <algorithm>

Warehouse::Warehouse()  {
}

queue<ThinTallBox> Warehouse::getBoxes() {
	return boxes;
}

queue<Object> Warehouse::getObjects() {
    return objects;
}

void Warehouse::setBoxes(queue<ThinTallBox> q) {
    while (!q.empty()) {
        boxes.push(q.front());
        q.pop();
    }
}

void Warehouse::addObject(Object o1) {
    objects.push(o1);
}


int Warehouse::InsertObjectsInQueue(vector <Object> obj){
    int maxIdx;
    int maxObj;
    /*
    for(int i = 0; i < obj.size(); i++){        // sort objects in descending order
        maxIdx = i;
        maxObj = obj[i].getSize();
        for(int j = i; j < obj.size(); j++){
            if(  obj[j].getSize() > maxObj){
                maxIdx = j, maxObj = obj[j].getSize();
            }
        }
        if(maxIdx != i){
            Object aux = obj[i];
            obj[i] = obj[maxIdx], obj[maxIdx] = aux;
        }
    }
     */
    sort(obj.begin(), obj.end(), [](Object obj1, Object obj2){
        return obj1.getSize() >= obj2.getSize();
    });
    for(int i = 0; i < obj.size(); i++)
        this->addObject(obj[i]);
    return obj.size();
}

Object Warehouse::RemoveObjectQueue(int maxSize){
     Object obj;
     queue<Object> aux;
     bool hasFound = false;
     while( (!this->objects.empty()) ){
         if( (this->objects.front().getSize() <= maxSize) && (!hasFound) ){
             obj = this->objects.front();
             hasFound = true;
         }
         else
             aux.push(this->objects.front());
         this->objects.pop();
     }
    while(!aux.empty()){
        this->objects.push(aux.front());
        aux.pop();
    }
     if(!hasFound)
         obj = Object("dummy", maxSize);
    return obj;
}

int Warehouse::addPackOfBoxes(vector <ThinTallBox> boV) {
    for(int i = 0; i < boV.size(); i++)
        boxes.push(boV[i]);
    return this->boxes.size();
}


vector<ThinTallBox> Warehouse::DailyProcessBoxes(){
    vector<ThinTallBox> res;
    queue<ThinTallBox> auxBoxes;
    queue<Object> auxObjects;
    int no_it = this->boxes.size();
    for(int i = 0; i < no_it; i++){
        ThinTallBox currBox = this->boxes.front();
        if( currBox.full() ){           // se a caixa estiver cheia, eliminar
            res.push_back(currBox);
        }
        else if(currBox.getDays() == 0){            // se a validade terminar, adicionar objeto e eliminar
            Object newObject = RemoveObjectQueue(currBox.getCapacity() - currBox.getContentSize());
            currBox.insert(newObject);
            res.push_back(currBox);
        }
        else{                     // Caso ainda esteja válida, adicionar objeto e colocar no fim da fila
            Object newObject = RemoveObjectQueue(currBox.getCapacity() - currBox.getContentSize());
            currBox.insert(newObject);
            currBox.setDaysToSend(currBox.getDays()-1);
            this->boxes.push(currBox);
        }
        this->boxes.pop();
    }
    return res;
}

