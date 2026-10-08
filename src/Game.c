// Matthew Heltman
// Oct 08 2026

// Game logic file for game logic functions

#include <raylib.h>
#include <math.h>

#include "Game.h"
#include "Paddle.h"
#include "Ball.h"


/**
 * Checks the ball position and scores point accordingly and then restart the ball
 * 
 * @param ball required for checking ball postion compared to vertical edges 
 * of screen
 * @param player required to update score 
 */
void checkScore(Ball *ball, Paddle *playerOne, Paddle *playerTwo) {
	if (ball->entity.x <= 0) {
		incrementPlayerScore(playerTwo); 
		ballInit(ball); 
	}

	if (ball->entity.x >= GetScreenWidth()) {
		incrementPlayerScore(playerOne); 
		ballInit(ball); 
	}
}


/**
 * Increments player score by one, required by checkScore. 
 * 
 * @param paddle the player that we would like to update * 
 */
void incrementPlayerScore(Paddle *paddle) {
	paddle->score = paddle->score + 1; 
}


/**
 * Checks the score of paddles and decides if there is a winner or continue playing 
 *
 * @param paddle pass both players to check their scores
 * @param whoWon int value: 1 = playerOne, 2 = playerTwo
 * @return 0 if winner and 1 if no winner
 */
int checkWin(Paddle *playerOne, Paddle *playerTwo, int *whoWon) {
	if (playerOne->score == 3) {
		*whoWon = 1; 
		return 0; 
	} else if (playerTwo->score == 3) {
		*whoWon = 2; 
		return 0; 
	} else {
		return 1;
	}
}


/**
 * to check collision of ball against paddle and send it back
 * 
 * @param ball we need the we need the x, y, and rad of ball
 * @param paddle we need the pos and size of the paddle 
 * @return bool to say collided or not 
 */
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


/**
 * AI handling of second paddle while in single player mode. compares the x,y 
 * of ball and paddle and moves the paddle towards the ball
 * 
 * @param ball needed for the ai to see balls x,y 
 * @param paddle needed for the ai to see the paddles x,y position
 */
void AIPaddle(Ball *ball, Paddle *paddle) {
	float paddleCenter = paddle->entity.y + paddle->height / 2.0f; 
	float ballPaddleDifference = ball->entity.y - paddleCenter; 
	float screenPaddleCentersDifference = (GetScreenHeight()/2) - paddleCenter;


	// if ball is positive X and past the screen center
	if (ball->speedX > 0 && ball->entity.x > GetScreenWidth()/2) { 
		// if the abs diference is greater than 20, added to reduce ai paddle jittering 
		if (fabsf(ballPaddleDifference) > 20.0f) {
			if (ballPaddleDifference > 0) {
				paddle->entity.y += paddle->speed; 
			} else {
				paddle->entity.y -= paddle->speed; 
			}
		}
	} else { // move back to center of play space
		if (fabsf(screenPaddleCentersDifference) > 20.0f) {
			if (screenPaddleCentersDifference > 0) {
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