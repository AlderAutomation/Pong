// Matthew Heltman 
// Sep 14 2026
//
// lets make pong! 


// need a paddle object, initiated twice 
// need a ball object
// need window bounds on top and bottom 
// need to track current game score 
// need rules for how to win (first to 3)
// Multi Player 
// will therefore need two sets of controls 
// single with game AI 

// will need to set up cmake 
// setup include folders for objects and the logger 
//


#include <raylib.h>
#include <stdio.h>
#include <time.h>

#include "Entity.h"
#include "Paddle.h"
#include "Ball.h"


int main () {

	const int PADDLE_WIDTH = 10; 
	const int PADDLE_HEIGHT = 100; 
	const int PADDLE_OFFSET = 10;
	const float PADDLE_SPEED = 10.0; 

	const int WIN_WIDTH = 800; 
	const int WIN_HEIGHT = 600; 

	Ball ball; 
	ballInit(&ball); 

	Paddle playerOne; 
	playerOne.entity.x = PADDLE_OFFSET;
	playerOne.entity.y = (WIN_HEIGHT/2)-(PADDLE_HEIGHT/2);
	playerOne.width = PADDLE_WIDTH; 
	playerOne.height = PADDLE_HEIGHT; 
	playerOne.speed = PADDLE_SPEED; 

	Paddle playerTwo; 
	playerTwo.entity.x = WIN_WIDTH - (PADDLE_OFFSET+PADDLE_WIDTH); 
	playerTwo.entity.y = (WIN_HEIGHT/2)-(PADDLE_HEIGHT/2);
	playerTwo.width = PADDLE_WIDTH; 
	playerTwo.height = PADDLE_HEIGHT; 
	playerTwo.speed = PADDLE_SPEED; 

	SetRandomSeed(time(NULL)); 

	InitWindow(WIN_WIDTH, WIN_HEIGHT, "Ponger!"); 
	SetTargetFPS(30); 

	while (!WindowShouldClose()) {
		movePaddle(&playerOne, KEY_W, KEY_S); 
		movePaddle(&playerTwo, KEY_I, KEY_J); 

		moveBall(&ball); 
		bounceBall(&ball);
		checkScore(&ball, &playerOne, &playerTwo); 	

		BeginDrawing(); 

		ClearBackground(BLACK); 
		
		char playerOneScoreText[50]; 
		snprintf(playerOneScoreText, sizeof(playerOneScoreText), "Player One Score: %d", playerOne.score);
		DrawText(playerOneScoreText, 10, 10, 30, RAYWHITE); 

		char playerTwoScoreText[50]; 
		snprintf(playerTwoScoreText, sizeof(playerTwoScoreText), "Player Two Score: %d", playerTwo.score);
		DrawText(playerTwoScoreText, 410, 10, 30, RAYWHITE); 
		
		DrawRectangle(playerOne.entity.x, playerOne.entity.y, playerOne.width, playerOne.height, RAYWHITE); 
		DrawRectangle(playerTwo.entity.x, playerTwo.entity.y, playerTwo.width, playerOne.height, RAYWHITE); 
		DrawCircle(ball.entity.x, ball.entity.y, ball.radius, RAYWHITE); 

		DrawLine(0, 50, 800, 50, RAYWHITE); // horizantal to sperate score from game 
		DrawLine(400, 0, 400, 600, RAYWHITE); // vertical for center court
		DrawLine(0, 599, 800, 599, RAYWHITE); // vertical to give visual bounds of court


		EndDrawing(); 
	}

	CloseWindow(); 

	return 0;
}
