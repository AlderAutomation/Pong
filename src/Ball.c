// Matthew Heltman
// Sep 22 2026
//
// Ball 

#include <raylib.h>

#include <stdbool.h>
#include "Ball.h"


void ballInit(Ball *ball) {
	ball->entity.x = 400; 
	ball->entity.y = 300; 
	ball->radius = 10.0; 

	ball->speedX = GetRandomValue(0, 1) ? 10 : -10; 
	ball->speedY = GetRandomValue(-15, 15); 
}


void moveBall(Ball *ball) {
	ball->entity.x += ball->speedX; 
	ball->entity.y += ball->speedY; 
}


bool bounceBall(Ball *ball) {
	if (ball->entity.y - ball->radius <= 50 || ball->entity.y + ball->radius >= GetScreenHeight()) {
		ball->speedY *= -1; 
		return true; 
	} else {
		return false; 
	}
}



