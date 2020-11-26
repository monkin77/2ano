#include "ThinTallBox.h"
#include "WideFlatBox.h"

ThinTallBox::ThinTallBox(double capacity) : Box(capacity) {
}

ThinTallBox::ThinTallBox(double capacity, stack<Object> objects, double content_size) : Box(capacity) {
	this->objects = objects;
	this->setContentSize(content_size);
}

stack<Object> ThinTallBox::getObjects() const {
    return objects;
}

void ThinTallBox::remove(Object object) {
	Object next_object = next();
	if(!(next_object == object)) {
		throw InaccessibleObjectException(object);
	} else {
		setContentSize(getContentSize()-next_object.getSize());
		objects.pop();
	}
}

const Object& ThinTallBox::next() const {
	return objects.top();
}


void ThinTallBox::insert(Object object) {
    if(this->getContentSize() + object.getSize() <= this->getCapacity()){
        this->setContentSize(this->getContentSize() + object.getSize());
        this->objects.push(object);
    }
    else
        throw ObjectDoesNotFitException();
}

void ThinTallBox::sortObjects() {
	stack<Object> ans;
	WideFlatBox aux(1000000);             //contains all the objects
	while(!this->objects.empty()){
	    aux.insert(this->objects.top());
	    this->remove(this->objects.top());
	}
	aux.sortObjects();
	try{
        while(!aux.empty()) {
            this->insert(aux.removeNext());
        }
	}
    catch(...){
        ;
    }
}
