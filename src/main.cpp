// Matthew Heltman 
// Sep 14 2026
//
// lets make pong! 


// need a paddle object, initiated twice 
// need a ball object
// need window bounds on top and bottom 
// need to track current game score 
// need rules for how to win (first to 3)
// Multi Player 
// will therefore need two sets of controls 
// single with game AI 

// will need to set up cmake 
// setup include folders for objects and the logger 
//


#include <iostream>

#include "Entity.hpp"

int main () {

	std::cout << "\n\nHello World\n"; 

	Entity ball(5, 5); 
	ball.printStatus(); 

	return 0;
}
