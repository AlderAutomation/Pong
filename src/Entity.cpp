// Matthew Heltman 
// Sept 15 
//
// Entity class for ball and paddle parent 


#include <iostream>

#include "Entity.hpp"

Entity::Entity() {
	X = 0; 
	Y = 0; 
}

Entity::Entity(int X, int Y) {
	this->X = X; 
	this->Y = Y;
}

int Entity::getX() {
	return this->X; 
}

int Entity::getY() {
	return this->Y; 
}

void Entity::setX(int X) {
	this->X = X; 
}

void Entity::setY(int Y) {
	this->Y = Y; 
}

void Entity::draw() {
	std::cout << "I'm drawing the entity.\n";
}

void Entity::printStatus() {
	std::cout << "POS X: " << this->X
		<< "\nPOS Y: " << this->Y << "\n";
}
