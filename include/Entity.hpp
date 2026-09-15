// Matthew Heltman 
// Sep 15 2026
//
// Entity header file 

#pragma once

class Entity {

private: 
	int X; 
	int Y; 

public: 
	// constructors 
	Entity(); 
	Entity(int X, int Y); 

	// getters 
	int getX(); 
	int getY(); 

	// setters 
	void setX(int X); 
	void setY(int Y);

	// Functions 
	void draw(); 
	void printStatus(); 
};
