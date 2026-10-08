// Matthew Heltman 
// Sep 14 2026
//
// lets make pong! 

#include <raylib.h>
#include <stdio.h>
#include <time.h>

#include "Game.h"
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


// global variable to for which game mode player is in: 
// 0 = currently playing or in menus 
// 1 = p1 wins 
// 2 = p2 wins 
int whoWon = 0; 



int main () {

	// Some core game consts
	const int PADDLE_WIDTH = 10; 
	const int PADDLE_HEIGHT = 100; 
	const int PADDLE_OFFSET = 10;
	const float PADDLE_SPEED = 10.0; 
	const int WIN_WIDTH = 800; 
	const int WIN_HEIGHT = 600; 
	const int FONT_SIZE = 30; 

	// Const Strings 
	const char *TITLE = "PONG!";
	const char *ONE_PLAYER = "Start 1P Game"; 
	const char *TWO_PLAYER = "Start 2P Game";
	const char *OPTION = "Options";
	const char *GAMEOVER = "Game Over!"; 
	const char *P1_WINS = "Player 1 wins!";
	const char *P2_WINS = "Player 2 wins!";
	const char *RESTART = "Click anywhere to start over."; 

	// Game mode 
	// 1 = 1 player (default)
	// 2 = 2 player 
	int gameMode = 1; 

	bool isGamePaused = false; 

	

	// time tracking variables  
	double matchStartTime; 
	double matchElapsedTime; 

	// Create the ball
	Ball ball; 
	ballInit(&ball); 

	// Create the paddles/players 
	Paddle playerOne;
	paddleReset(&playerOne, PADDLE_OFFSET, (GetScreenHeight()/2)-(PADDLE_HEIGHT/2), PADDLE_WIDTH, PADDLE_HEIGHT, PADDLE_SPEED, 0); 

	Paddle playerTwo; 
	paddleReset(&playerTwo, WIN_WIDTH - (PADDLE_OFFSET+PADDLE_WIDTH), (GetScreenHeight()/2)-(PADDLE_HEIGHT/2), PADDLE_WIDTH, PADDLE_HEIGHT, PADDLE_SPEED, 0); 

	// random seed based on time for the ball direction and speed
	SetRandomSeed(time(NULL)); 

	// Create window
	InitWindow(WIN_WIDTH, WIN_HEIGHT, "Pong!"); 
	// limit the FPS, otherwise its dayum fast!
	SetTargetFPS(30); 

	// set the current scene, game starts in main menu 
	Scene currentScene = SCENE_MENU; 

	// Options menu variables 
	float musicVolume = 0.3f; 
	float sfxVolume = 1.0f; 
	int p1UpKey = KEY_W; 
	int p1DownKey = KEY_S; 
	int p2UpKey = KEY_I; 
	int p2DownKey = KEY_J; 	
	
	
	// some text width veriables for text centering 
	// Note: i want to move this up with other text variables but it breaks everything when i do. 
	int onePlayerWidth = MeasureText(ONE_PLAYER, FONT_SIZE);
	int twoPlayerWidth = MeasureText(TWO_PLAYER, FONT_SIZE); 
	int optionWidth = MeasureText(OPTION, FONT_SIZE);
	int inOptionWidth = MeasureText(OPTION, FONT_SIZE*3); 
	int gameOverWidth = MeasureText(GAMEOVER, FONT_SIZE*3); 
	int p1WinsWidth = MeasureText(P1_WINS, FONT_SIZE); 
	int p2WinsWidth = MeasureText(P2_WINS, FONT_SIZE); 	

	// Audio settings 
	InitAudioDevice(); 
	Music themeSong = LoadMusicStream("include/kontraa-water-afro-pop-music-445661.mp3"); 
	themeSong.looping = true; 
	SetMusicVolume(themeSong, 0.3f); 
	PlayMusicStream(themeSong); 
	Sound bounce = LoadSound("include/sumaga123-marble-440414.wav");


	while (!WindowShouldClose()) {
		UpdateMusicStream(themeSong); 	

		// switch case for logic 
		switch (currentScene) {
			// Main menu logic
			case SCENE_MENU: 
				// Rectangles for menu options buttones 
				Rectangle onePlayerButton = {GetScreenWidth()/2-onePlayerWidth/2, GetScreenHeight()/2+30, onePlayerWidth, FONT_SIZE}; 
				Rectangle twoPlayerButton = {GetScreenWidth()/2-twoPlayerWidth/2, GetScreenHeight()/2+90, twoPlayerWidth, FONT_SIZE};
				Rectangle optionsButton = { GetScreenWidth()/2-optionWidth/2, GetScreenHeight()/2+150, optionWidth, FONT_SIZE,};

				// find mouse pos 
				Vector2 mouse = GetMousePosition(); 

				// check for mouse on button on left mouseclick 
				if (CheckCollisionPointRec(mouse, onePlayerButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
					// start timer to track elapsed time of game 
					matchStartTime = GetTime();

					currentScene = SCENE_GAMEPLAY; 
					gameMode = 1; 
				}

				if (CheckCollisionPointRec(mouse, twoPlayerButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
					// start timer to track elapsed time of game 
					matchStartTime = GetTime();

					currentScene = SCENE_GAMEPLAY; 
					gameMode = 2; 
				}

				if (CheckCollisionPointRec(mouse, optionsButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
					currentScene = SCENE_OPTIONS; 
				}

				
				break; 

			// Main gameplay logic
			case SCENE_GAMEPLAY: 
				// Check for pause key 
				if (IsKeyPressed(KEY_P)) {
					isGamePaused = !isGamePaused; 
				}

				if (!isGamePaused) {
					// bind paddles to movement keys 
					movePaddle(&playerOne, p1UpKey, p1DownKey); 
					if (gameMode == 2) {
						movePaddle(&playerTwo, p2UpKey, p2DownKey); 
					} else {
						AIPaddle(&ball, &playerTwo); 
					}

					// moves ball in chosen random directions
					moveBall(&ball); 
					
					// checks for horizontal confines and reverses direction
					if (bounceBall(&ball)) {
						PlaySound(bounce); 
					}
				
					// Checks ball for vertical windows bound and updates appropriate players score
					checkScore(&ball, &playerOne, &playerTwo); 

					// checks players score and switches to game over screen if one player is at a score of 3
					if (checkWin(&playerOne, &playerTwo, &whoWon) == 0) {
						// get elapsed time 
						matchElapsedTime = GetTime() - matchStartTime; 
	
						currentScene = SCENE_GAMEOVER; 
					}

					// check for ball on paddle collision, reverse direction, and play sound 
					if (checkPaddleCollision(&ball, &playerOne)) {
						ball.speedX *= -1;  
						PlaySound(bounce); 
					}

					if (checkPaddleCollision(&ball, &playerTwo)) {
						ball.speedX *= -1; 
						PlaySound(bounce); 
					}

					break; 
				}

			// Gameover logic
			case SCENE_GAMEOVER: 
				// click anywhere to restart the game back to main menu 
				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
					currentScene = SCENE_MENU; 
					whoWon = 0; 
					paddleReset(&playerOne, PADDLE_OFFSET, (WIN_HEIGHT/2)-(PADDLE_HEIGHT/2), PADDLE_WIDTH, PADDLE_HEIGHT, PADDLE_SPEED, 0); 
					paddleReset(&playerTwo, WIN_WIDTH - (PADDLE_OFFSET+PADDLE_WIDTH), (WIN_HEIGHT/2)-(PADDLE_HEIGHT/2), PADDLE_WIDTH, PADDLE_HEIGHT, PADDLE_SPEED, 0); 
				}
				
				break; 

			// options logic
			case SCENE_OPTIONS:
				// get mouse 
				Vector2 optionsMouse = GetMousePosition();

				// create clickable spots 
				Rectangle musicCheckBox = {GetScreenWidth()-125, 250, FONT_SIZE, FONT_SIZE};
				Rectangle sfxCheckBox = {GetScreenWidth()-125, 300, FONT_SIZE, FONT_SIZE};
				Rectangle exitBox = {0, GetScreenHeight()-FONT_SIZE, 125, FONT_SIZE}; // guessed at width. Should make proper responsive var

				// check for clicks 
				// Music
				if (CheckCollisionPointRec(optionsMouse, musicCheckBox) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
					if (musicVolume == 0.3f) {
						musicVolume = 0.0f; 
					} else {
						musicVolume = 0.3f; 
					}

					SetMusicVolume(themeSong, musicVolume);
				}

				// sound effects
				if (CheckCollisionPointRec(optionsMouse, sfxCheckBox) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
					if (sfxVolume == 1.0f) {
						sfxVolume = 0.0f; 
					} else {
						sfxVolume = 1.0f; 
					}

					SetSoundVolume(bounce, sfxVolume);
				}

				// Exit button 
				if (CheckCollisionPointRec(optionsMouse, exitBox) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
					currentScene = SCENE_MENU; 
				}

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
				DrawText(OPTION, GetScreenWidth()/2-optionWidth/2, GetScreenHeight()/2+150, FONT_SIZE, RAYWHITE);

				// draw hint text for player controls
				DrawText("P1 up: W down: S", 0, GetScreenHeight()-FONT_SIZE, FONT_SIZE, RAYWHITE); 
				DrawText("P2 up: I down: J", GetScreenWidth()-250, GetScreenHeight()-FONT_SIZE, FONT_SIZE, RAYWHITE); // 250 is guess and should be changed to relative var 
				DrawText("P to Pause", GetScreenWidth()/2-90, GetScreenHeight()-FONT_SIZE, FONT_SIZE, RAYWHITE); 

				break; 

			// Gameplay drawing
			case SCENE_GAMEPLAY: 
				// Draw player one score
				char playerOneScoreText[50]; 
				snprintf(playerOneScoreText, sizeof(playerOneScoreText), "Player One Score: %d", playerOne.score);
				DrawText(playerOneScoreText, 10, 10, FONT_SIZE, RAYWHITE); 

				// draw player two score 
				char playerTwoScoreText[50]; 
				snprintf(playerTwoScoreText, sizeof(playerTwoScoreText), "Player Two Score: %d", playerTwo.score);
				DrawText(playerTwoScoreText, 410, 10, FONT_SIZE, RAYWHITE); 
		
				// draw players 
				DrawRectangle(playerOne.entity.x, playerOne.entity.y, playerOne.width, playerOne.height, RAYWHITE); 
				DrawRectangle(playerTwo.entity.x, playerTwo.entity.y, playerTwo.width, playerOne.height, RAYWHITE); 

				// draw ball
				DrawCircle(ball.entity.x, ball.entity.y, ball.radius, RAYWHITE); 

				// draw game lines 
				DrawLine(0, 50, 800, 50, RAYWHITE); // horizantal to seperate score from game 
				DrawLine(400, 0, 400, 600, RAYWHITE); // vertical for center court
				DrawLine(0, 599, 800, 599, RAYWHITE); // vertical to give visual bounds of court

				break; 

			// Gameover drawing
			case SCENE_GAMEOVER: 
				// draw game over title 
				char gameOverText[10]; 
				DrawText(GAMEOVER, GetScreenWidth()/2-gameOverWidth/2, 100, FONT_SIZE*3, RAYWHITE); 

				// draw elapsed time 
				char elapsedTimeMsge[500]; 
				snprintf(elapsedTimeMsge, sizeof(elapsedTimeMsge), "Match took: %.1f", matchElapsedTime); 
				DrawText(elapsedTimeMsge, 0, 0, FONT_SIZE, RAYWHITE); 

				// draw who wins 
				char winnerText[14]; 
				if (whoWon == 1) {
					DrawText(P1_WINS, GetScreenWidth()/2-p1WinsWidth/2, GetScreenHeight()/2 + 30, FONT_SIZE, RAYWHITE); 
				} else if (whoWon == 2) {
					DrawText(P2_WINS, GetScreenWidth()/2-p2WinsWidth/2, GetScreenHeight()/2 + 30, FONT_SIZE, RAYWHITE); 
				} else {
					printf("Error on player win check?");
				}

				// draw hint text to click anywhere to restart
				DrawText("Click anywhere to restart", 10, GetScreenHeight()-40, FONT_SIZE, RAYWHITE); 

				break; 

			// Options menu drawing 
			case SCENE_OPTIONS: 
				DrawText(OPTION, GetScreenWidth()/2-inOptionWidth/2, 100, FONT_SIZE*3, RAYWHITE); 

				// music volume 
				DrawText("Music Volume: ", 125, 250, FONT_SIZE, RAYWHITE); 
				if (musicVolume == 0.0f) {
					DrawRectangle(GetScreenWidth()-125, 250, FONT_SIZE, FONT_SIZE, RED); 
				} else {
					DrawRectangle(GetScreenWidth()-125, 250, FONT_SIZE, FONT_SIZE, GREEN); 
				}


				// SFX Volume 
				DrawText("SFX Volume: ", 125, 300, FONT_SIZE, RAYWHITE); 
				if (sfxVolume == 0.0f) {
					DrawRectangle(GetScreenWidth()-125, 300, FONT_SIZE, FONT_SIZE, RED); 
				} else {
					DrawRectangle(GetScreenWidth()-125, 300, FONT_SIZE, FONT_SIZE, GREEN); 
				}

				// exit/back to menu button
				DrawText("<- Main Menu", 0, GetScreenHeight()-FONT_SIZE, FONT_SIZE, RAYWHITE); 

				break; 
		}


		EndDrawing(); 
	}

	// Clean ups 
	UnloadSound(bounce);
	UnloadMusicStream(themeSong);

	CloseAudioDevice(); 
	CloseWindow(); 

	return 0;
}
