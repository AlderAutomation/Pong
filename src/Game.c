// Matthew Heltman
// Oct 08 2026

// Game logic file for game logic functions

#include "Game.h"
#include "Paddle.h"
#include "Ball.h"



/**
 * Checks the score of paddles and decides if there is a winner or continue playing 
 *
 * @param paddle pass both players to check their scores
 * @param whoWon int value: 1 = playerOne, 2 = playerTwo
 * @return 0 if winner and 1 if no winner
 */
int checkWin(Paddle *playerOne, Paddle *playerTwo, int *whoWon) {
	if (playerOne->score == 3) {
		*whoWon = 1; 
		return 0; 
	} else if (playerTwo->score == 3) {
		*whoWon = 2; 
		return 0; 
	} else {
		return 1;
	}
}