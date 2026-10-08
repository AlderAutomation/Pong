// Matthew Heltman
// Sep 22 2026
//
// Ball 

#include <raylib.h>

#include <stdbool.h>
#include "Ball.h"

/**
 * reset the ball on game start and after scoring 
 * 
 * @param ball to reset ball data fields 
 */
void resetBallToStart(Ball *ball) {
	ball->entity.x = 400; 
	ball->entity.y = 300; 
	ball->radius = 10.0; 

	ball->speedX = GetRandomValue(0, 1) ? 10 : -10; 
	ball->speedY = GetRandomValue(-15, 15); 
}

/**
 * ball movement function 
 * 
 * @param ball to update x,y based on speed
 */
void moveBall(Ball *ball) {
	ball->entity.x += ball->speedX; 
	ball->entity.y += ball->speedY; 
}


/**
 * checks the horizontal confines, walls, and reverses direction 
 * 
 * @param ball needed for the balls y and speed 
 * @return bool for sound file trigger
 */
bool bounceBall(Ball *ball) {
	if (ball->entity.y - ball->radius <= 50 || ball->entity.y + ball->radius >= GetScreenHeight()) {
		ball->speedY *= -1; 
		return true; 
	} else {
		return false; 
	}
}



