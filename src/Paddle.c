// Mathew Heltman 
// Sep 16 2026
//
// Paddle header file 

#include <stdio.h>

#include "Paddle.h"
#include "Entity.h"


void paddleInit(Paddle *paddle) {
	paddle->width = 0; 
	paddle->height = 0; 
	paddle->upControl = 'w'; 
	paddle->downControl = 's'; 
	paddle->score = 0; 
}


void updateScore(Paddle *paddle, int score) {
	paddle->score = paddle->score + score; 
}


void paddlePrintStatus(Paddle *paddle) {
	printf("POS X: %i\nPOS Y: %i\nWidth: %i\nHeight: %i\nControls: %c, %c\nScore: %i\n",
			paddle->entity.x, 
			paddle->entity.y, 
			paddle->width, 
			paddle->height, 
			paddle->upControl, 
			paddle->downControl, 
			paddle->score); 
}

