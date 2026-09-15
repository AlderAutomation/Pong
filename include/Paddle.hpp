// Matthew Heltman 
// Sep 15 2026
//
// paddle entity

#include "Entity.hpp"

class Paddle : public Entity {
	private: 
		char upControl; 
		char downControl;
		int score; 

	public: 
		// Constructors 
		Paddle();
		Paddle(char up, char down);
		Paddle(char up, char down, int score);

		// Getters 
		char getUpControl(); 
		char getDownControl(); 
		int getScore(); 

		// Setters
		void setUpControl(char control); 
		void setDownControl(char control); 
		void setScore(int score); 

		// Functions 
		int increaseScore(); 
		void printStatus() override; 
};
