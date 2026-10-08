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
	int upKey; 
	int downKey; 
} Paddle;

void movePaddle(Paddle *paddle); 
void paddleReset(Paddle *paddle, int x, int y); 

#endif
