// Mathew Heltman 
// Sep 16 2026
//
// Paddle header file 

#include <stdio.h>
#include <raylib.h>

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
