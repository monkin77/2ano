#include "animal.h"
#include <sstream>
#include <iostream>

using namespace std;

string Animal::getName() const {
	return name;
}

int Animal::getAge() const {
    return age;
}

void Animal::setVeterinary(Veterinary *vet) {
    this->vet = vet;
}

Veterinary *Animal::getVeterinary() const {
    return vet;
}

int Animal::youngest = INT_MAX;

Animal::Animal(string name, int age) {
    this->name = name, this->age = age;
    this->vet = NULL;
    if(this->age < youngest)
        youngest = age;
}

Dog::Dog(string name, int age, string breed) : Animal(name, age) {
    this->breed = breed;
}

Flying::Flying(int maxv, int maxa) {
    this->maxAltitude = maxa, this->maxVelocity = maxv;
}

Bat::Bat(string name, int age, int maxv, int maxa) : Animal(name, age), Flying(maxv, maxa) {

}

int Animal::getYoungest() {
    return youngest;
}

bool Dog::isYoung() const {
    return this->age < 5;
}

bool Bat::isYoung() const {
    return this->age < 4;
}

string Animal::getInfo() const {
    string ans = "";
    ans += this->name + ", " + to_string(this->age);
    if(this->vet != NULL){
        ans = ans + this->vet->getInfo();
    }
    return ans;
}

string Dog::getInfo() const {
    string ans = "";
    ans += Animal::getInfo() + ", " + this->breed;
    //std::cout << ans << std::endl;
    return ans;
}

int Flying::getMaxAltitude() const {
    return this->maxAltitude;
}

int Flying::getMaxVelocity() const {
    return this->maxVelocity;
}

string Bat::getInfo() const {
    string ans = "";
    ans += Animal::getInfo() + ", " + to_string(this->getMaxVelocity()) + ", " + to_string(this->getMaxAltitude());
    //std::cout << ans << std::endl;
    return ans;
}




