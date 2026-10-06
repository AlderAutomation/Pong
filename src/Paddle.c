// Mathew Heltman 
// Sep 16 2026
//
// Paddle header file 

#include <stdio.h>
#include <raylib.h>
#include <math.h>

#include "Paddle.h"
#include "Entity.h"


void paddleInit(Paddle *paddle) {
	paddle->width = 0; 
	paddle->height = 0; 
	paddle->score = 0; 
	paddle->speed = 0.0; 
}


void updateScore(Paddle *paddle, int score) {
	paddle->score = paddle->score + score; 
}


void movePaddle(Paddle *paddle, int upKey, int downKey) {
	// movement 
	if (IsKeyDown(upKey)) {
		paddle->entity.y -= paddle->speed; 
	}

	if (IsKeyDown(downKey)) {
		paddle->entity.y += paddle->speed; 
	}

	// window boundaries
	if (paddle->entity.y < 50) {
		paddle->entity.y = 50; 
	}

	if (paddle->entity.y + paddle->height > GetScreenHeight()) {
		paddle->entity.y = GetScreenHeight()-paddle->height; 
	}

}



void paddlePrintStatus(Paddle *paddle) {
	printf("POS X,Y: %i, %i\nWidth: %i\nHeight: %i\nScore: %i\n",
			paddle->entity.x, 
			paddle->entity.y, 
			paddle->width, 
			paddle->height, 
			paddle->score); 
}


void paddleReset(Paddle *paddle, int x, int y, int w, int h, float speed, int score) {
	paddle->entity.x = x;
	paddle->entity.y = y;
	paddle->width = w; 
	paddle->height = h; 
	paddle->speed = speed; 
	paddle->score = score; 

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

void AIPaddle(Ball *ball, Paddle *paddle) {
	float paddleCenter = paddle->entity.y + paddle->height / 2.0f; 
	float difference = ball->entity.y - paddleCenter; 
	float centerDifference = (GetScreenHeight()/2) - paddleCenter;


	if (ball->speedX > 0) { // move to ball
		if (fabsf(difference) > 10.0f) { // movement delay to kill jitter
			if (difference > 0) {
				paddle->entity.y += paddle->speed; 
			} else {
				paddle->entity.y -= paddle->speed; 
			}
		}
	} else { // move to center
		if (fabsf(centerDifference) > 10.0f) {
			if (centerDifference > 0) {
				paddle->entity.y += paddle->speed; 
			} else {
				paddle->entity.y -= paddle->speed; 
			}
		}
	}

	// window boundaries
	if (paddle->entity.y < 50) {
		paddle->entity.y = 50; 
	}

	if (paddle->entity.y + paddle->height > GetScreenHeight()) {
		paddle->entity.y = GetScreenHeight()-paddle->height; 
	}

}
