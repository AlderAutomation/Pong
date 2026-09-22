// Matthew Heltman 
// Sep 15 2026
//
// paddle entity

#ifndef PADDLE_H
#define PADDLE_H

#include "Entity.h"

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


#endif
