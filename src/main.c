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


#include <stdio.h>
#include <raylib.h>

#include "Entity.h"
#include "Paddle.h"
#include "Ball.h"


int main () {

	const int PADDLE_WIDTH = 10; 
	const int PADDLE_HEIGHT = 100; 
	const int PADDLE_OFFSET = 10;

	const int WIN_WIDTH = 800; 
	const int WIN_HEIGHT = 600; 


	Ball ball; 
	ball.entity.x = 400; 
	ball.entity.y = 300; 
	ball.radius = 10; 

	Paddle playerOne; 
	playerOne.entity.x = PADDLE_OFFSET;
	playerOne.entity.y = (WIN_HEIGHT/2)-(PADDLE_HEIGHT/2);
	playerOne.upControl = 'w'; 
	playerOne.downControl = 's'; 
	playerOne.width = PADDLE_WIDTH; 
	playerOne.height = PADDLE_HEIGHT; 

	Paddle playerTwo; 
	playerTwo.entity.x = WIN_WIDTH - (PADDLE_OFFSET+PADDLE_WIDTH); 
	playerTwo.entity.y = (WIN_HEIGHT/2)-(PADDLE_HEIGHT/2);
	playerTwo.upControl = 'i';
	playerTwo.downControl = 'k';
	playerTwo.width = PADDLE_WIDTH; 
	playerTwo.height = PADDLE_HEIGHT; 

	InitWindow(WIN_WIDTH, WIN_HEIGHT, "Ponger!"); 

	while (!WindowShouldClose()) {
		
		BeginDrawing(); 

		ClearBackground(BLACK); 

		DrawRectangle(playerOne.entity.x, playerOne.entity.y, playerOne.width, playerOne.height, RAYWHITE); 
		DrawRectangle(playerTwo.entity.x, playerTwo.entity.y, playerTwo.width, playerOne.height, RAYWHITE); 
		DrawCircle(ball.entity.x, ball.entity.y, ball.radius, RAYWHITE); 

		EndDrawing(); 
	}

	CloseWindow(); 

	return 0;
}
