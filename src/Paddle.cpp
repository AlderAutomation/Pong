// Mathew Heltman 
// Sep 16 2026
//
// Paddle header file 

#include <iostream>

#include "Paddle.hpp"


// Constructors 
Paddle::Paddle() {
	upControl = 'w'; 
	downControl = 's'; 
	score = 0; 
} 

Paddle::Paddle(char up, char down) {
	upControl = up; 
	downControl = down; 
	score = 0; 
}

Paddle::Paddle(char up, char down, int score) {
	upControl = up; 
	downControl = down; 
	this->score = score; 
}


// Getters 
char Paddle::getUpControl() {
	return this->upControl; 
}

char Paddle::getDownControl() {
	return this->downControl;
}

int Paddle::getScore() {
	return this->score; 
}


// Setters 
void Paddle::setUpControl(char control) {
	this->upControl = control;
}

void Paddle::setDownControl(char control) {
	this->downControl = control; 
}

void Paddle::setScore(int score) {
	this->score = score; 
}


// functions 
int Paddle::increaseScore() {
	this->score = this->score + 1; 

	return this->score; 
}

void Paddle::printStatus() {
	std::cout << "POS X: " << this->getX() 
		<< "\nPOS y: " << this->getY()
		<< "\nUp: " << this->getUpControl() 
		<< "\ndown: " << this->getDownControl()
		<< "\nScore: " << this->getScore() << "\n";
}

