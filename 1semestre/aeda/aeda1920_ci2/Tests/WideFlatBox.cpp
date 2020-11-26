#include <algorithm>
#include "WideFlatBox.h"

WideFlatBox::WideFlatBox(double capacity) : Box(capacity) {
}

void WideFlatBox::insert(Object object) {
	if(getContentSize()+object.getSize() <= getCapacity()) {
		objects.push_back(object);
		setContentSize(getContentSize()+object.getSize());
	} else {
		throw ObjectDoesNotFitException();
	}
}

const Object& WideFlatBox::next() const {
	return objects[0];
}

void WideFlatBox::sortObjects() {
	sort(objects.begin(), objects.end());
}


void WideFlatBox::remove(Object object) {
    bool found = false;
    for(auto it = this->objects.begin(); it !=this->objects.end(); it++){
        if(*it == object){
            this->setContentSize(this->getContentSize() - object.getSize());
            this->objects.erase(it);
            found = true;
            if(this->objects.empty())
                break;
        }
    }
    if(!found)
        throw InaccessibleObjectException(object);
}
