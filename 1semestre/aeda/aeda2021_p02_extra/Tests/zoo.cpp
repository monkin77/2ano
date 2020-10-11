#include "zoo.h"
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <fstream>

using namespace std;

unsigned Zoo::numAnimals() const {
    return animals.size();
}

unsigned Zoo::numVeterinarians() const {
    return veterinarians.size();
}

void Zoo::addAnimal(Animal *a1) {
    this->animals.push_back(a1);
}

string Zoo::getInfo() const {
    string info = "";
    for(int i = 0; i < this->animals.size(); i++){
        info += this->animals[i]->getInfo() + "\n";
    }
    return info;
}

bool Zoo::isYoung(string nameA) {
    for(int i = 0; i < this->animals.size(); i++){
        if( (*(this->animals[i])).getName() == nameA  ){
            if( (*(this->animals[i])).isYoung() ){
                return true;
            }
        }
    }
    return false;
}

void Zoo::allocateVeterinarians(istream &isV) {
    ifstream fin;
    fin.open("vets.txt");
    string name, codOrder;
    while(getline(fin, name)){
        getline(fin, codOrder );
        Veterinary vet(name, stoi(codOrder));    //stoi converts a string to int
        this->veterinarians.push_back(&vet);
    }

    if(this->veterinarians.size() > 0){
        int vetIdx = 0;
        for(int i = 0; i < this->animals.size(); i++){
            (*(this->animals[i])).setVeterinary(this->veterinarians[vetIdx]);
            if(vetIdx + 1 >= this->veterinarians.size())
                vetIdx = 0;
            else
                vetIdx++;
        }
    }

    fin.close();
}