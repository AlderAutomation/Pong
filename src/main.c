// Matthew Heltman 
// Sep 14 2026
//
// lets make pong! 

// need rules for how to win (first to 3)
// single with game AI 

#include <raylib.h>
#include <stdio.h>
#include <time.h>

#include "Entity.h"
#include "Paddle.h"
#include "Ball.h"


// Enum of scenes 
typedef enum {
	SCENE_MENU, 
	SCENE_GAMEPLAY, 
	SCENE_GAMEOVER, 
	SCENE_OPTIONS
} Scene;

// Check win condition and return 0 to end game or 1 to continue game 
int checkWin(Ball *ball, Paddle *playerOne, Paddle *playerTwo) {
	if (playerOne->score == 3) {
		printf("Player One wins\n"); 
		return 0; 
	} else if (playerTwo->score == 3) {
		printf("Player two wins\n"); 
		return 0; 
	} else {
		return 1;
	}
}

int main () {

	// Some core game consts
	const int PADDLE_WIDTH = 10; 
	const int PADDLE_HEIGHT = 100; 
	const int PADDLE_OFFSET = 10;
	const float PADDLE_SPEED = 10.0; 
	const int WIN_WIDTH = 800; 
	const int WIN_HEIGHT = 600; 

	// Const Strings 
	const char *TITLE = "PONG!";
	const char *ONE_PLAYER = "Start One Player Game"; 
	const char *TWO_PLAYER = "Start Two Player Game";
	const char *OPTIONS = "Options menu";
	const int FONT_SIZE = 30; 

	// Create the ball
	Ball ball; 
	ballInit(&ball); 

	// Create the paddles/players 
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

	// random seed based on time for the ball direction and speed
	SetRandomSeed(time(NULL)); 

	// Create window
	InitWindow(WIN_WIDTH, WIN_HEIGHT, "Ponger!"); 
	// limit the FPS, otherwise dayum
	SetTargetFPS(30); 

	// set the current scene
	Scene currentScene = SCENE_MENU; 

	while (!WindowShouldClose()) {
		
		// switch case for logic 
		switch (currentScene) {
			case SCENE_MENU: 


				break; 

			case SCENE_GAMEPLAY: 
				// bind paddles to movement keys 
				// This should be moved to options for player choice 
				// Also this should display on screen somewhere 
				movePaddle(&playerOne, KEY_W, KEY_S); 
				movePaddle(&playerTwo, KEY_I, KEY_J); 

				// moves ball in chosen random directions
				moveBall(&ball); 
				// checks for horizontal confines and reverses direction
				bounceBall(&ball);
				// Checks ball for vertical windows bound and updates appropriate players score
				checkScore(&ball, &playerOne, &playerTwo); 

				// checks players score and switches to game over screen if one player is at a score of 3
				// TODO working on this after scenes 
				if (checkWin(&ball, &playerOne, &playerTwo) == 0) {
					// restart game 
					printf("Restart game\n");
				}

				break; 

			case SCENE_GAMEOVER: 

				break; 
		}


		BeginDrawing(); 
		ClearBackground(BLACK); 


		// switch case for drawing 
		switch (currentScene) {
			case SCENE_MENU: 
				// draw title 
				int titleWidth = MeasureText(TITLE, FONT_SIZE*3); 
				DrawText(TITLE, GetScreenWidth()/2-titleWidth/2, GetScreenHeight()/2-200, FONT_SIZE*3, RAYWHITE); 

				// draw menu: Play 2 player, play 1 player, options
				int onePlayerWidth = MeasureText(ONE_PLAYER, FONT_SIZE);
				int twoPlayerWidth = MeasureText(TWO_PLAYER, FONT_SIZE); 
				int optionWidth = MeasureText(OPTIONS, FONT_SIZE);

				DrawText(ONE_PLAYER, GetScreenWidth()/2-onePlayerWidth/2, GetScreenHeight()/2+20, FONT_SIZE, RAYWHITE); 
				DrawText(TWO_PLAYER, GetScreenWidth()/2-onePlayerWidth/2, GetScreenHeight()/2+60, FONT_SIZE, RAYWHITE); 
				DrawText(OPTIONS, GetScreenWidth()/2-optionWidth/2, GetScreenHeight()/2+100, FONT_SIZE, RAYWHITE);

				break; 

			case SCENE_GAMEPLAY: 
				// Draw player one score
				char playerOneScoreText[50]; 
				snprintf(playerOneScoreText, sizeof(playerOneScoreText), "Player One Score: %d", playerOne.score);
				DrawText(playerOneScoreText, 10, 10, 30, RAYWHITE); 

				// draw player two score 
				char playerTwoScoreText[50]; 
				snprintf(playerTwoScoreText, sizeof(playerTwoScoreText), "Player Two Score: %d", playerTwo.score);
				DrawText(playerTwoScoreText, 410, 10, 30, RAYWHITE); 
		
				// draw players 
				DrawRectangle(playerOne.entity.x, playerOne.entity.y, playerOne.width, playerOne.height, RAYWHITE); 
				DrawRectangle(playerTwo.entity.x, playerTwo.entity.y, playerTwo.width, playerOne.height, RAYWHITE); 

				// draw ball
				DrawCircle(ball.entity.x, ball.entity.y, ball.radius, RAYWHITE); 

				// draw game lines 
				DrawLine(0, 50, 800, 50, RAYWHITE); // horizantal to sperate score from game 
				DrawLine(400, 0, 400, 600, RAYWHITE); // vertical for center court
				DrawLine(0, 599, 800, 599, RAYWHITE); // vertical to give visual bounds of court

				break; 

			case SCENE_GAMEOVER: 

				break; 

		}


		EndDrawing(); 
	}

	CloseWindow(); 

	return 0;
}
