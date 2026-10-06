// Matthew Heltman 
// Sep 15 2026
//
// paddle entity

#ifndef PADDLE_H
#define PADDLE_H

#include "Entity.h"
#include "Ball.h"

typedef struct {
	Entity entity; 
	int width; 
	int height; 
	int score; 
	float speed; 
} Paddle;

void paddleInit(Paddle *paddle); 
void updateScore(Paddle *paddle, int score); 
void movePaddle(Paddle *paddle, int upKey, int downKey); 
void paddlePrintStatus(Paddle *paddle); 
void paddleReset(Paddle *paddle, int x, int y, int w, int h, float speed, int score); 
bool checkPaddleCollision(Ball *ball, Paddle *paddle); 
void checkScore(Ball *ball, Paddle *playerOne, Paddle *playerTwo); 
void AIPaddle(Ball *ball, Paddle *paddle); 

#endif
