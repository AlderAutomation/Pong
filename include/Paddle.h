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
	char upControl; 
	char downControl; 
	int score; 
} Paddle;

void paddleInit(Paddle *paddle); 
void updateScore(Paddle *paddle, int score); 
void paddlePrintStatus(Paddle *paddle); 

#endif
