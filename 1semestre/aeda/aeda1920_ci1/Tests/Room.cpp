#include <iostream>
#include "Room.h"

using namespace std;

Room::Room(): code(0), floor(0), reservation(false) {}

Room::Room(string c, int f) : code(c), floor(f), reservation(false) {
	roomLength = 0;
	roomWidth = 0;
}

Room::Room(string c, int f, int w, int l) : code(c), floor(f), roomWidth(w), roomLength(l), reservation(false) {
}

string Room::getCode() const {
	return code;
}

int Room::getFloor() const {
	return floor;
}

int Room::getWidth() const {
    return roomWidth;
}

int Room::getLength() const {
    return roomLength;
}

float Room::getArea() const {
    return roomLength * roomWidth / 10000; // need to ensure conversion from cm2 to m2
}

void Room::setLength(int roomLength){
    this->roomLength = roomLength;
}

void Room::setWidth(int roomWidth){
    this->roomWidth = roomWidth;
}

bool Room::getReservation() const{
    return reservation;
}

void Room::setReservation(bool roomReserv){
    this->reservation = roomReserv;
}

RegularRoom::RegularRoom(string c, int f) : Room (c, f) {
}

RegularRoom::RegularRoom(string c, int f, int w, int l) : Room (c, f, w, l) {
}


FamilyRoom::FamilyRoom(string c, int f) : Room (c, f) {
    numChildrenBed = 0;
}
FamilyRoom::FamilyRoom(std::string c, int f, int w, int l, float numCB) : Room (c, f, w, l) {
    this->numChildrenBed = numCB;
}

int FamilyRoom::getNumChildrenBed() const {
    return numChildrenBed;
}

void FamilyRoom::setNumChildrenBed(int numCB){
    this->numChildrenBed = numCB;
}


LuxuryRoom::LuxuryRoom(string c, int f) : Room(c, f) {
    typeBed = "";
}

LuxuryRoom::LuxuryRoom(std::string c, int f, int w, int l, std::string typeBed) : Room(c, f, w, l) {
    this->typeBed = typeBed;
}


string LuxuryRoom::getTypeBed() const {
    return typeBed;
}

void LuxuryRoom::setTypeBed(string tB){
    this->typeBed = tB;
}



//------------------------------------------
//------------------------------------------

//TODO
bool Room::operator == (const Room &room) const{
    if( (this->code == room.code) && (this->floor == room.floor) )
        return true;
    return false;
}

//TODO
float RegularRoom::price() const {
    float singlePrice = 4.0;
    return singlePrice * this->getArea();
}

//TODO
float FamilyRoom::price() const {
    float singlePrice = 4.0;
    return singlePrice * this->getArea();
}

//TODO
float LuxuryRoom::price() const {
    float singlePrice = 4.0 * 1.15;
    return singlePrice * this->getArea();
}




