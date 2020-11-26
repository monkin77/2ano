#ifndef SRC_HOTEL_H_
#define SRC_HOTEL_H_

#include <vector>
#include <list>
#include <algorithm>

template <class Chamber>
class Hotel {
	std::vector<Chamber *> chambers;
	const unsigned int maxCapacity;
	const std::string city;
    std::list<Chamber> reservationsDone;
public:
	Hotel(int size, std::string municipality);
	~Hotel();
	std::vector<Chamber *> getChambers() const;
	void setChambers(std::vector<Chamber *> chambers);
	int getCapacity() const;
    std::list<Chamber> getReservationsDone() const;
	bool addChamber(Chamber *chamber);
    void addReservationDone(Chamber chamber);
    Chamber* removeChamber(std::string code, int floor);
	float avgArea(int floor) const;
	void sortChambers();
	bool doReservation(std::string code, int floor);
    std::list<Chamber> roomsNeverReserved() const;
};

class NoSuchChamberException {
public:
	NoSuchChamberException() { }
};

class NoSuchFloorException{
private:
    int floor;
public:
    NoSuchFloorException(int floor) { this->floor = floor;}
    int getFloor() { return this->floor; }
};

template <class Chamber>
Hotel<Chamber>::Hotel(int size, std::string municipality) : maxCapacity(size), city(municipality) {
}

template <class Chamber>
Hotel<Chamber>::~Hotel(){
	typename std::vector<Chamber *>::const_iterator it;
	for (it=chambers.begin(); it!=chambers.end(); it++) {
		delete *it;
	}
}

template<class Chamber>
std::vector<Chamber *> Hotel<Chamber>::getChambers() const {
	return chambers;
}

template<class Chamber>
void Hotel<Chamber>::setChambers(std::vector<Chamber*> chambers) {
	this->chambers = chambers;
}

template<class Chamber>
int Hotel<Chamber>::getCapacity() const {
	return maxCapacity;
}

template<class Chamber>
void Hotel<Chamber>::addReservationDone(Chamber chamber) {
    reservationsDone.push_back(chamber);
}

template<class Chamber>
std::list<Chamber> Hotel<Chamber>::getReservationsDone() const {
    return reservationsDone;
}

//------------------------------------------------------
//------------------------------------------------------

//TODO
template<class Chamber>
bool Hotel<Chamber>::addChamber(Chamber *chamber) {
    if(this->getChambers().size() < this->maxCapacity){
        for(int i = 0; i < this->chambers.size(); i++){
            if( ( *(this->chambers[i]) ) == (*chamber) )          // if this room already exists
                return false;
        }
        this->chambers.push_back(chamber);
        return true;
    }
    return false;
}


//TODO
template<class Chamber>
void Hotel<Chamber>::sortChambers() {
    int minIdx;
    float maxFloor;
    std::string minCode;
    /*
    for(int i = 0; i< this->chambers.size(); i++){
        minCode = this->chambers[i]->getCode();
        maxFloor = -1000;
        minIdx = 0;
        for(int j = i; j < this->chambers.size(); j++){
            //std::cout << this->chambers[j]->getCode() << std::endl;
            if(this->chambers[j]->getCode() < minCode){
                minIdx = j, minCode = this->chambers[j]->getCode();
                maxFloor = this->chambers[j]->getFloor();
            }
            else if(this->chambers[j]->getCode() == minCode){
                if(this->chambers[j]->getFloor() > maxFloor){
                    minIdx = j, minCode = this->chambers[j]->getCode();
                    maxFloor = this->chambers[j]->getFloor();
                }
            }
        }
        if( *(this->chambers[i]) == *(this->chambers[minIdx]) ){
            continue;
        }
        else{
            Room* aux = this->chambers[i];
            this->chambers[i] = this->chambers[minIdx], this->chambers[minIdx] = aux;   // this->chamber[minxIdx] = copy of aux thats why its not lost
        }
    } */
    sort(this->chambers.begin(), this->chambers.end(), [](Chamber* c1, Chamber* c2){
        if(c1->getCode() < c2->getCode())
            return true;
        else if(c1->getCode() == c2->getCode()){
            if(c1->getFloor() > c2->getFloor())
                return true;
        }
        return false;
    });
}

//TODO
template<class Chamber>
Chamber* Hotel<Chamber>::removeChamber(std::string code, int floor) {
    for(int i = 0; i < this->chambers.size(); i++){
        if( (this->chambers[i]->getCode() == code) && (this->chambers[i]->getFloor() == floor) ){
            Chamber* res = this->chambers[i];
            this->chambers.erase(this->chambers.begin() + i);
            return res;
        }
    }
    throw NoSuchChamberException();
}

//TODO
template<class Chamber>
float Hotel<Chamber>::avgArea(int floor) const {
    std::vector<int> floorIdx;
    int size = 0;
    float sum;
    for(int i = 0; i < this->chambers.size(); i++){
        if(this->chambers[i]->getFloor() == floor){
            floorIdx.push_back(i);
            size++;
        }
    }
    if(size == 0)
        throw NoSuchFloorException(floor);
    for(int i = 0; i < size; i++){
        sum += this->chambers[floorIdx[i]]->getArea();
    }
    return sum / size;
}

//TODO
template<class Chamber>
bool Hotel<Chamber>::doReservation(std::string code, int floor){
    for(int i = 0; i < this->chambers.size(); i++){
        if( (this->chambers[i]->getCode() == code) && (this->chambers[i]->getFloor() == floor)){
            if(this->chambers[i]->getReservation())
                return false;
            this->chambers[i]->setReservation(true);
            this->addReservationDone(*(this->chambers[i]));
            return true;
        }
    }
    return false;
}

//TODO
template<class Chamber>
std::list<Chamber> Hotel<Chamber>::roomsNeverReserved() const {
    std::list<Chamber> res;
    bool found;
    for(int i = 0; i < this->chambers.size(); i++){
        found = false;
        for(auto it = this->reservationsDone.begin(); it != this->reservationsDone.end(); it++){
            if( (this->chambers[i]->getCode() == it->getCode()) && (this->chambers[i]->getFloor() == it->getFloor()) ){
                found = true;
                break;
            }
        }
        if(!found)
            res.push_back(*(this->chambers[i]));
    }
    return res;
}



#endif /* SRC_HOTEL_H_ */
