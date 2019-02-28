#pragma once

#include "Animal.h"


class Event {
public:
	Event() {}
	virtual void handle() = 0;
};


class ChangeDirection:public Event {
public:	
	Animal* ani1;
	Animal* ani2; 
	
	//change ani1's direction
	ChangeDirection(Animal* ani1, Animal* ani2): ani1(ani1), ani2(ani2) {}
	
	void handle() {
		ani1->changeDir(*ani2);
	}
};


class DeleteObject:public Event {
public:
	Animal* ani;
	DeleteObject(Animal* animal): ani(animal) {}

	void handle() {
		ani->deleteFlag = true;
	}
};


class StopModeling:public Event {
public:
	StopModeling() {}

	void handle() {}
};