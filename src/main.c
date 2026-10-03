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

int whoWon = 0; 

// Check win condition and return 0 to end game or 1 to continue game 
int checkWin(Ball *ball, Paddle *playerOne, Paddle *playerTwo) {
	if (playerOne->score == 3) {
		whoWon = 1; 
		return 0; 
	} else if (playerTwo->score == 3) {
		whoWon = 2; 
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
	const char *ONE_PLAYER = "Start 1P Game"; 
	const char *TWO_PLAYER = "Start 2P Game";
	const char *OPTIONS = "Options menu";
	const int FONT_SIZE = 30; 
	const char *GAMEOVER = "Game Over!"; 
	const char *P1_WINS = "Player 1 wins!";
	const char *P2_WINS = "Player 2 wins!";
	const char *RESTART = "Click anywhere to start over."; 


	// Create the ball
	Ball ball; 
	ballInit(&ball); 

	// Create the paddles/players 
	Paddle playerOne;
	paddleReset(&playerOne, PADDLE_OFFSET, (WIN_HEIGHT/2)-(PADDLE_HEIGHT/2), PADDLE_WIDTH, PADDLE_HEIGHT, PADDLE_SPEED, 0); 

	Paddle playerTwo; 
	paddleReset(&playerTwo, WIN_WIDTH - (PADDLE_OFFSET+PADDLE_WIDTH), (WIN_HEIGHT/2)-(PADDLE_HEIGHT/2), PADDLE_WIDTH, PADDLE_HEIGHT, PADDLE_SPEED, 0); 

	// random seed based on time for the ball direction and speed
	SetRandomSeed(time(NULL)); 

	// Create window
	InitWindow(WIN_WIDTH, WIN_HEIGHT, "Ponger!"); 
	// limit the FPS, otherwise dayum
	SetTargetFPS(30); 

	// set the current scene
	Scene currentScene = SCENE_MENU; 

	// some text width veriables for centering 
	int onePlayerWidth = MeasureText(ONE_PLAYER, FONT_SIZE);
	int twoPlayerWidth = MeasureText(TWO_PLAYER, FONT_SIZE); 
	int optionWidth = MeasureText(OPTIONS, FONT_SIZE);
	int gameOverWidth = MeasureText(GAMEOVER, FONT_SIZE*3); 
	int p1WinsWidth = MeasureText(P1_WINS, FONT_SIZE); 
	int p2WinsWidth = MeasureText(P2_WINS, FONT_SIZE); 


	while (!WindowShouldClose()) {
		
		// switch case for logic 
		switch (currentScene) {
			// Main menu logic
			case SCENE_MENU: 
				Rectangle onePlayerButton = {GetScreenWidth()/2-onePlayerWidth/2, GetScreenHeight()/2+30, onePlayerWidth, FONT_SIZE}; 
				Rectangle twoPlayerButton = {GetScreenWidth()/2-twoPlayerWidth/2, GetScreenHeight()/2+90, twoPlayerWidth, FONT_SIZE};
				Rectangle optionsButton = { GetScreenWidth()/2-optionWidth/2, GetScreenHeight()/2+150, optionWidth, FONT_SIZE,};

				Vector2 mouse = GetMousePosition(); 

				if (CheckCollisionPointRec(mouse, onePlayerButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
					currentScene = SCENE_GAMEPLAY; 
				}

				if (CheckCollisionPointRec(mouse, twoPlayerButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
					currentScene = SCENE_GAMEPLAY; 
				}

				if (CheckCollisionPointRec(mouse, optionsButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
					currentScene = SCENE_GAMEPLAY; 
				}

				
				break; 

			// Main gameplay logic
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
				if (checkWin(&ball, &playerOne, &playerTwo) == 0) {
					currentScene = SCENE_GAMEOVER; 
				}

				break; 

			// Gameover logic
			case SCENE_GAMEOVER: 
				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
					currentScene = SCENE_MENU; 
					whoWon = 0; 
					paddleReset(&playerOne, PADDLE_OFFSET, (WIN_HEIGHT/2)-(PADDLE_HEIGHT/2), PADDLE_WIDTH, PADDLE_HEIGHT, PADDLE_SPEED, 0); 
					paddleReset(&playerTwo, WIN_WIDTH - (PADDLE_OFFSET+PADDLE_WIDTH), (WIN_HEIGHT/2)-(PADDLE_HEIGHT/2), PADDLE_WIDTH, PADDLE_HEIGHT, PADDLE_SPEED, 0); 
				}
				
				break; 

			// options logic
			case SCENE_OPTIONS:

				break; 
		}


		BeginDrawing(); 
		ClearBackground(BLACK); 


		// switch case for drawing 
		switch (currentScene) {
			// Main menu drawing 
			case SCENE_MENU: 
				// draw title 
				int titleWidth = MeasureText(TITLE, FONT_SIZE*3); 
				DrawText(TITLE, GetScreenWidth()/2-titleWidth/2, GetScreenHeight()/2-200, FONT_SIZE*3, RAYWHITE); 

				// draw menu: Play 2 player, play 1 player, options
				DrawText(ONE_PLAYER, GetScreenWidth()/2-onePlayerWidth/2, GetScreenHeight()/2+30, FONT_SIZE, RAYWHITE); 
				DrawText(TWO_PLAYER, GetScreenWidth()/2-onePlayerWidth/2, GetScreenHeight()/2+90, FONT_SIZE, RAYWHITE); 
				DrawText(OPTIONS, GetScreenWidth()/2-optionWidth/2, GetScreenHeight()/2+150, FONT_SIZE, RAYWHITE);

				break; 

			// Gameplay drawing
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

			// Gameover drawing
			case SCENE_GAMEOVER: 
				char gameOverText[10]; 
				DrawText(GAMEOVER, GetScreenWidth()/2-gameOverWidth/2, 100, FONT_SIZE*3, RAYWHITE); 

				char winnerText[14]; 
				if (whoWon == 1) {
					DrawText(P1_WINS, GetScreenWidth()/2-p1WinsWidth/2, GetScreenHeight()/2 + 30, FONT_SIZE, RAYWHITE); 
				} else if (whoWon == 2) {
					DrawText(P2_WINS, GetScreenWidth()/2-p2WinsWidth/2, GetScreenHeight()/2 + 30, FONT_SIZE, RAYWHITE); 
				} else {
					printf("Error on player win check?");
				}

				break; 

			// Options menu drawing 
			case SCENE_OPTIONS: 

				break; 
		}


		EndDrawing(); 
	}

	CloseWindow(); 

	return 0;
}
