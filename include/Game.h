// Matthew Heltman
// Oct 08 2026

// Game logic file for game logic functions

#ifndef GAME_H
#define GAME_H

#include "Paddle.h"
#include "Ball.h"


int checkWin(Paddle *playerOne, Paddle *playerTwo, int *whoWon); 
void checkScore(Ball *ball, Paddle *playerOne, Paddle *playerTwo); 
void incrementPlayerScore(Paddle *paddle); 
bool checkPaddleCollision(Ball *ball, Paddle *paddle); 
void AIPaddle(Ball *ball, Paddle *paddle); 


#endif