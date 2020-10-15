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
        Veterinary* v = new Veterinary(name, stoi(codOrder));    //stoi converts a string to int
        this->veterinarians.push_back(v);
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

bool Zoo::removeVeterinary(string nameV) {
    int idx = -1;
    for(int i = 0; i < this->veterinarians.size(); i++){
        if( (*(this->veterinarians[i])).getName() == nameV ){
            idx = i;
            break;
        }
    }
    if(idx == -1)
        return false;

    this->veterinarians.erase(this->veterinarians.begin() + idx);
    for(int j = 0; j < this->animals.size(); j++){
        if( (*(this->animals[j])).getVeterinary()->getName() == nameV ){
            if(this->veterinarians.size() > idx)
                (*(this->animals[j])).setVeterinary(this->veterinarians[idx]);
        }
    }

    return true;
}

bool Zoo::operator<(Zoo &zoo2) const {
    int age1, age2;
    for(int i = 0; i < this->animals.size(); i++){
        age1 += (*(this->animals[i])).getAge();
    }
    for(int j = 0; j < zoo2.animals.size(); j++){
        age2 += (*(zoo2.animals[j])).getAge();
    }
    if(age1 < age2)
        return true;
}
