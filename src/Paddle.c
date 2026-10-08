// Mathew Heltman 
// Sep 16 2026
//
// Paddle header file 


#include <raylib.h>

#include "Paddle.h"
#include "Entity.h"


/**
 * User input to move user paddles and vertical window bounding 
 * 
 * @param paddle to know which player paddle to move 
 */
void movePaddle(Paddle *paddle) {
	// movement 
	if (IsKeyDown(paddle->upKey)) {
		paddle->entity.y -= paddle->speed; 
	}

	if (IsKeyDown(paddle->downKey)) {
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


/**
 * To reset the paddles back to begining so we can have rematches without reloading entire game 
 * 
 * @param paddle to distinguish which paddle to reset
 * @param x int positional
 * @param y int positional 
 */
void paddleReset(Paddle *paddle, int x, int y) {
	paddle->entity.x = x;
	paddle->entity.y = y;
	paddle->score = 0; 
}
