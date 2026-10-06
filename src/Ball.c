// Matthew Heltman
// Sep 22 2026
//
// Ball 

#include <raylib.h>

#include <stdbool.h>
#include "Ball.h"
#include "Paddle.h"


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


void bounceBall(Ball *ball) {
	if (ball->entity.y - ball->radius <= 50 || ball->entity.y + ball->radius >= GetScreenHeight()) {
		ball->speedY *= -1; 
	}
}


void checkScore(Ball *ball, Paddle *playerOne, Paddle *playerTwo) {
	if (ball->entity.x <= 0) {
		updateScore(playerTwo, 1); 
		ballInit(ball); 
	}

	if (ball->entity.x >= GetScreenWidth()) {
		updateScore(playerOne, 1); 
		ballInit(ball); 
	}
}


bool checkPaddleCollision(Ball *ball, Paddle *paddle) {
	return CheckCollisionCircleRec(
			(Vector2){ball->entity.x, ball->entity.y}, 
			ball->radius, 
			(Rectangle){
				paddle->entity.x, 
				paddle->entity.y, 
				paddle->width, 
				paddle->height
			}
		);
}
